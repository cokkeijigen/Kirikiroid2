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
        struct libpair_t
        {
            uint64_t hash;
            void*  handle;
        };

        std::vector<libpair_t> m_dl_handles{};
        std::filesystem::path m_plugin_path{};
        JavaVM* m_jvm;

        [[gnu::noinline]] auto    _load(const std::filesystem::path& path) noexcept -> bool;
        [[gnu::noinline]] auto  _unload(const std::filesystem::path& path) noexcept -> bool;
        [[gnu::noinline]] auto  _unload(void* handle) noexcept -> void;
        [[gnu::noinline]] auto _is_load(const std::filesystem::path& path) noexcept -> bool;

    public:
        ~plugin_manager() noexcept;
        plugin_manager () noexcept {};

        auto unload_all() noexcept -> void;
        auto unload(const std::filesystem::path&     path) noexcept -> bool;
        auto unload(std::string_view                 path) noexcept -> bool;

        auto load(const std::filesystem::path& path) noexcept -> bool;
        auto load(std::string_view             path) noexcept -> bool;

        auto is_load(const std::filesystem::path& path) noexcept -> bool;
        auto is_load(std::string_view             path) noexcept -> bool;

        auto is_init() noexcept -> bool;
        auto init(JavaVM* const jvm) noexcept -> bool;
    };
}