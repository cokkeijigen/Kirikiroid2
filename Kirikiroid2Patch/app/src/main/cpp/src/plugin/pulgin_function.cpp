#include <pulgin_function.hpp>


namespace TVP
{
    auto AddAutoPath(const ttstr& path) noexcept -> bool
    {
        return k2a::tvp::storage::add_auto_path(path);
    }

    auto RemoveAutoPath(const ttstr& path) noexcept -> bool
    {
        return k2a::tvp::storage::remove_auto_path(path);
    }

    auto GetPlacedPath(const ttstr& path) noexcept -> std::optional<ttstr>
    {
        return k2a::tvp::storage::get_placed_path(path);
    }

    auto IsExistentStorage(const ttstr& path) noexcept -> std::optional<bool>
    {
        return k2a::tvp::storage::is_existent(path);
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
        return k2a::tvp::storage::get_local_name(name);
    }

    auto ExtractStorageExt(const ttstr& name) noexcept -> ttstr
    {
        return k2a::tvp::storage::extract_ext(name);
    }

    auto ExtractStorageName(const ttstr& name) noexcept -> ttstr
    {
        return k2a::tvp::storage::extract_name(name);
    }

    auto ExtractStoragePath(const ttstr& name) noexcept -> ttstr
    {
        return k2a::tvp::storage::extract_path(name);
    }

    auto ChopStorageExt(const ttstr& name) noexcept -> ttstr
    {
        return k2a::tvp::storage::chop_ext(name);
    }

    auto IsExistentStorageNoSearch(const ttstr& name) noexcept -> std::optional<bool>
    {
        return k2a::tvp::storage::is_existent_no_search(name);
    }

    auto IsExistentStorageNoSearchNoNormalize(const ttstr& name) noexcept -> std::optional<bool>
    {
        return k2a::tvp::storage::is_existent_no_search_no_normalize(name);
    }

    auto ClearStorageCaches() noexcept -> bool
    {
        return k2a::tvp::storage::clear_caches();
    }

    auto SetCurrentDirectory(const ttstr& directory) noexcept -> bool
    {
        return k2a::tvp::storage::set_current_directory(directory);
    }

    auto NormalizeStorageName(const ttstr& name) noexcept -> std::optional<ttstr>
    {
        return k2a::tvp::storage::normalize_name(name);
    }

    auto CreateTextStreamForRead(const ttstr& name, const ttstr& modestr) noexcept -> iTJSTextReadStream*
    {
        return k2a::tvp::stream::create_text_for_read(name, modestr);
    }

    auto CreateTextStreamForWrite(const ttstr& name, const ttstr& modestr) noexcept -> iTJSTextWriteStream*
    {
        return k2a::tvp::stream::create_text_for_write(name, modestr);
    }

    auto CreateBinaryStreamForRead(const ttstr& name, const ttstr& modestr) noexcept -> tTJSBinaryStream*
    {
        return k2a::tvp::stream::create_binary_for_read(name, modestr);
    }

    auto CreateBinaryStreamForWrite(const ttstr& name, const ttstr& modestr) noexcept -> tTJSBinaryStream*
    {
        return k2a::tvp::stream::create_binary_for_write(name, modestr);
    }

    auto GetDefaultReadEncoding() noexcept -> const tjs_char*
    {
        return k2a::tvp::scripts::get_text_encoding();
    }

    auto SetDefaultReadEncoding(const ttstr& name) noexcept -> bool
    {
        return k2a::tvp::scripts::set_text_encoding(name);
    }

    namespace StorageMedia
    {
        auto RegisterStorageMedia(iTVPStorageMedia* media) noexcept -> bool
        {
            return k2a::tvp::storage::register_media(media);
        }

        auto UnregisterStorageMedia(iTVPStorageMedia* media) noexcept -> bool
        {
            return k2a::tvp::storage::unregister_media(media);
        }
    }

    namespace XP3Archive
    {
        auto GetXP3ArchiveExtractionFilter() noexcept -> tTVPXP3ArchiveExtractionFilter
        {
            return k2a::tvp::xp3::get_extraction_filter();
        }

        auto GetXP3ArchiveContentFilter() noexcept -> tTVPXP3ArchiveContentFilter
        {
            return k2a::tvp::xp3::get_content_filter();
        }

        auto SetXP3ArchiveExtractionFilter(tTVPXP3ArchiveExtractionFilter filter) noexcept -> bool
        {
            return k2a::tvp::xp3::set_extraction_filter(filter);
        }

        auto SetXP3ArchiveContentFilter(tTVPXP3ArchiveContentFilter    filter) noexcept -> bool
        {
            return k2a::tvp::xp3::set_content_filter(filter);
        }
    }

    namespace Graphic
    {
        auto RegisterGraphicLoadingHandler
        (
            const ttstr&                      name,
            tTVPGraphicLoadingHandler      loading,
            tTVPGraphicHeaderLoadingHandler header,
            tTVPGraphicSaveHandler            save,
            tTVPGraphicAcceptSaveHandler    accept,
            void*                        formatdata
        ) noexcept -> bool
        {
            Graphic::HandlerType handler
            {
                .IsPlugin      = false,
                .Extension     = name,
                .LoadHandler   = loading,
                .HeaderHandler = header,
                .SaveHandler   = save,
                .AcceptHandler = accept,
                .FormatData    = formatdata
            };
            return k2a::tvp::graphic::register_loading_handler(handler);
        }

        auto UnregisterGraphicLoadingHandler
        (
            const ttstr&                      name,
            tTVPGraphicLoadingHandler      loading,
            tTVPGraphicHeaderLoadingHandler header,
            tTVPGraphicSaveHandler            save,
            tTVPGraphicAcceptSaveHandler    accept,
            void*                       formatdata
        ) noexcept -> bool
        {
            Graphic::HandlerType handler
            {
                    .IsPlugin      = false,
                    .Extension     = name,
                    .LoadHandler   = loading,
                    .HeaderHandler = header,
                    .SaveHandler   = save,
                    .AcceptHandler = accept,
                    .FormatData    = formatdata
            };
            return k2a::tvp::graphic::unregister_loading_handler(handler);
        }

        auto ClearGraphicCache() noexcept -> bool
        {
            return k2a::tvp::graphic::clear_cache();
        }
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