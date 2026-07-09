#include <tjsObject.h>
#include <TJSDumpFileOutput.hpp>
#include <filesystem>
#include <fstream>
#include <kr2android.hpp>
#include <k2atvp.hpp>
#include <xstr.hpp>

namespace kr2android::tvp
{
    using namespace kr2android::symbol_hash;

    namespace system
    {
        [[gnu::noinline]]
        auto get_dir() noexcept -> const ttstr*
        {
            static ttstr* _ptr{};
            if(_ptr == nullptr)
            {
                _ptr = k2a::plugin.query<TJS::ttstr*>("TJSString::ProjectDir"_hash);
            }
            return _ptr;
        }

        [[gnu::noinline]]
        auto get_native_dir() noexcept -> const ttstr*
        {
            static ttstr* _ptr{};
            if(_ptr == nullptr)
            {
                _ptr = k2a::plugin.query<TJS::ttstr*>("TJSString::NativeProjectDir"_hash);
            }
            return _ptr;
        }

        [[gnu::noinline]]
        auto app_path() noexcept -> ttstr
        {
            const TJS::ttstr* dir { system::get_dir() };
            if(dir != nullptr && !dir->IsEmpty())
            {
                return storage::extract_path(*dir);
            }
            else
            {
                const unirawptr_t<decltype(&system::app_path)> call
                {
                    k2a::plugin.query("system::app_path(void)->[ttstr]"_hash)
                };
                if(call.ptr != nullptr)
                {
                    return storage::extract_path(call.raw());
                }
            }
            return ttstr{};
        }

        [[gnu::noinline]]
        auto base_path() noexcept -> ttstr
        {
            const TJS::ttstr* dir { system::get_native_dir() };
            if(dir != nullptr && !dir->IsEmpty())
            {
                return storage::extract_path(*dir);
            }
            else
            {
                const unirawptr_t<decltype(&system::base_path)> call
                {
                    k2a::plugin.query("system::base_path(void)->[ttstr]"_hash)
                };
                if(call.ptr != nullptr)
                {
                    return storage::extract_path(call.raw());
                }
            }
            return ttstr{};
        }

    }

    namespace storage
    {
        [[gnu::noinline]]
        auto register_media(storage::iStorageMedia* media) noexcept -> bool
        {
            static decltype(&register_media) _ptr{};
            if(_ptr == nullptr)
            {
                const uint64_t hash{ "storage::register_media(iStorageMedia*)->[bool]"_hash };
                _ptr = k2a::plugin.query<decltype(_ptr)>(hash);
            }
            return bool{ _ptr != nullptr ? _ptr(media) : false };
        }

        [[gnu::noinline]]
        auto unregister_media(storage::iStorageMedia* media) noexcept -> bool
        {
            static decltype(&unregister_media) _ptr{};
            if(_ptr == nullptr)
            {
                const uint64_t hash{ "storage::unregister_media(iStorageMedia*)->[bool]"_hash };
                _ptr = k2a::plugin.query<decltype(_ptr)>(hash);
            }
            return bool{ _ptr != nullptr ? _ptr(media) : false };
        }

        [[gnu::noinline]]
        auto clear_caches() noexcept -> bool
        {
            static decltype(&clear_caches) _ptr{};
            if(_ptr == nullptr)
            {
                const uint64_t hash{ "storage::clear_caches(void)->[bool]"_hash };
                _ptr = k2a::plugin.query<decltype(_ptr)>(hash);
            }
            return bool{ _ptr ? _ptr() : false };
        }

        [[gnu::noinline]]
        auto normalize_name(const ttstr& name) noexcept -> std::optional<ttstr>
        {
            static decltype(&normalize_name) _ptr{};
            if(_ptr == nullptr)
            {
                const uint64_t hash{ "storage::normalize_name(const ttstr&)->[std::optional<ttstr>]"_hash };
                _ptr = k2a::plugin.query<decltype(_ptr)>(hash);
            }
            return std::optional<ttstr>{ _ptr != nullptr ?  _ptr(name) : std::nullopt };
        }

        [[gnu::noinline]]
        auto is_existent_no_search(const ttstr& name) noexcept -> std::optional<bool>
        {
            static decltype(&is_existent_no_search) _ptr{};
            if(_ptr == nullptr)
            {
                const uint64_t hash{ "storage::is_existent_no_search(const ttstr&)->[std::optional<bool>]"_hash };
                _ptr = k2a::plugin.query<decltype(_ptr)>(hash);
            }
            return std::optional<bool>{ _ptr != nullptr ?  _ptr(name) : std::nullopt };
        }

        [[gnu::noinline]]
        auto is_existent_no_search_no_normalize(const ttstr& name) noexcept -> std::optional<bool>
        {
            static decltype(&is_existent_no_search_no_normalize) _ptr{};
            if(_ptr == nullptr)
            {
                const uint64_t hash{ "storage::is_existent_no_search_no_normalize(const ttstr&)->[std::optional<bool>]"_hash };
                _ptr = k2a::plugin.query<decltype(_ptr)>(hash);
            }
            return std::optional<bool>{ _ptr != nullptr ?  _ptr(name) : std::nullopt };
        }

        [[gnu::noinline]]
        auto set_current_directory(const ttstr& directory) noexcept -> bool
        {
            static decltype(&set_current_directory) _ptr{};
            if(_ptr == nullptr)
            {
                const uint64_t hash{ "storage::set_current_directory(const ttstr&)->[bool]"_hash };
                _ptr = k2a::plugin.query<decltype(_ptr)>(hash);
            }
            return bool{ _ptr != nullptr ? _ptr(directory) : false };
        }

        [[gnu::noinline]]
        auto add_auto_path(const ttstr& path) noexcept -> bool
        {
            static decltype(&add_auto_path) _ptr{};
            if(_ptr == nullptr)
            {
                const uint64_t hash{ "storage::add_auto_path(const ttstr&)->[bool]"_hash };
                _ptr = k2a::plugin.query<decltype(_ptr)>(hash);
            }
            return bool{ _ptr ? _ptr(path) : false };
        }

        [[gnu::noinline]]
        auto remove_auto_path(const ttstr& path) noexcept -> bool
        {
            static decltype(&remove_auto_path) _ptr{};
            if(_ptr == nullptr)
            {
                const uint64_t hash{ "storage::remove_auto_path(const ttstr&)->[bool]"_hash };
                _ptr = k2a::plugin.query<decltype(_ptr)>(hash);
            }
            return bool{ _ptr ? _ptr(path) : false };
        }

        [[gnu::noinline]]
        auto get_placed_path(const ttstr& path) noexcept -> std::optional<ttstr>
        {
            static decltype(&get_placed_path) _ptr{};
            if(_ptr != nullptr)
            {
                const uint64_t hash{ "storage::get_placed_path(const ttstr&)->[std::optional<ttstr>]"_hash };
                _ptr = k2a::plugin.query<decltype(_ptr)>(hash);
            }
            return std::optional<ttstr>{ _ptr != nullptr ? _ptr(path) : std::nullopt };
        }

        [[gnu::noinline]]
        auto is_existent(const ttstr& path) noexcept -> std::optional<bool>
        {
            std::optional<ttstr> _path{ storage::get_placed_path(path) };
            if(!_path.has_value())
            {
                const uint64_t hash{ "storage::is_existent(const ttstr&)->[std::optional<bool>]"_hash };
                const auto    call { k2a::plugin.query<decltype(&storage::is_existent)>(hash) };
                if(call != nullptr)
                {
                    _path = call(path);
                }
            }
            if(_path.has_value())
            {
                return !_path->IsEmpty();
            }
            return std::nullopt;
        }

        [[gnu::noinline]]
        auto get_local_name(const ttstr& name) noexcept -> std::optional<ttstr>
        {
            static decltype(&get_local_name) _ptr{};
            if(_ptr == nullptr)
            {
                const uint64_t hash{ "storage::get_local_name(const ttstr&)->[std::optional<ttstr>]"_hash };
                _ptr = k2a::plugin.query<decltype(_ptr)>(hash);
            }
            return std::optional<ttstr>{ _ptr != nullptr ? _ptr(name) : std::nullopt };
        }

        [[gnu::noinline]]
        auto extract_ext(const ttstr& name) noexcept -> ttstr
        {
            if(name.IsEmpty())
            {
                return name;
            }

            std::u16string_view str{ name.c_str(), static_cast<size_t>(name.GetLen()) };
            const size_t    sep_pos{ str.find_last_of(u"\\/>") };
            const size_t    dot_pos{ str.find_last_of(u".")    };

            if (dot_pos != std::u16string_view::npos && (sep_pos == std::u16string_view::npos || dot_pos > sep_pos))
            {
                const auto ext_len{ static_cast<tjs_int>(str.size() - dot_pos) };
                return ttstr{ name.c_str() + dot_pos, ext_len };
            }
            return ttstr{};
        }

        [[gnu::noinline]]
        auto extract_name(const ttstr& name) noexcept -> ttstr
        {
            if (name.IsEmpty())
            {
                return name;
            }

            std::u16string_view str{ name.c_str(), static_cast<size_t>(name.GetLen()) };
            const size_t    sep_pos{ str.find_last_of(u"\\/>") };

            if (sep_pos == std::u16string_view::npos)
            {
                return name;
            }

            const size_t begin{ sep_pos + 1 },  length{ str.length() - begin };
            return ttstr{ name.c_str() + begin, static_cast<tjs_int>(length) };
        }

        [[gnu::noinline]]
        auto extract_path(const ttstr& name) noexcept -> ttstr
        {
            if (name.IsEmpty())
            {
                return name;
            }

            size_t begin{}, length{};
            std::u16string_view str{ name.c_str(), static_cast<size_t>(name.length()) };

            size_t offset{ str.find_last_of(u"\\/>") };
            if(offset != std::u16string_view::npos)
            {
                str = str.substr(0, offset);
            }

            length = str.end() - str.begin();
            return ttstr{ name.c_str() + begin, static_cast<tjs_int>(length) };
        }

        [[gnu::noinline]]
        auto chop_ext(const ttstr& name) noexcept -> ttstr
        {
            if (name.IsEmpty())
            {
                return name;
            }

            std::u16string_view str{ name.c_str(), static_cast<size_t>(name.GetLen()) };
            const size_t    sep_pos{ str.find_last_of(u"\\/>") };
            const size_t    dot_pos{ str.find_last_of(u".")    };

            if (dot_pos != std::u16string_view::npos && (sep_pos == std::u16string_view::npos || dot_pos > sep_pos))
            {
                return ttstr{ name.c_str(), static_cast<tjs_int>(dot_pos) };
            }
            return name;
        }
    }

    namespace xp3
    {

        [[gnu::noinline]]
        auto get_content_filter() noexcept -> content_filter_t
        {
            static decltype(&get_content_filter) _ptr{};
            if(_ptr == nullptr)
            {
                const uint64_t hash{ "xp3::get_content_filter(void)->[content_filter_t]"_hash };
                _ptr = k2a::plugin.query<decltype(_ptr)>(hash);
            }
            return content_filter_t{ _ptr != nullptr ? _ptr() : nullptr };
        }

        [[gnu::noinline]]
        auto get_extraction_filter() noexcept -> extraction_filter_t
        {
            static decltype(&get_extraction_filter) _ptr{};
            if(_ptr == nullptr)
            {
                const uint64_t hash{ "xp3::get_extraction_filter(void)->[extraction_filter_t]"_hash };
                _ptr = k2a::plugin.query<decltype(_ptr)>(hash);
            }
            return extraction_filter_t{ _ptr != nullptr ? _ptr() : nullptr };
        }

        [[gnu::noinline]]
        auto set_content_filter(content_filter_t filter) noexcept -> bool
        {
            static decltype(&set_content_filter) _ptr{};
            if(_ptr == nullptr)
            {
                const uint64_t hash{ "xp3::set_content_filter(content_filter_t)->[bool]"_hash };
                _ptr = k2a::plugin.query<decltype(_ptr)>(hash);
            }
            return bool{ _ptr != nullptr ? _ptr(filter) : false };
        }

        [[gnu::noinline]]
        auto set_extraction_filter(extraction_filter_t filter) noexcept -> bool
        {
            static decltype(&set_extraction_filter) _ptr{};
            if(_ptr == nullptr)
            {
                const uint64_t hash{ "xp3::set_extraction_filter(extraction_filter_t)->[bool]"_hash };
                _ptr = k2a::plugin.query<decltype(_ptr)>(hash);
            }
            return bool{ _ptr != nullptr ? _ptr(filter) : false };
        }
    }

    namespace graphic
    {

        [[gnu::noinline]]
        auto NativeBaseBitmap::GetWidth() const noexcept -> tjs_uint
        {
            static decltype(&NativeBaseBitmap::GetWidth) _ptr{};
            if(_ptr != nullptr)
            {
                const uint64_t hash{ "graphic::class[NativeBaseBitmap]::GetWidth(void)->[tjs_uint]"_hash };
                _ptr = k2a::plugin.query<decltype(_ptr)>(hash);
            }

            if(static_cast<const void*>(this) != nullptr && _ptr != nullptr)
            {
                return (this->*_ptr)();
            }
            return 0;
        }

        [[gnu::noinline]]
        auto NativeBaseBitmap::GetHeight() const noexcept -> tjs_uint
        {
            static decltype(&NativeBaseBitmap::GetHeight) _ptr{};
            if(_ptr != nullptr)
            {
                const uint64_t hash{ "graphic::class[NativeBaseBitmap]::GetHeight(void)->[tjs_uint]"_hash };
                _ptr = k2a::plugin.query<decltype(_ptr)>(hash);
            }

            if(static_cast<const void*>(this) != nullptr && _ptr != nullptr)
            {
                return (this->*_ptr)();
            }
            return 0;
        }

        [[gnu::noinline]]
        auto NativeBaseBitmap::GetScanLine(tjs_uint line) const noexcept -> const void*
        {
            static decltype(&NativeBaseBitmap::GetScanLine) _ptr{};
            if(_ptr != nullptr)
            {
                const uint64_t hash{ "graphic::class[NativeBaseBitmap]::GetScanLine(tjs_uint)->[tjs_uint]"_hash };
                _ptr = k2a::plugin.query<decltype(_ptr)>(hash);
            }

            if(static_cast<const void*>(this) != nullptr && _ptr != nullptr)
            {
                return (this->*_ptr)(line);
            }
            return nullptr;
        }

        [[gnu::noinline]]
        auto register_loading_handler(const HandlerType& handler) noexcept -> bool
        {
            static decltype(&register_loading_handler) _ptr{};
            if(_ptr == nullptr)
            {
                const uint64_t hash{ "graphic::register_loading_handler(const HandlerType&)->[bool]"_hash };
                _ptr = k2a::plugin.query<decltype(_ptr)>(hash);
            }
            return bool{ _ptr != nullptr ? _ptr(handler) : false };
        }

        [[gnu::noinline]]
        auto unregister_loading_handler(const HandlerType& handler) noexcept -> bool
        {
            static decltype(&unregister_loading_handler) _ptr{};
            if(_ptr == nullptr)
            {
                const uint64_t hash{ "graphic::unregister_loading_handler(const HandlerType&)->[bool]"_hash };
                _ptr = k2a::plugin.query<decltype(_ptr)>(hash);
            }
            return bool{ _ptr != nullptr ? _ptr(handler) : false };
        }

        [[gnu::noinline]]
        auto clear_cache() noexcept -> bool
        {
            static decltype(&clear_cache) _ptr{};
            if(_ptr == nullptr)
            {
                const uint64_t hash{ "graphic::clear_cache(void)->[bool]"_hash };
                _ptr = k2a::plugin.query<decltype(_ptr)>(hash);
            }
            return bool{ _ptr != nullptr ? _ptr() : false };
        }
    }

    namespace stream
    {

        [[gnu::noinline]]
        auto create_text_for_read(const ttstr& name, const ttstr& modestr) noexcept -> iTJSTextReadStream*
        {
            static decltype(&create_text_for_read) _ptr{};
            if(_ptr == nullptr)
            {
                const uint64_t hash{ "stream::create_text_for_read(const ttstr&,const ttstr&)->[iTJSTextReadStream*]"_hash };
                _ptr = k2a::plugin.query<decltype(_ptr)>(hash);
            }
            return (iTJSTextReadStream*){ _ptr ? _ptr(name, modestr) : nullptr };
        }

        [[gnu::noinline]]
        auto create_text_for_write(const ttstr& name, const ttstr& modestr) noexcept -> iTJSTextWriteStream*
        {
            static decltype(&create_text_for_write) _ptr{};
            if(_ptr == nullptr)
            {
                const uint64_t hash{ "stream::create_text_for_write(const ttstr&,const ttstr&)->[iTJSTextWriteStream*]"_hash };
                _ptr = k2a::plugin.query<decltype(_ptr)>(hash);
            }
            return (iTJSTextWriteStream*){ _ptr ? _ptr(name, modestr) : nullptr };
        }

        [[gnu::noinline]]
        auto create_binary_for_read(const ttstr& name, const ttstr& modestr) noexcept -> tTJSBinaryStream*
        {
            static decltype(&create_binary_for_read) _ptr{};
            if(_ptr == nullptr)
            {
                const uint64_t hash{ "stream::create_binary_for_read(const ttstr&,const ttstr&)->[tTJSBinaryStream*]"_hash };
                _ptr = k2a::plugin.query<decltype(_ptr)>(hash);
            }
            return (tTJSBinaryStream*){ _ptr ? _ptr(name, modestr) : nullptr };
        }

        [[gnu::noinline]]
        auto create_binary_for_write(const ttstr& name, const ttstr& modestr) noexcept -> tTJSBinaryStream*
        {
            static decltype(&create_binary_for_write) _ptr{};
            if(_ptr == nullptr)
            {
                const uint64_t hash{ "stream::create_binary_for_write(const ttstr&,const ttstr&)->[tTJSBinaryStream*]"_hash };
                _ptr = k2a::plugin.query<decltype(_ptr)>(hash);
            }
            return (tTJSBinaryStream*){ _ptr ? _ptr(name, modestr) : nullptr };
        }
    }

    namespace scripts
    {

        [[gnu::noinline]]
        auto get_dispatch(bool addref) noexcept -> iTJSDispatch2*
        {
            static decltype(&get_dispatch) _ptr{};
            if(_ptr == nullptr)
            {
                const uint64_t hash{ "scripts::get_dispatch(bool)->[iTJSDispatch2*]"_hash };
                _ptr = k2a::plugin.query<decltype(_ptr)>(hash);
            }
            return (iTJSDispatch2*){ _ptr != nullptr ? _ptr(addref) : nullptr };
        }

        [[gnu::noinline]]
        auto dump_engine(std::string_view name, bool global) noexcept -> bool
        {
            static bool(*_ptr)(std::string_view, bool){};
            if(_ptr == nullptr)
            {
                const uint64_t hash{ "scripts::dump_engine(std::string_view,bool)->[bool]"_hash };
                _ptr = k2a::plugin.query<decltype(_ptr)>(hash);
            }
            return bool{ _ptr != nullptr ? _ptr(name, global) : false };
        }

        [[gnu::noinline]]
        auto execute(const ttstr& content, iTJSDispatch2* context, tTJSVariant* result) noexcept -> bool
        {
            static bool(*_ptr)(const ttstr&, iTJSDispatch2*, tTJSVariant*){};
            if(_ptr == nullptr)
            {
                const uint64_t hash{ "scripts::execute(const ttstr&,iTJSDispatch2*,tTJSVariant*)->[bool]"_hash };
                _ptr = k2a::plugin.query<decltype(_ptr)>(hash);
            }
            return bool{ _ptr != nullptr ? _ptr(content, context, result) : false };
        }

        [[gnu::noinline]]
        auto execute(const ttstr& content, const ttstr& name, tjs_int lineofs, iTJSDispatch2* context, tTJSVariant* result) noexcept -> bool
        {
            static bool(*_ptr)(const ttstr&, const ttstr&, tjs_int, iTJSDispatch2*, tTJSVariant*){};
            if(_ptr == nullptr)
            {
                const uint64_t hash{ "scripts::execute(const ttstr&,const ttstr&,tjs_int,iTJSDispatch2*,tTJSVariant*)->[bool]"_hash };
                _ptr = k2a::plugin.query<decltype(_ptr)>(hash);
            }
            return bool{ _ptr != nullptr ? _ptr(content, name, lineofs, context, result) : false };
        }

        [[gnu::noinline]]
        auto execexpr(const ttstr& content, iTJSDispatch2* context, tTJSVariant* result) noexcept -> bool
        {
            static bool(*_ptr)(const ttstr&, iTJSDispatch2*, tTJSVariant*){};
            if(_ptr == nullptr)
            {
                const uint64_t hash{ "scripts::execexpr(const ttstr&,iTJSDispatch2*,tTJSVariant*)->[bool]"_hash };
                _ptr = k2a::plugin.query<decltype(_ptr)>(hash);
            }
            return bool{ _ptr != nullptr ? _ptr(content, context, result) : false };
        }

        [[gnu::noinline]]
        auto execexpr(const ttstr& content, const ttstr& name, tjs_int lineofs, iTJSDispatch2* context, tTJSVariant* result) noexcept -> bool
        {
            static bool(*_ptr)(const ttstr&, const ttstr&, tjs_int, iTJSDispatch2*, tTJSVariant*){};
            if(_ptr == nullptr)
            {
                const uint64_t hash{ "scripts::execexpr(const ttstr&,const ttstr&,tjs_int,iTJSDispatch2*,tTJSVariant*)->[bool]"_hash };
                _ptr = k2a::plugin.query<decltype(_ptr)>(hash);
            }
            return bool{ _ptr != nullptr ? _ptr(content, name, lineofs, context, result) : false };
        }

        [[gnu::noinline]]
        auto load(const ttstr& name, iTJSDispatch2* context, tTJSVariant* result, bool isexpression, const tjs_char* modestr) noexcept -> bool
        {
            static bool(*_ptr)(const ttstr&, iTJSDispatch2*, tTJSVariant*, bool, const tjs_char*){};
            if(_ptr == nullptr)
            {
                const uint64_t hash{ "scripts::load(const ttstr&,iTJSDispatch2*,tTJSVariant*,bool,consttjs_char*)->[bool]"_hash };
                _ptr = k2a::plugin.query<decltype(_ptr)>(hash);
            }
            return bool{ _ptr != nullptr ? _ptr(name, context, result, isexpression, modestr) : false };
        }

        [[gnu::noinline]]
        auto loadbytes(const tjs_uint8* content, size_t length, iTJSDispatch2* context, tTJSVariant* result, const tjs_char* name) noexcept -> bool
        {
            static bool(*_ptr)(const tjs_uint8*, size_t, iTJSDispatch2*, tTJSVariant*, const tjs_char*){};
            if(_ptr == nullptr)
            {
                const uint64_t hash{ "scripts::loadbytes(const tjs_uint8*,size_t,iTJSDispatch2*,tTJSVariant*,const tjs_char*)->[bool]"_hash };
                _ptr = k2a::plugin.query<decltype(_ptr)>(hash);
            }
            return bool{ _ptr != nullptr ? _ptr(content, length, context, result, name) : false };
        }

        auto dump_engine(bool global) noexcept -> bool
        {
            return dump_engine({}, global);
        }

        auto dump_engine(std::string_view name) noexcept -> bool
        {
            return dump_engine(name, false);
        }

        auto dump_engine() noexcept -> bool
        {
            return dump_engine({}, false);
        }

        auto execute(const ttstr& content, tTJSVariant* result) noexcept -> bool
        {
            return scripts::execute(content, nullptr, result);
        }

        auto execute(const ttstr& content, const ttstr& name, tjs_int lineofs, tTJSVariant* result) noexcept -> bool
        {
            return scripts::execute(content, name, lineofs, nullptr, result);
        }

        auto execexpr(const ttstr& content, tTJSVariant* result) noexcept -> bool
        {
            return scripts::execexpr(content, nullptr, result);
        }

        auto execexpr(const ttstr& content, const ttstr& name, tjs_int lineofs, tTJSVariant* result) noexcept -> bool
        {
            return scripts::execexpr(content, name, lineofs, nullptr, result);
        }

        auto load(const ttstr& name, tTJSVariant* result, bool isexpression, const tjs_char* modestr) noexcept -> bool
        {
            scripts::load(name, nullptr, result, isexpression, modestr);
        }

        [[gnu::noinline]]
        auto get_text_encoding() noexcept -> std::optional<ttstr>
        {
            static decltype(&get_text_encoding) _ptr{};
            if(_ptr == nullptr)
            {
                const uint64_t hash{ "scripts::get_text_encoding(void)->[std::optional<ttstr>]"_hash };
                _ptr = k2a::plugin.query<decltype(_ptr)>(hash);
            }
            return std::optional<ttstr>{ _ptr != nullptr ?  _ptr() : std::nullopt };
        }

        [[gnu::noinline]]
        auto set_text_encoding(const ttstr& name) noexcept -> bool
        {
            static decltype(&set_text_encoding) _ptr{};
            if(_ptr == nullptr)
            {
                const uint64_t hash{ "scripts::set_text_encoding(const ttstr&)->[bool]"_hash };
                _ptr = k2a::plugin.query<decltype(_ptr)>(hash);
            }
            return bool{ _ptr ? _ptr(name) : false };
        }
    }

    namespace events
    {

        [[gnu::noinline]]
        auto post(const event& e) noexcept -> bool
        {
            static decltype(&post) _ptr{};
            if(_ptr == nullptr)
            {
                const uint64_t hash{ "events::post(const event&)->[bool]"_hash };
                _ptr = k2a::plugin.query<decltype(_ptr)>(hash);
            }
            return bool{ _ptr != nullptr ? _ptr(e) : false };
        }

        [[gnu::noinline]]
        auto in_queue(const uniref_event e) noexcept -> std::optional<bool>
        {
            static decltype(&cancel) _ptr{};
            if(_ptr == nullptr)
            {
                const uint64_t hash{ "events::in_queue(const uniref_event)->[std::optional<bool>]"_hash };
                _ptr = k2a::plugin.query<decltype(_ptr)>(hash);
            }
            return bool{ _ptr != nullptr ? _ptr(e) : false };
        }

        [[gnu::noinline]]
        auto get_count(const uniref_event e) noexcept -> std::optional<tjs_int>
        {
            static decltype(&get_count) _ptr{};
            if(_ptr == nullptr)
            {
                const uint64_t hash{ "events::get_count(const uniref_event)->[std::optional<tjs_int>]"_hash };
                _ptr = k2a::plugin.query<decltype(_ptr)>(hash);
            }
            return std::optional<tjs_int>{ _ptr != nullptr ? _ptr(e) : std::nullopt };
        }

        [[gnu::noinline]]
        auto cancel(const uniref_event e) noexcept-> std::optional<tjs_int>
        {
            static decltype(&cancel) _ptr{};
            if(_ptr == nullptr)
            {
                const uint64_t hash{ "events::cancel(const uniref_event)->[std::optional<tjs_int>]"_hash };
                _ptr = k2a::plugin.query<decltype(_ptr)>(hash);
            }
            return std::optional<tjs_int>{ _ptr != nullptr ? _ptr(e) : false };
        }

        [[gnu::noinline]]
        auto cancel_tag(iTJSDispatch2* source, iTJSDispatch2* target, tjs_uint32 tag) noexcept -> std::optional<tjs_int>
        {
            static decltype(&cancel_tag) _ptr{};
            if(_ptr == nullptr)
            {
                const uint64_t hash{ "events::cancel_tag(iTJSDispatch2*,iTJSDispatch2*,tjs_uint32)->[std::optional<tjs_int>]"_hash };
                _ptr = k2a::plugin.query<decltype(_ptr)>(hash);
            }
            return std::optional<tjs_int>{ _ptr != nullptr ? _ptr(source, target, tag) : std::nullopt };
        }

        [[gnu::noinline]]
        auto cancel_source(iTJSDispatch2* source) noexcept -> std::optional<tjs_int>
        {
            static decltype(&cancel_source) _ptr{};
            if(_ptr == nullptr)
            {
                const uint64_t hash{ "events::cancel_source(iTJSDispatch2*)->[std::optional<tjs_int>]"_hash };
                _ptr = k2a::plugin.query<decltype(_ptr)>(hash);
            }
            return std::optional<tjs_int>{ _ptr != nullptr ? _ptr(source) : std::nullopt };
        }

        [[gnu::noinline]]
        auto create_object(const tjs_char* type, iTJSDispatch2* targthis, iTJSDispatch2* targ) noexcept -> std::optional<iTJSDispatch2*>
        {
            static decltype(&create_object) _ptr{};
            if(_ptr == nullptr)
            {
                const uint64_t hash{ "events::create_object(const tjs_char*,iTJSDispatch2*,iTJSDispatch2*)->[std::optional<iTJSDispatch2*>]"_hash };
                _ptr = k2a::plugin.query<decltype(_ptr)>(hash);
            }
        }

        [[gnu::noinline]]
        auto add_continuous_hook(const continuous_callback* hook) noexcept -> bool
        {
            static decltype(&add_continuous_hook) _ptr{};
            if(_ptr == nullptr)
            {
                const uint64_t hash{ "events::add_continuous_hook(const continuous_callback*)->[bool]"_hash };
                _ptr = k2a::plugin.query<decltype(_ptr)>(hash);
            }
            return bool{ _ptr != nullptr ? _ptr(hook) : false };
        }

        [[gnu::noinline]]
        auto remove_continuous_hook(const continuous_callback* hook) noexcept -> bool
        {
            static decltype(&remove_continuous_hook) _ptr{};
            if(_ptr == nullptr)
            {
                const uint64_t hash{ "events::remove_continuous_hook(const continuous_callback*)->[bool]"_hash };
                _ptr = k2a::plugin.query<decltype(_ptr)>(hash);
            }
            return bool{ _ptr != nullptr ? _ptr(hook) : false };
        }

        [[gnu::noinline]]
        auto add_compact_hook(const compact_callback* hook) noexcept -> bool
        {
            static decltype(&add_compact_hook) _ptr{};
            if(_ptr == nullptr)
            {
                const uint64_t hash{ "events::add_compact_hook(const compact_callback*)->[bool]"_hash };
                _ptr = k2a::plugin.query<decltype(_ptr)>(hash);
            }
            return bool{ _ptr != nullptr ? _ptr(hook) : false };
        }

        [[gnu::noinline]]
        auto remove_compact_hook(const compact_callback* hook) noexcept -> bool
        {
            static decltype(&remove_compact_hook) _ptr{};
            if(_ptr == nullptr)
            {
                const uint64_t hash{ "events::remove_compact_hook(const compact_callback*)->[bool]"_hash };
                _ptr = k2a::plugin.query<decltype(_ptr)>(hash);
            }
            return bool{ _ptr != nullptr ? _ptr(hook) : false };
        }

        auto set_system_disabled_state(bool state) noexcept -> bool
        {
            static decltype(&set_system_disabled_state) _ptr;
            if(_ptr == nullptr)
            {
                const uint64_t hash{ "events::set_system_disabled_state(bool)->[bool]"_hash };
                _ptr = k2a::plugin.query<decltype(_ptr)>(hash);
            }
            return bool{ _ptr != nullptr ? _ptr(state): false };
        }

        auto get_system_disabled_state() noexcept -> std::optional<bool>
        {
            static decltype(&get_system_disabled_state) _ptr;
            if(_ptr == nullptr)
            {
                const uint64_t hash{ "events::get_system_disabled_state(void)->[std::optional<bool>]"_hash };
                _ptr = k2a::plugin.query<decltype(_ptr)>(hash);
            }
            return std::optional<bool>{ _ptr != nullptr ? _ptr() :  std::nullopt };
        }

    }

    namespace sound
    {
        [[gnu::noinline]]
        auto pcm::to_16bits(tjs_int16* output, const void* input, tjs_int channels, tjs_int bytespersample,
             tjs_int bitspersample, bool isfloat, tjs_int count, bool downmix) noexcept -> bool
        {
            static bool(*_ptr)(tjs_int16*, const void*, tjs_int, tjs_int, tjs_int, bool, tjs_int, bool){};
            if(_ptr == nullptr)
            {
                const uint64_t hash{ "sound::pcm::to_16bits(tjs_int16*,const void*,tjs_int,tjs_int,tjs_int,bool,tjs_int,bool)->[bool]"_hash };
                _ptr = k2a::plugin.query<decltype(_ptr)>(hash);
            }

            if(_ptr != nullptr)
            {
                return _ptr(output, input, channels, bytespersample, bitspersample, isfloat, count, downmix);
            }
            return false;
        }

        [[gnu::noinline]]
        auto pcm::to_float(float* output, const void* input, tjs_int channels, tjs_int bytespersample,
             tjs_int bitspersample, bool isfloat, tjs_int count) noexcept -> bool
        {
            static bool(*_ptr)(float*, const void*, tjs_int, tjs_int, tjs_int, bool, tjs_int){};
            if(_ptr == nullptr)
            {
                const uint64_t hash{ "sound::pcm::to_float(float*,const void*,tjs_int,tjs_int,tjs_int,bool,tjs_int)->[bool]"_hash };
                _ptr = k2a::plugin.query<decltype(_ptr)>(hash);
            }
            if(_ptr != nullptr)
            {
                return _ptr(output, input, channels, bytespersample, bitspersample, isfloat, count);
            }
            return false;
        }

        auto pcm::to_16bits(tjs_int16* output, const void* input, const wave_format& format, tjs_int count, bool downmix) noexcept -> bool
        {
            return pcm::to_16bits(output, input, format.channels, format.bytespersample, format.bitspersample, format.isfloat, count, downmix);
        }

        auto pcm::to_float(float* output, const void* input, const wave_format& format, tjs_int count) noexcept -> bool
        {
            return pcm::to_float(output, input, format.channels, format.bytespersample, format.bytespersample, format.isfloat, count);
        }
    }

     [[gnu::noinline]]
    auto add_log(const ttstr &line, bool appendtoimportant) noexcept -> bool
    {
        static decltype(&add_log) _ptr{};
        if(_ptr == nullptr)
        {
            const uint64_t hash{ "log(const ttstr&,bool)->[bool]"_hash };
            _ptr = k2a::plugin.query<decltype(_ptr)>(hash);
        }
        return bool{ _ptr != nullptr ? _ptr(line, appendtoimportant) : false };
    }

    auto important_log(const ttstr& line) noexcept -> bool
    {
        return log(line, true);
    }

    auto inputbox(ttstr& text, const ttstr& caption, const ttstr& prompt, const std::vector<ttstr>& vecButtons) noexcept -> std::optional<int>
    {
        static std::optional<int>(*_ptr)(ttstr&, const ttstr&, const ttstr&, const std::vector<ttstr>&){};
        const uint64_t hash{ "inputbox(ttstr&,const ttstr&,const ttstr&,const std::vector<ttstr>&)->[std::optional<int>]"_hash };
        if(_ptr == nullptr && !k2a::plugin.query(_ptr, hash))
        {
            return std::nullopt;
        }
        return _ptr(text, caption, prompt, vecButtons);
    }

    auto inputbox(ttstr& text, const ttstr& caption, const std::vector<ttstr>& vecButtons) noexcept -> std::optional<int>
    {
        return inputbox(text, caption, "", vecButtons);
    }

    [[gnu::noinline]]
    auto inputbox(ttstr& text, const ttstr& caption) noexcept -> std::optional<bool>
    {
        std::vector<ttstr> btn{};
        btn.resize(2);
        btn[0] = "Cancel";
        btn[1] = "OK";

        const std::optional<int> ret{ inputbox(text, caption, btn) };
        if(ret.has_value())
        {
            return *ret == 1;
        }
        return std::nullopt;
    }

    [[gnu::noinline]]
    auto inputbox(ttstr& text, const ttstr& caption, const ttstr& prompt) noexcept -> std::optional<bool>
    {
        std::vector<ttstr> btn{};
        btn.resize(2);
        btn[0] = "Cancel";
        btn[1] = "OK";

        const std::optional<int> ret{ inputbox(text, caption, prompt, btn) };
        if(ret.has_value())
        {
            return *ret == 1;
        }
        return std::nullopt;
    }

    [[gnu::noinline]]
    auto messagebox(const ttstr& text, const ttstr& caption, const std::vector<ttstr>& vecButtons) noexcept -> std::optional<int>
    {
        static std::optional<int>(*_ptr)(const ttstr&, const ttstr&, const std::vector<ttstr>&){};
        const uint64_t hash{ "messagebox(const ttstr&,const ttstr&,const std::vector<ttstr>&)->[std::optional<int>]"_hash };
        if(_ptr == nullptr && !k2a::plugin.query(_ptr, hash))
        {
            return std::nullopt;
        }
        return _ptr(text, caption, vecButtons);
    }

    [[gnu::noinline]]
    auto messagebox(const ttstr& text, const ttstr& caption) noexcept -> std::optional<bool>
    {
        std::vector<ttstr> btn{};
        btn.resize(2);
        btn[0] = "Cancel";
        btn[1] = "OK";

        const std::optional<int> ret{ messagebox(text, caption, btn) };
        if(ret.has_value())
        {
            return *ret == 1;
        }
        return std::nullopt;
    }

    [[gnu::noinline]]
    auto get_about_string() noexcept -> std::optional<ttstr>
    {
        static decltype(&get_about_string) _ptr{};
        const uint64_t hash{ "get_about_string(void)->[std::optional<ttstr>]"_hash };
        if(_ptr == nullptr && !k2a::plugin.query(_ptr, hash))
        {
            return std::nullopt;
        }
        return _ptr();
    }

    [[gnu::noinline]]
    auto get_version_string() noexcept -> std::optional<ttstr>
    {
        static decltype(&get_version_string) _ptr{};
        const uint64_t hash{ "get_version_string(void)->[std::optional<ttstr>]"_hash };
        if(_ptr == nullptr && !k2a::plugin.query(_ptr, hash))
        {
            return std::nullopt;
        }
        return _ptr();
    }

    [[gnu::noinline]]
    auto get_version_information() noexcept -> std::optional<ttstr>
    {
        static decltype(&get_version_information) _ptr{};
        const uint64_t hash{ "get_version_information(void)->[std::optional<ttstr>]"_hash };
        if(_ptr == nullptr && !k2a::plugin.query(_ptr, hash))
        {
            return std::nullopt;
        }
        return _ptr();
    }

    auto get_tjs_version(tjs_int& major, tjs_int& minor, tjs_int& release) noexcept -> void
    {
        major   = TJSVersionMajor;
        minor   = TJSVersionMinor;
        release = TJSVersionRelease;
    }

    [[gnu::noinline]]
    auto get_system_version(tjs_int& major, tjs_int& minor, tjs_int& release, tjs_int& build) noexcept -> bool
    {
        static decltype(&get_system_version) _ptr{};
        const uint64_t hash{ "get_system_version(tjs_int&,tjs_int&,tjs_int&,tjs_int&)->[bool]"_hash };
        if(_ptr == nullptr && !k2a::plugin.query(_ptr, hash))
        {
            return false;
        }
        return _ptr(major, minor, release, build);
    }

    [[gnu::noinline]]
    auto get_command_line_argument_generation() noexcept -> std::optional<tjs_int>
    {
        static decltype(&get_command_line_argument_generation) _ptr{};
        const uint64_t hash{ "get_command_line_argument_generation(void)->[std::optional<tjs_int>]"_hash };
        if(_ptr == nullptr && !k2a::plugin.query(_ptr, hash))
        {
            return std::nullopt;
        }
        return _ptr();
    }

    [[gnu::noinline]]
    auto get_random_bits128(void* dest) noexcept -> bool
    {
        static decltype(&get_random_bits128) _ptr{};
        if(_ptr == nullptr)
        {
            const uint64_t hash{ "get_random_bits128(void*)->[bool]"_hash };
            _ptr = k2a::plugin.query<decltype(_ptr)>(hash);
        }
        return bool{ _ptr != nullptr ? _ptr(dest) : false };
    }

    [[gnu::noinline]]
    auto get_command_line(const tjs_char* name, tTJSVariant* value) -> std::optional<bool>
    {
        static decltype(&get_command_line) _ptr{};
        if(_ptr == nullptr)
        {
            const uint64_t hash{ "get_command_line(const tjs_char*,tTJSVariant*)->[std::optional<bool>]"_hash };
            _ptr = k2a::plugin.query<decltype(_ptr)>(hash);
        }
        return bool{ _ptr != nullptr ? _ptr(name, value) : std::nullopt };
    }

    [[gnu::noinline]]
    auto set_command_line(const tjs_char* name, const ttstr& value) -> bool
    {
        static decltype(&set_command_line) _ptr{};
        if(_ptr == nullptr)
        {
            const uint64_t hash{ "set_command_line(const tjs_char*,const ttstr&)->[bool]"_hash };
            _ptr = k2a::plugin.query<decltype(_ptr)>(hash);
        }
        return bool{ _ptr != nullptr ? _ptr(name, value) : false };
    }

    [[gnu::noinline]]
    auto get_tick_count() noexcept -> std::optional<tjs_uint64>
    {
        static decltype(&get_tick_count) _ptr{};
        if(_ptr == nullptr)
        {
            const uint64_t hash{ "get_tick_count(void)->[std::optional<tjs_uint64>]"_hash };
            _ptr = k2a::plugin.query<decltype(_ptr)>(hash);
        }
        return bool{ _ptr != nullptr ? _ptr() : false };
    }
}

