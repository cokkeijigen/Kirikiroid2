#pragma once
#include <tjs.h>
#include <k2atvp_graphic.hpp>
#include <k2atvp_storage.hpp>

namespace kr2android::tvp
{
    struct project_dir
    {
        static auto get() noexcept -> const TJS::ttstr*;
    };

    struct graphic_type
    {
        static auto get() noexcept -> graphic::GraphicType*;
    };

    struct storage_media_manager
    {
        static auto get() noexcept -> storage::StorageMediaManager*;
    };

    extern auto       add_auto_path(const ttstr& path) noexcept -> bool;
    extern auto    remove_auto_path(const ttstr& path) noexcept -> bool;
    extern auto     get_placed_path(const ttstr& path) noexcept -> std::optional<ttstr>;
    extern auto is_existent_storage(const ttstr& path) noexcept -> std::optional<bool>;

    extern auto get_game_path () noexcept -> std::optional<ttstr>;
    extern auto get_app_path  () noexcept -> std::optional<ttstr>;
    extern auto get_local_name(ttstr& name) noexcept -> std::optional<ttstr>;

    extern auto  extract_storage_ext(const ttstr& name) noexcept -> ttstr;
    extern auto extract_storage_name(const ttstr& name) noexcept -> ttstr;
    extern auto extract_storage_path(const ttstr& name) noexcept -> ttstr;
    extern auto     chop_storage_ext(const ttstr& name) noexcept -> ttstr;

    extern auto   register_storage_media(storage::iStorageMedia* media) noexcept -> bool;
    extern auto unregister_storage_media(storage::iStorageMedia* media) noexcept -> bool;

    extern auto              is_existent_storage_no_search(const ttstr& name) noexcept -> std::optional<bool>;
    extern auto is_existent_storage_no_search_no_normalize(const ttstr& name) noexcept -> std::optional<bool>;

    extern auto   clear_storage_caches() noexcept -> bool;
    extern auto  set_current_directory(const ttstr& directory) noexcept -> bool;
    extern auto normalize_storage_name(const ttstr&      name) noexcept -> std::optional<ttstr>;

    extern auto    create_text_stream_for_read(const ttstr& name, const ttstr& modestr) noexcept -> iTJSTextReadStream*;
    extern auto   create_text_stream_for_write(const ttstr& name, const ttstr& modestr) noexcept -> iTJSTextWriteStream*;
    extern auto  create_binary_stream_for_read(const ttstr& name, const ttstr& modestr) noexcept -> tTJSBinaryStream*;
    extern auto create_binary_stream_for_write(const ttstr& name, const ttstr& modestr) noexcept -> tTJSBinaryStream*;

    extern auto get_default_read_encoding() noexcept -> const tjs_char*;
    extern auto set_default_read_encoding(const ttstr& name) noexcept -> bool;

    extern auto set_command_line(const tjs_char* name, const ttstr& value) -> bool;
    extern auto get_command_line(const tjs_char* name, tTJSVariant* value) -> std::optional<bool>;

    extern auto   get_tick_count() noexcept -> std::optional<tjs_uint64>;
}