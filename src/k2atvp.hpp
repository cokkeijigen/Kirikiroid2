#pragma once
#include <tjs.h>
#include <k2atvp_graphic.hpp>
#include <k2atvp_storage.hpp>

namespace kr2android::tvp
{

    namespace project
    {
        extern auto get_dir() noexcept -> const ttstr*;
        extern auto get_native_dir() noexcept -> const ttstr*;
    }

    namespace storage
    {
        struct media_manager
        {
            static auto get() noexcept -> storage::StorageMediaManager*;
        };

        extern auto   register_media(storage::iStorageMedia* media) noexcept -> bool;
        extern auto unregister_media(storage::iStorageMedia* media) noexcept -> bool;

        extern auto   clear_caches() noexcept -> bool;
        extern auto normalize_name(const ttstr& name) noexcept -> std::optional<ttstr>;

        extern auto              is_existent_no_search(const ttstr& name) noexcept -> std::optional<bool>;
        extern auto is_existent_no_search_no_normalize(const ttstr& name) noexcept -> std::optional<bool>;

        extern auto  set_current_directory(const ttstr& directory) noexcept -> bool;

        extern auto    add_auto_path(const ttstr& path) noexcept -> bool;
        extern auto remove_auto_path(const ttstr& path) noexcept -> bool;
        extern auto  get_placed_path(const ttstr& path) noexcept -> std::optional<ttstr>;
        extern auto      is_existent(const ttstr& path) noexcept -> std::optional<bool>;

        extern auto get_local_name(ttstr& name) noexcept -> std::optional<ttstr>;

        extern auto  extract_ext(const ttstr& name) noexcept -> ttstr;
        extern auto extract_name(const ttstr& name) noexcept -> ttstr;
        extern auto extract_path(const ttstr& name) noexcept -> ttstr;
        extern auto     chop_ext(const ttstr& name) noexcept -> ttstr;
    }

    namespace xp3
    {
        #pragma pack(push, 4)
        struct ExtractionFilterInfo
        {
            const tjs_uint SizeOfSelf{ sizeof(ExtractionFilterInfo) }; // structure size of ExtractionFilterInfo itself
            const tjs_uint64   Offset; // offset of the buffer data in uncompressed stream position
            void*              Buffer; // target data buffer
            const tjs_uint BufferSize; // buffer size in bytes pointed by "Buffer"
            const tjs_uint32 FileHash; // hash value of the file (since inteface v2)
            const ttstr&     FileName;
        };
        #pragma pack(pop)

        using ExtractionFilterType = void   (*)(ExtractionFilterInfo *info, tTJSVariant *ctx);
        using    ContentFilterType = tjs_int(*)(const ttstr &filepath, const ttstr &archivename, tjs_uint64 filesize, tTJSVariant *ctx);
        using extraction_filter_t  = ExtractionFilterType;
        using    content_filter_t  = ContentFilterType;

        auto    get_content_filter() noexcept -> content_filter_t;
        auto get_extraction_filter() noexcept -> extraction_filter_t;

        auto    set_content_filter(content_filter_t    filter) noexcept -> bool;
        auto set_extraction_filter(extraction_filter_t filter) noexcept -> bool;
    }

    namespace graphic
    {
        struct type
        {
            static auto get() noexcept -> graphic::GraphicType*;
        };
        extern auto   register_loading_handler(const graphic::HandlerType& handler) noexcept -> bool;
        extern auto unregister_loading_handler(const graphic::HandlerType& handler) noexcept -> bool;
        extern auto clear_cache() noexcept -> bool;
    }

    namespace stream
    {
        extern auto    create_text_for_read(const ttstr& name, const ttstr& modestr) noexcept -> iTJSTextReadStream*;
        extern auto   create_text_for_write(const ttstr& name, const ttstr& modestr) noexcept -> iTJSTextWriteStream*;
        extern auto  create_binary_for_read(const ttstr& name, const ttstr& modestr) noexcept -> tTJSBinaryStream*;
        extern auto create_binary_for_write(const ttstr& name, const ttstr& modestr) noexcept -> tTJSBinaryStream*;
    }

    namespace script
    {
        extern auto   get_engine() noexcept -> tTJS*;
        extern auto get_dispatch() noexcept -> iTJSDispatch2*;
        extern auto  dump_engine() noexcept -> bool;

        extern auto execute(const ttstr& content, tTJSVariant* result) noexcept -> bool;
        extern auto execute(const ttstr& content, iTJSDispatch2* context, tTJSVariant* result) noexcept -> bool;
        extern auto execute(const ttstr& content, const ttstr& name, tjs_int lineofs, tTJSVariant* result) noexcept -> bool;
        extern auto execute(const ttstr& content, const ttstr& name, tjs_int lineofs, iTJSDispatch2* context, tTJSVariant* result) noexcept -> bool;

        extern auto execexpr(const ttstr& content, tTJSVariant* result) noexcept -> bool;
        extern auto execexpr(const ttstr& content, iTJSDispatch2* context, tTJSVariant* result) noexcept -> bool;
        extern auto execexpr(const ttstr& content, const ttstr& name, tjs_int lineofs, tTJSVariant* result) noexcept -> bool;
        extern auto execexpr(const ttstr& content, const ttstr& name, tjs_int lineofs, iTJSDispatch2* context, tTJSVariant* result) noexcept -> bool;

        extern auto load(const ttstr& name, tTJSVariant* result, bool isexpression, const tjs_char* modestr) noexcept -> bool;
        extern auto load(const ttstr& name, iTJSDispatch2* context, tTJSVariant* result, bool isexpression, const tjs_char* modestr) noexcept -> bool;
        extern auto loadbytes(const tjs_uint8* content, size_t length, iTJSDispatch2* context, tTJSVariant* result, const tjs_char* name) noexcept -> bool;

    }

    namespace scripts
    {
        extern auto get_text_encoding() noexcept -> const tjs_char*;
        extern auto set_text_encoding(const ttstr& name) noexcept -> bool;
    }

    extern auto get_game_path() noexcept -> std::optional<ttstr>;
    extern auto get_app_path () noexcept -> std::optional<ttstr>;


    extern auto set_command_line(const tjs_char* name, const ttstr& value) -> bool;
    extern auto get_command_line(const tjs_char* name, tTJSVariant* value) -> std::optional<bool>;

    extern auto   get_tick_count() noexcept -> std::optional<tjs_uint64>;
}