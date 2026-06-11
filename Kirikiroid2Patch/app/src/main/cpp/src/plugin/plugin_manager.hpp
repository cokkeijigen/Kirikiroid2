#pragma once
#include <filesystem>
#include <string>
#include <vector>
#include <jni.h>
#include <dlfcn.h>

namespace kr2patch
{
    class plugin_manager
    {
        std::vector<void*>     m_dl_handles{};
        std::filesystem::path m_plugin_path{};
        JavaVM* m_jvm;

    public:
        ~plugin_manager() noexcept;
        plugin_manager () noexcept {};

        auto unload() noexcept -> void;
        auto load(const std::filesystem::path& path) noexcept -> bool;
        auto load(std::string_view             path) noexcept -> bool;

        auto is_init() noexcept -> bool;
        auto init(JavaVM* const jvm) noexcept -> bool;
    };
}