#include <pulgin_function.hpp>


namespace TVP
{

    auto AddAutoPath(const ttstr& path) noexcept -> bool
    {
        return k2a::tvp::add_auto_path(path);
    }

    auto RemoveAutoPath(const ttstr& path) noexcept -> bool
    {
        return k2a::tvp::remove_auto_path(path);
    }

    auto GetPlacedPath(const ttstr& path) noexcept -> std::optional<ttstr>
    {
        return k2a::tvp::get_placed_path(path);
    }

    auto IsExistentStorage(const ttstr& path) noexcept -> std::optional<bool>
    {
        return k2a::tvp::is_existent_storage(path);
    }

    auto GetAppPath() noexcept -> std::optional<ttstr>
    {
        return k2a::tvp::get_app_path();
    }

    auto GetGamePath() noexcept -> std::optional<ttstr>
    {
        return k2a::tvp::get_game_path();
    }

    auto GetLocalName(ttstr& name) noexcept -> std::optional<ttstr>
    {
        return k2a::tvp::get_local_name(name);
    }

    auto ExtractStorageExt(const ttstr& name) noexcept -> ttstr
    {
        return k2a::tvp::extract_storage_ext(name);
    }

    auto ExtractStorageName(const ttstr& name) noexcept -> ttstr
    {
        return k2a::tvp::extract_storage_name(name);
    }

    auto ExtractStoragePath(const ttstr& name) noexcept -> ttstr
    {
        return k2a::tvp::extract_storage_path(name);
    }

    auto ChopStorageExt(const ttstr& name) noexcept -> ttstr
    {
        return k2a::tvp::chop_storage_ext(name);
    }

    auto RegisterStorageMedia(iTVPStorageMedia* media) noexcept -> bool
    {
        return k2a::tvp::register_storage_media(media);
    }

    auto UnregisterStorageMedia(iTVPStorageMedia* media) noexcept -> bool
    {
        return k2a::tvp::unregister_storage_media(media);
    }

    auto IsExistentStorageNoSearch(const ttstr& name) noexcept -> std::optional<bool>
    {
        return k2a::tvp::is_existent_storage_no_search(name);
    }

    auto IsExistentStorageNoSearchNoNormalize(const ttstr& name) noexcept -> std::optional<bool>
    {
        return k2a::tvp::is_existent_storage_no_search_no_normalize(name);
    }

    auto ClearStorageCaches() noexcept -> bool
    {
        return k2a::tvp::clear_storage_caches();
    }

    auto SetCurrentDirectory(const ttstr& directory) noexcept -> bool
    {
        return k2a::tvp::set_current_directory(directory);
    }

    auto NormalizeStorageName(const ttstr& name) noexcept -> std::optional<ttstr>
    {
        return k2a::tvp::normalize_storage_name(name);
    }

    auto CreateTextStreamForRead(const ttstr& name, const ttstr& modestr) noexcept -> iTJSTextReadStream*
    {
        return k2a::tvp::create_text_stream_for_read(name, modestr);
    }

    auto CreateTextStreamForWrite(const ttstr& name, const ttstr& modestr) noexcept -> iTJSTextWriteStream*
    {
        return k2a::tvp::create_text_stream_for_write(name, modestr);
    }

    auto CreateBinaryStreamForRead(const ttstr& name, const ttstr& modestr) noexcept -> tTJSBinaryStream*
    {
        return k2a::tvp::create_binary_stream_for_read(name, modestr);
    }

    auto CreateBinaryStreamForWrite(const ttstr& name, const ttstr& modestr) noexcept -> tTJSBinaryStream*
    {
        return k2a::tvp::create_binary_stream_for_write(name, modestr);
    }

    auto GetDefaultReadEncoding() noexcept -> const tjs_char*
    {
        return k2a::tvp::get_default_read_encoding();
    }

    auto SetDefaultReadEncoding(const ttstr& name) noexcept -> bool
    {
        return k2a::tvp::set_default_read_encoding(name);
    }

    auto GetCommandLine(const tjs_char* name, tTJSVariant* value) -> std::optional<bool>
    {
        return k2a::tvp::get_command_line(name, value);
    }

    auto SetCommandLine(const tjs_char* name, const ttstr& value) -> bool
    {
        return k2a::tvp::set_command_line(name, value);
    }

    auto GetTickCount() -> std::optional<tjs_uint64>
    {
        return k2a::tvp::get_tick_count();
    }
}