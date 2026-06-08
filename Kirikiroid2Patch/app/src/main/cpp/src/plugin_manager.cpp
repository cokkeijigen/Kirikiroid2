#include <plugin_manager.hpp>
#include <native-lib.hpp>
#include <kr2android.hpp>

namespace kr2patch
{
    static auto K2A_OnLoad(void* modbase, JavaVM* jvm) -> void
    {
    }

    plugin_manager::~plugin_manager() noexcept
    {
        this->unload();
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
            target_length += 8;

            std::string plugin_path{};
            plugin_path.reserve(target_length);
            plugin_path.append(path_cstr, target_length - 8);
            plugin_path.append("/plugin/");

            this->m_plugin_path = plugin_path;
            if(std::filesystem::exists(this->m_plugin_path, error) && !error)
            {
                std::filesystem::remove_all(this->m_plugin_path, error);
                if(error)
                {
                    logd("remove plugin path failed: %s\n", error.message().c_str());
                }
            }
            std::filesystem::create_directories(this->m_plugin_path, error);

            return std::filesystem::exists(this->m_plugin_path, error) && !error;
        }
        catch (...) { }

        if (is_attached)
        {
            jvm->DetachCurrentThread();
        }

        return false;
    }

    auto plugin_manager::unload() noexcept -> void
    {
        if(!this->m_dl_handles.empty())
        {
            for (void* handle : this->m_dl_handles)
            {
                if (handle != nullptr)
                {
                    ::dlclose(handle);
                }
            }
            this->m_dl_handles.clear();
        }

        if(!this->m_plugin_path.empty())
        {
            std::error_code error{};
            std::filesystem::remove_all(this->m_plugin_path, error);
        }
    }

    auto plugin_manager::load(std::string_view path) noexcept -> bool
    {
        if(this->m_plugin_path.empty())
        {
            return false;
        }
        return this->load(std::filesystem::path{ path });
    }

    auto plugin_manager::load(const std::filesystem::path& path) noexcept -> bool
    {
        if(this->m_plugin_path.empty())
        {
            return false;
        }

        std::error_code error{};
        if(!std::filesystem::exists(path, error)  && !error)
        {
            return false;
        }

        std::filesystem::path redirect_path = this->m_plugin_path / path.filename();
        std::filesystem::copy_file(path, redirect_path, std::filesystem::copy_options::overwrite_existing, error);

        if (error)
        {
            return false;
        }

        void* handle = ::dlopen(redirect_path.string().c_str(), RTLD_NOW | RTLD_GLOBAL);
        if(handle == nullptr)
        {
            std::filesystem::remove(redirect_path, error);
            return false;
        }

        ::dlerror();
        void* k2a_onload = ::dlsym(handle, "K2A_OnLoad");
        if (::dlerror() == nullptr && k2a_onload != nullptr)
        {
            const auto call = reinterpret_cast<decltype(&K2A_OnLoad)>(k2a_onload);
            call(k2a::get_base().ptr, this->m_jvm);
        }

        this->m_dl_handles.push_back(handle);
        return true;
    }
}