#include <filesystem>
#include <native-lib.hpp>
#include <plugin_manager.hpp>
#include <thread>
#include <chrono>

namespace kr2patch
{
    static JavaVM *javavm{};
    static kr2patch::plugin_manager plugin_manager{};

    auto get_jvm() noexcept -> JavaVM*
    {
        return kr2patch::javavm;
    }

    static noinline auto TVPLoadPlugins() -> void
    {
        std::optional<ttstr> tjsstr_path{ k2a::tvp::get_game_path() };
        if(!tjsstr_path.has_value() || (*tjsstr_path).IsEmpty())
        {
            return;
        }

        std::filesystem::path plugin_path{ (*tjsstr_path).c_str() };
        plugin_path.append(u"plugin");
        logd("plugin_path: %s\n", plugin_path.string().c_str());

        std::error_code error{};
        if (!std::filesystem::exists(plugin_path, error) || !std::filesystem::is_directory(plugin_path, error) || error)
        {
            logd("plugin_path not exists!\n");
            return;
        }

        size_t count{};
        const std::string_view target_suffix = armv8orv7(".plugin.arm64-v8a.so", ".plugin.armeabi-v7a.so");
        for (const auto& entry : std::filesystem::directory_iterator(plugin_path, error))
        {
            const std::filesystem::path& current_path = entry.path();
            if (std::filesystem::is_regular_file(current_path))
            {
                std::string_view filename_view = current_path.filename().native();
                if(filename_view.ends_with(target_suffix))
                {
                    const bool is_load = plugin_manager.load(current_path);
                    if(is_load)
                    {
                        count++;
                        logd("load plugin: %s\n", current_path.string().c_str());
                    }
                    else
                    {
                        logd("load plugin failed: %s\n", current_path.string().c_str());
                    }
                }
            }
        }
        logd("load %zu plugin.\n", count);
    }

    static noinline auto TVPExecuteStartupScript_Hook() noexcept -> void*
    {
        logd("TVPExecuteStartupScript_Hook called!");

        if(kr2patch::plugin_manager.is_init())
        {
            arm_only(TVPLoadPlugins());
        }
        return hooker::call<TVPExecuteStartupScript_Hook>();
    }

    extern "C" JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved)
    {
        kr2patch::javavm = vm;

        if(plugin_manager.init(javavm))
        {
            logd("plugin_manager init success!\n");
        }
        else
        {
            logd("plugin_manager init failed!\n");
        }

        if(kr2android::init())
        {
            logd("kr2android init success!\n");
            void* const TVPExecuteStartupScript = k2a::cast_ptr(tvprva(0x8E5004, 0));
            if(TVPExecuteStartupScript != nullptr)
            {
                bool success = hooker::add<TVPExecuteStartupScript_Hook>(TVPExecuteStartupScript);
                logd("Add TVPExecuteStartupScript Hook: %s", success ? "success": "failed");
            }
            else
            {
                logd("Get TVPExecuteStartupScript Address Failed!");
            }
        }
        else
        {
            logd("kr2android init failed!\n");
        }

        return JNI_VERSION_1_6;
    }
}
