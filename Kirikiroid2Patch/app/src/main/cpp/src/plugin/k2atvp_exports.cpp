#include <algorithm>
#include <ranges>
#include <stdint.h>
#include <kr2android.hpp>
#include <kr2rva.hpp>
#include <funcutils.hpp>

namespace kr2android
{

    struct tvpaddr
    {
        uint64_t  hash;
        uniptr_t  addr;
    };

    template<size_t n>
    struct tvpaddr_list
    {
        std::unique_ptr<tvpaddr[]> data;
        static inline constexpr const size_t count{ n };

        template<class ...T>
        requires (std::is_same_v<T, tvpaddr> && ...)
        tvpaddr_list(T... args) : data{ new tvpaddr[n]{ std::forward<T>(args)... }  }
        {
            std::ranges::sort(std::views::counted(this->data.get(), n), std::less{}, &tvpaddr::hash);
        }

        inline auto query(const uint64_t hash) const noexcept -> void*
        {
            const std::span<tvpaddr> list{ this->data.get(), n };
            const auto it{ std::ranges::lower_bound(list, hash, std::less{}, &tvpaddr::hash) };
            if (it != list.end() && it->hash == hash)
            {
                return it->addr.ptr;
            }
            return nullptr;
        }

    };

    template<class ...T>
    tvpaddr_list(T...) -> tvpaddr_list<sizeof...(T)>;

    using namespace kr2android::symbol_hash;
    static const tvpaddr_list exports
    {
        tvpaddr
        {
            .hash = "TJSString::ProjectDir"_hash,
            .addr = TVP::RVA::TJSString::ProjectDir
        },
        tvpaddr
        {
            .hash = "TJSString::NativeProjectDir"_hash,
            .addr = TVP::RVA::TJSString::NativeProjectDir
        },
        tvpaddr
        {
            .hash = "system::base_path(void)->[ttstr]"_hash,
            .addr = k2a::tvp::system::base_path
        },
        tvpaddr
        {
            .hash = "system::app_path(void)->[ttstr]"_hash,
            .addr = k2a::tvp::system::base_path
        },
        tvpaddr
        {
            .hash = "system::base_path(void)->[ttstr]"_hash,
            .addr = k2a::tvp::system::base_path
        },
        tvpaddr
        {
            .hash = "storage::register_media(iStorageMedia*)->[bool]"_hash,
            .addr = k2a::tvp::storage::register_media
        },
        tvpaddr
        {
            .hash = "storage::unregister_media(iStorageMedia*)->[bool]"_hash,
            .addr = k2a::tvp::storage::unregister_media
        },
        tvpaddr
        {
            .hash = "storage::clear_caches(void)->[bool]"_hash,
            .addr = k2a::tvp::storage::clear_caches
        },
        tvpaddr
        {
            .hash = "storage::normalize_name(const ttstr&)->[std::optional<ttstr>]"_hash,
            .addr = k2a::tvp::storage::normalize_name
        },
        tvpaddr
        {
            .hash = "storage::is_existent_no_search(const ttstr&)->[std::optional<bool>]"_hash,
            .addr = k2a::tvp::storage::is_existent_no_search
        },
        tvpaddr
        {
            .hash = "storage::is_existent_no_search_no_normalize(const ttstr&)->[std::optional<bool>]"_hash,
            .addr = k2a::tvp::storage::is_existent_no_search_no_normalize
        },
        tvpaddr
        {
            .hash = "storage::set_current_directory(const ttstr&)->[bool]"_hash,
            .addr = k2a::tvp::storage::set_current_directory
        },
        tvpaddr
        {
            .hash = "storage::add_auto_path(const ttstr&)->[bool]"_hash,
            .addr = k2a::tvp::storage::add_auto_path
        },
        tvpaddr
        {
            .hash = "storage::remove_auto_path(const ttstr&)->[bool]"_hash,
            .addr = k2a::tvp::storage::remove_auto_path
        },
        tvpaddr
        {
            .hash = "storage::get_placed_path(const ttstr&)->[std::optional<ttstr>]"_hash,
            .addr = k2a::tvp::storage::get_placed_path
        },
        tvpaddr
        {
            .hash = "storage::is_existent(const ttstr&)->[std::optional<bool>]"_hash,
            .addr = k2a::tvp::storage::is_existent
        },
        tvpaddr
        {
            .hash = "storage::get_local_name(const ttstr&)->[std::optional<ttstr>]"_hash,
            .addr = k2a::tvp::storage::get_local_name
        },
        tvpaddr
        {
            .hash = "storage::extract_ext(const ttstr&)->[ttstr]"_hash,
            .addr = k2a::tvp::storage::extract_ext
        },
        tvpaddr
        {
            .hash = "storage::extract_name(const ttstr&)->[ttstr]"_hash,
            .addr = k2a::tvp::storage::extract_name
        },
        tvpaddr
        {
            .hash = "storage::extract_path(const ttstr&)->[ttstr]"_hash,
            .addr = k2a::tvp::storage::extract_path
        },
        tvpaddr
        {
            .hash = "storage::chop_ext(const ttstr&)->[ttstr]"_hash,
            .addr = k2a::tvp::storage::chop_ext
        },
        tvpaddr
        {
            .hash = "xp3::get_content_filter(void)->[content_filter_t]"_hash,
            .addr = k2a::tvp::xp3::get_content_filter
        },
        tvpaddr
        {
            .hash = "xp3::get_extraction_filter(void)->[extraction_filter_t]"_hash,
            .addr = k2a::tvp::xp3::get_extraction_filter
        },
        tvpaddr
        {
            .hash = "xp3::set_content_filter(extraction_filter_t)->[bool]"_hash,
            .addr = k2a::tvp::xp3::set_content_filter
        },
        tvpaddr
        {
            .hash = "xp3::set_extraction_filter(extraction_filter_t)->[bool]"_hash,
            .addr = k2a::tvp::xp3::set_extraction_filter
        },
        tvpaddr
        {
            .hash = "xp3::set_extraction_filter(extraction_filter_t)->[bool]"_hash,
            .addr = k2a::tvp::xp3::set_extraction_filter
        },
        tvpaddr
        {
            .hash = "graphic::class[NativeBaseBitmap]::GetWidth(void)->[tjs_uint]"_hash,
            .addr = &k2a::tvp::graphic::NativeBaseBitmap::GetWidth
        },
        tvpaddr
        {
            .hash = "graphic::class[NativeBaseBitmap]::GetHeight(void)->[tjs_uint]"_hash,
            .addr = &k2a::tvp::graphic::NativeBaseBitmap::GetHeight
        },
        tvpaddr
        {
            .hash = "graphic::class[NativeBaseBitmap]::GetScanLine(tjs_uint)->[const void*]"_hash,
            .addr = &k2a::tvp::graphic::NativeBaseBitmap::GetScanLine
        },
        tvpaddr
        {
            .hash = "graphic::register_loading_handler(const HandlerType&)->[bool]"_hash,
            .addr = k2a::tvp::graphic::register_loading_handler
        },
        tvpaddr
        {
            .hash = "graphic::unregister_loading_handler(const HandlerType&)->[bool]"_hash,
            .addr = k2a::tvp::graphic::unregister_loading_handler
        },
        tvpaddr
        {
            .hash = "graphic::clear_cache(void)->[bool]"_hash,
            .addr = k2a::tvp::graphic::clear_cache
        },
        tvpaddr
        {
            .hash = "stream::create_text_for_read(const ttstr&,const ttstr&)->[iTJSTextReadStream*]"_hash,
            .addr = k2a::tvp::stream::create_text_for_read
        },
        tvpaddr
        {
            .hash = "stream::create_text_for_write(const ttstr&,const ttstr&)->[iTJSTextWriteStream*]"_hash,
            .addr = k2a::tvp::stream::create_text_for_write
        },
        tvpaddr
        {
            .hash = "stream::create_binary_for_read(const ttstr&,const ttstr&)->[tTJSBinaryStream*]"_hash,
            .addr = k2a::tvp::stream::create_binary_for_read
        },
        tvpaddr
        {
            .hash = "stream::create_binary_for_write(const ttstr&,const ttstr&)->[tTJSBinaryStream*]"_hash,
            .addr = k2a::tvp::stream::create_binary_for_write
        },
        tvpaddr
        {
            .hash = "scripts::get_dispatch(bool)->[iTJSDispatch2*]"_hash,
            .addr = k2a::tvp::scripts::get_dispatch
        },
        tvpaddr
        {
            .hash = "scripts::dump_engine(std::string_view,bool)->[bool]"_hash,
            .addr = func::of<std::string_view, bool>(k2a::tvp::scripts::dump_engine)
        },
        tvpaddr
        {
            .hash = "scripts::execute(const ttstr&,iTJSDispatch2*,tTJSVariant*)->[bool]"_hash,
            .addr = func::of<const ttstr&, iTJSDispatch2*, tTJSVariant*>(k2a::tvp::scripts::execute)
        },
        tvpaddr
        {
            .hash = "scripts::execute(const ttstr&,const ttstr&,tjs_int,iTJSDispatch2*,tTJSVariant*)->[bool]"_hash,
            .addr = func::of<const ttstr&, const ttstr&, tjs_int, iTJSDispatch2*, tTJSVariant*>(k2a::tvp::scripts::execute)
        },
        tvpaddr
        {
            .hash = "scripts::execexpr(const ttstr&,iTJSDispatch2*,tTJSVariant*)->[bool]"_hash,
            .addr = func::of<const ttstr&, iTJSDispatch2*, tTJSVariant*>(k2a::tvp::scripts::execexpr)
        },
        tvpaddr
        {
            .hash = "scripts::execexpr(const ttstr&,const ttstr&,tjs_int,iTJSDispatch2*,tTJSVariant*)->[bool]"_hash,
            .addr = func::of<const ttstr&, const ttstr&, tjs_int, iTJSDispatch2*, tTJSVariant*>(k2a::tvp::scripts::execexpr)
        },
        tvpaddr
        {
            .hash = "scripts::load(const ttstr&,iTJSDispatch2*,tTJSVariant*,bool,consttjs_char*)->[bool]"_hash,
            .addr = func::of<const ttstr&, iTJSDispatch2*, tTJSVariant*, bool, const tjs_char*>(k2a::tvp::scripts::load)
        },
        tvpaddr
        {
            .hash = "scripts::loadbytes(const tjs_uint8*,size_t,iTJSDispatch2*,tTJSVariant*,const tjs_char*)->[bool]"_hash,
            .addr = func::of<const tjs_uint8*, size_t, iTJSDispatch2*, tTJSVariant*, const tjs_char*>(k2a::tvp::scripts::loadbytes)
        },
        tvpaddr
        {
            .hash = "scripts::get_text_encoding(void)->[std::optional<ttstr>]"_hash,
            .addr = k2a::tvp::scripts::get_text_encoding
        },
        tvpaddr
        {
            .hash = "scripts::set_text_encoding(const ttstr&)->[bool]"_hash,
            .addr = k2a::tvp::scripts::set_text_encoding
        },
        tvpaddr
        {
            .hash = "events::post(const event&)->[bool]"_hash,
            .addr = k2a::tvp::events::post
        },
        tvpaddr
        {
            .hash = "events::in_queue(const uniref_event)->[std::optional<bool>]"_hash,
            .addr = k2a::tvp::events::in_queue
        },
        tvpaddr
        {
            .hash = "events::get_count(const uniref_event)->[std::optional<tjs_int>]"_hash,
            .addr = k2a::tvp::events::get_count
        },
        tvpaddr
        {
            .hash = "events::cancel(const uniref_event)->[std::optional<tjs_int>]"_hash,
            .addr = k2a::tvp::events::cancel
        },
        tvpaddr
        {
            .hash = "events::cancel_tag(iTJSDispatch2*,iTJSDispatch2*,tjs_uint32)->[std::optional<tjs_int>]"_hash,
            .addr = k2a::tvp::events::cancel_tag
        },
        tvpaddr
        {
            .hash = "events::cancel_source(iTJSDispatch2*)->[std::optional<tjs_int>]"_hash,
            .addr = k2a::tvp::events::cancel_source
        },
        tvpaddr
        {
            .hash = "events::create_object(const tjs_char*,iTJSDispatch2*,iTJSDispatch2*)->[std::optional<iTJSDispatch2*>]"_hash,
            .addr = k2a::tvp::events::create_object
        },
        tvpaddr
        {
            .hash = "events::add_continuous_hook(const continuous_callback*)->[bool]"_hash,
            .addr = k2a::tvp::events::add_continuous_hook
        },
        tvpaddr
        {
            .hash = "events::remove_continuous_hook(const continuous_callback*)->[bool]"_hash,
            .addr = k2a::tvp::events::remove_continuous_hook
        },
        tvpaddr
        {
            .hash = "events::add_compact_hook(const compact_callback*)->[bool]"_hash,
            .addr = k2a::tvp::events::add_compact_hook
        },
        tvpaddr
        {
            .hash = "events::remove_compact_hook(const compact_callback*)->[bool]"_hash,
            .addr = k2a::tvp::events::remove_compact_hook
        },
        tvpaddr
        {
            .hash = "events::set_system_disabled_state(bool)->[bool]"_hash,
            .addr = k2a::tvp::events::set_system_disabled_state
        },
        tvpaddr
        {
            .hash = "events::get_system_disabled_state(void)->[std::optional<bool>]"_hash,
            .addr = k2a::tvp::events::get_system_disabled_state
        },
        tvpaddr
        {
            .hash = "sound::pcm::to_16bits(tjs_int16*,const void*,tjs_int,tjs_int,tjs_int,bool,tjs_int,bool)->[bool]"_hash,
            .addr = func::of<tjs_int16*, const void*, tjs_int, tjs_int, tjs_int, bool, tjs_int, bool>(k2a::tvp::sound::pcm::to_16bits)
        },
        tvpaddr
        {
            .hash = "sound::pcm::to_float(float*,const void*,tjs_int,tjs_int,tjs_int,bool,tjs_int)->[bool]"_hash,
            .addr = func::of<float*, const void*, tjs_int, tjs_int, tjs_int, bool, tjs_int>(k2a::tvp::sound::pcm::to_float)
        },
        tvpaddr
        {
            .hash = "add_log(const ttstr&, bool)->[bool]"_hash,
            .addr = k2a::tvp::add_log
        },
        tvpaddr
        {
            .hash = "inputbox(ttstr&,const ttstr&,const ttstr&,const std::vector<ttstr>&)->[std::optional<int>]"_hash,
            .addr = func::of<ttstr&, const ttstr&, const ttstr&, const std::vector<ttstr>&>(k2a::tvp::inputbox)
        },
        tvpaddr
        {
            .hash = "messagebox(const ttstr&,const ttstr&,const std::vector<ttstr>&)->[std::optional<int>]"_hash,
            .addr = func::of<const ttstr&, const ttstr&, const std::vector<ttstr>&>(k2a::tvp::messagebox)
        },

        tvpaddr
        {
            .hash = "get_random_bits128(void*)->[bool]"_hash,
            .addr = k2a::tvp::get_random_bits128
        },
        tvpaddr
        {
            .hash = "set_command_line(const tjs_char*,const ttstr&)->[bool]"_hash,
            .addr = k2a::tvp::set_command_line
        },
        tvpaddr
        {
            .hash = "get_command_line(const tjs_char*,tTJSVariant*)->[std::optional<bool>]"_hash,
            .addr = k2a::tvp::get_command_line
        },
        tvpaddr
        {
            .hash = "get_tick_count(void)->[std::optional<tjs_uint64>]"_hash,
            .addr = k2a::tvp::get_tick_count
        },
    };

    extern "C"
    {
        #define symbol(v) __attribute__((visibility(v)))

        symbol("hidden") extern void* __executable_start;
        symbol("hidden") extern void* _end;

        inline auto is_internal_address(uniptr_t ptr) noexcept -> bool
        {
            const uniptr_t begin{ &__executable_start }, end{ &_end };
            return bool{ ptr.uintptr >= begin.uintptr && ptr.uintptr < end.uintptr };
        }

        symbol("default") auto k2a_query(uint64_t hash) -> void*
        {
            uniptr_t ptr{ exports.query(hash) };
            if(!is_internal_address(ptr))
            {
                ptr = k2a::cast_ptr(ptr.uintptr);
            }
            return ptr.ptr;
        }
    }

}