#include <plugin_manager.hpp>
#include <native-lib.hpp>
#include <kr2android.hpp>
#include <optional>
#include <concepts>

namespace kr2patch
{
    template<std::invocable T>
    struct scoped
    {
        T call;
        ~scoped() { call(); }
    };

    template<class T> scoped(T) -> scoped<T>;

    static auto K2A_OnLoad(void* modbase, JavaVM* jvm) -> void
    {
    }

    static auto K2A_UnLoad() -> void
    {
    }

    static auto to_string(uint64_t hash) noexcept -> std::string
    {
        std::string result{};
        result.resize(17);

        std::snprintf(result.data(), result.size(), "%016llX", static_cast<unsigned long long>(hash));

        result.resize(16);
        return result;
    }

    static auto path_hash(const std::filesystem::path& path) noexcept -> std::optional<uint64_t>
    {
        std::string normal_str{ path.generic_string() };
        if(normal_str.empty())
        {
            return std::nullopt;
        }

        constexpr uint64_t fnv1a_prime { 0x00000100000001B3 };
        constexpr uint64_t fnv1a_offset{ 0xCBF29CE484222325 };
        uint64_t hash{ fnv1a_offset };
        for (char c : normal_str)
        {
            hash ^= static_cast<uint64_t>(c);
            hash *= fnv1a_prime;
        }
        return hash;
    }

    static auto path_hashstr(const std::filesystem::path& path) noexcept -> std::string
    {
        const std::optional<uint64_t> hash{ path_hash(path) };
        return hash.has_value() ? to_string(*hash) : std::string{};
    }

    plugin_manager::~plugin_manager() noexcept
    {
        this->unload_all();
        this->m_plugin_path.clear();
    }

    auto plugin_manager::is_init() noexcept -> bool
    {
        if(this->m_plugin_path.empty())
        {
            return false;
        }

        std::error_code error{};
        if(std::filesystem::exists(this->m_plugin_path, error) && !error)
        {
            return true;
        }
        return false;
    }

    auto plugin_manager::init(JavaVM* const jvm) noexcept -> bool
    {
        std::error_code error{};
        if(this->is_init())
        {
            return true;
        }

        this->m_jvm = jvm;
        if(jvm == nullptr)
        {
            return false;
        }

        JNIEnv* env{};
        bool is_attached{};

        const jint env_status = jvm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6);
        if (env_status == JNI_EDETACHED)
        {
            if(jvm->AttachCurrentThread(&env, nullptr) != JNI_OK)
            {
                return false;
            }
            is_attached = true;
        }
        [[maybe_unused]] scoped __auto_detach__{ [is_attached, jvm]() { if (is_attached) { jvm->DetachCurrentThread(); }} };

        try
        {
            const jclass             activity_thread_clz = env->FindClass("android/app/ActivityThread");
            const jmethodID current_activity_thread_mid  = env->GetStaticMethodID(activity_thread_clz, "currentActivityThread", "()Landroid/app/ActivityThread;");

            const jobject   activity_thread_obj = env->CallStaticObjectMethod(activity_thread_clz, current_activity_thread_mid);
            const jmethodID get_application_mid = env->GetMethodID(activity_thread_clz, "getApplication", "()Landroid/app/Application;");
            const jobject           context_obj = env->CallObjectMethod(activity_thread_obj, get_application_mid);

            if (context_obj == nullptr)
            {
                return false;
            }

            const jclass          context_clz = env->GetObjectClass(context_obj);
            const jmethodID get_files_dir_mid = env->GetMethodID(context_clz, "getFilesDir", "()Ljava/io/File;");
            const jobject            file_obj = env->CallObjectMethod(context_obj, get_files_dir_mid);

            if (file_obj == nullptr)
            {
                return false;
            }

            const jclass                 file_clz = env->GetObjectClass(file_obj);
            const jmethodID get_absolute_path_mid = env->GetMethodID(file_clz, "getAbsolutePath", "()Ljava/lang/String;");
            const jstring               path_jstr = static_cast<jstring>(env->CallObjectMethod(file_obj, get_absolute_path_mid));

            if (path_jstr == nullptr)
            {
                return false;
            }

            const char* path_cstr = env->GetStringUTFChars(path_jstr, nullptr);
            if(path_cstr == nullptr)
            {
                return false;
            }

            size_t target_length = std::strlen(path_cstr);
            if(target_length == 0)
            {
                return false;
            }

            if(path_cstr[target_length - 1] == '/')
            {
                target_length--;
            }

            target_length += 9;

            std::string plugin_path{};
            plugin_path.reserve(target_length);
            plugin_path.append(path_cstr, target_length - 9);
            plugin_path.append("/plugins/");

            this->m_plugin_path = plugin_path;
            if(std::filesystem::exists(this->m_plugin_path, error) && !error)
            {
                std::filesystem::remove_all(this->m_plugin_path, error);
            }

            std::filesystem::create_directories(this->m_plugin_path, error);
            return std::filesystem::exists(this->m_plugin_path, error) && !error;
        }
        catch (...) { }

        return false;
    }

    auto plugin_manager::unload_all() noexcept -> void
    {
        if(!this->m_dl_handles.empty())
        {
            for (const auto& lib : this->m_dl_handles)
            {
                this->_unload(lib.handle);
            }
            this->m_dl_handles.clear();
        }

        if(!this->m_plugin_path.empty())
        {
            std::error_code error{};
            std::filesystem::remove_all(this->m_plugin_path, error);
        }
    }

    auto plugin_manager::_load(const std::filesystem::path& path) noexcept -> bool
    {
        std::error_code error{};
        if(!std::filesystem::exists(path, error)  && !error)
        {
            return false;
        }

        const std::optional<uint64_t> hash{ path_hash(path) };
        if(!hash.has_value())
        {
            return false;
        }

        const std::string hash_str{ to_string(*hash) };
        std::filesystem::path redirect_dir = this->m_plugin_path / hash_str;

        if(std::filesystem::exists(path, error)  && !error)
        {
            std::filesystem::remove_all(redirect_dir, error);
            if(error)
            {
                return false;
            }
        }

        if(!std::filesystem::create_directories(redirect_dir, error) || error)
        {
            return false;
        }

        std::filesystem::path redirect_path = redirect_dir / path.filename();
        std::filesystem::copy_file(path, redirect_path, std::filesystem::copy_options::overwrite_existing, error);

        if (error)
        {
            return false;
        }

        void* handle = ::dlopen(redirect_path.string().c_str(), RTLD_NOW | RTLD_GLOBAL);
        if(handle == nullptr)
        {
            std::filesystem::remove_all(redirect_path, error);
            return false;
        }

        ::dlerror();
        void* k2a_onload = ::dlsym(handle, "K2A_OnLoad");
        if (::dlerror() == nullptr && k2a_onload != nullptr)
        {
            const auto call = reinterpret_cast<decltype(&K2A_OnLoad)>(k2a_onload);
            call(k2a::get_base().ptr, this->m_jvm);
        }

        this->m_dl_handles.push_back(plugin_manager::libpair_t{ *hash, handle });
        return true;
    }

    auto plugin_manager::_unload(const std::filesystem::path& path) noexcept -> bool
    {
        const std::optional<uint64_t> hash{ path_hash(path) };
        if(!hash.has_value())
        {
            return false;
        }

        for (auto it = this->m_dl_handles.begin(); it != this->m_dl_handles.end(); ++it)
        {
            if (it->hash != *hash)
            {
                continue;
            }
            this->_unload(it->handle);

            std::error_code error{};
            const std::filesystem::path dir{ this->m_plugin_path / to_string(*hash) };
            std::filesystem::remove_all(dir, error);

            this->m_dl_handles.erase(it);
            return true;
        }
        return false;
    }

    auto plugin_manager::_unload(void* handle) noexcept -> void
    {
        if(handle != nullptr)
        {
            ::dlerror();
            void* k2a_onload = ::dlsym(handle, "K2A_UnLoad");
            if (::dlerror() == nullptr && k2a_onload != nullptr)
            {
                reinterpret_cast<decltype(&K2A_UnLoad)>(k2a_onload)();
            }
            ::dlclose(handle);
        }
    }

    auto plugin_manager::unload(const std::filesystem::path& path) noexcept -> bool
    {
        if(this->m_dl_handles.empty())
        {
            return false;
        }
        return this->_unload(path);
    }

    auto plugin_manager::unload(std::string_view path) noexcept -> bool
    {
        if(this->m_dl_handles.empty())
        {
            return false;
        }
        return this->_unload(std::filesystem::path{ path });
    }

    auto plugin_manager::load(std::string_view path) noexcept -> bool
    {
        if(this->m_plugin_path.empty())
        {
            return false;
        }
        return this->_load(std::filesystem::path{ path });
    }

    auto plugin_manager::load(const std::filesystem::path& path) noexcept -> bool
    {
        if(this->m_plugin_path.empty())
        {
            return false;
        }
        return this->_load(path);
    }

}