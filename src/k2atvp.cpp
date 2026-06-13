#include <kr2android.hpp>
#include <kr2rva.hpp>
#include <k2atvp.hpp>

namespace kr2android::tvp
{
    namespace project
    {

       auto get_dir() noexcept -> const ttstr*
       {
           static ttstr* _ptr{};
           if(_ptr == nullptr)
           {
               _ptr = k2a::cast_ptr<TJS::ttstr*>(rva::TJSString::ProjectDir);
           }
           return _ptr;
       }

       auto get_native_dir() noexcept -> const ttstr*
       {
           static ttstr* _ptr{};
           if(_ptr == nullptr)
           {
               _ptr = k2a::cast_ptr<TJS::ttstr*>(rva::TJSString::NativeProjectDir);
           }
           return _ptr;
       }

        auto app_path() noexcept -> ttstr
        {
            const TJS::ttstr* dir { project::get_dir() };
            if(dir != nullptr && !dir->IsEmpty())
            {
                return storage::extract_path(*dir);
            }
            return ttstr{};
        }

        auto game_path() noexcept -> ttstr
        {
            const TJS::ttstr* dir { project::get_native_dir() };
            if(dir != nullptr && !dir->IsEmpty())
            {
                return storage::extract_path(*dir);
            }
            return ttstr{};
        }

    }

    namespace storage
    {
        auto media_manager::get() noexcept -> storage::StorageMediaManager*
        {
            static storage::StorageMediaManager* _ptr{};
            if(_ptr == nullptr)
            {
                _ptr = k2a::cast_ptr<decltype(_ptr)>(rva::StorageMediaManager::MediaManager);
            }
            return _ptr;
        }

        auto register_media(storage::iStorageMedia* media) noexcept -> bool
        {
            storage::StorageMediaManager* manager{ media_manager::get() };
            if(manager == nullptr)
            {
                return false;
            }
            return manager->Register(media);
        }

        auto unregister_media(iStorageMedia* media) noexcept -> bool
        {
            storage::StorageMediaManager* manager{ media_manager::get() };
            if(manager == nullptr)
            {
                return false;
            }
            manager->Unregister(media);
            return true;
        }

        auto clear_caches() noexcept -> bool
        {
            static void(*_ptr)(void){};
            if(_ptr == nullptr)
            {
                _ptr = k2a::cast_ptr<decltype(_ptr)>(rva::ClearStorageCaches);
            }
            return bool{ _ptr ? (_ptr(), true) : false };
        }

        auto normalize_name(const ttstr& name) noexcept -> std::optional<ttstr>
        {
            StorageMediaManager* manager{ media_manager::get() };
            if(manager != nullptr)
            {
                return manager->NormalizeStorageName(name);
            }
            return std::nullopt;
        }

        auto is_existent_no_search(const ttstr& name) noexcept -> std::optional<bool>
        {
            static bool(*_ptr)(const ttstr&){};
            if(_ptr == nullptr)
            {
                _ptr = cast_ptr<decltype(_ptr)>(rva::IsExistentStorageNoSearch);
            }
            if(_ptr != nullptr)
            {
                return _ptr(name);
            }
            return std::nullopt;
        }

        auto is_existent_no_search_no_normalize(const ttstr& name) noexcept -> std::optional<bool>
        {
            static bool(*_ptr)(const ttstr&){};
            if(_ptr == nullptr)
            {
                _ptr = cast_ptr<decltype(_ptr)>(rva::IsExistentStorageNoSearchNoNormalize);
            }
            if(_ptr) return _ptr(name);
            return std::nullopt;
        }

        auto set_current_directory(const ttstr& directory) noexcept -> bool
        {
            static void(*_ptr)(const ttstr&){};
            if(_ptr == nullptr)
            {
                _ptr = k2a::cast_ptr<decltype(_ptr)>(rva::SetCurrentDirectory);
            }
            return bool{ _ptr ? (_ptr(directory), true) : false  };
        }

        auto add_auto_path(const ttstr& path) noexcept -> bool
        {
            static void(*_ptr)(const ttstr&){};
            if(_ptr == nullptr)
            {
                _ptr = cast_ptr<decltype(_ptr)>(rva::AddAutoPath);
            }
            return bool{ _ptr ? (_ptr(path), true) : false };
        }

        auto remove_auto_path(const ttstr& path) noexcept -> bool
        {
            static void(*_ptr)(const ttstr&){};
            if(_ptr == nullptr)
            {
                _ptr = cast_ptr<decltype(_ptr)>(rva::RemoveAutoPath);
            }
            return bool{ _ptr ? (_ptr(path), true) : false };
        }

        auto get_placed_path(const ttstr& path) noexcept -> std::optional<ttstr>
        {
            static ttstr(*_ptr)(const ttstr&){};
            if(_ptr == nullptr)
            {
                _ptr = cast_ptr<decltype(_ptr)>(rva::GetPlacedPath);
            }

            if(_ptr != nullptr)
            {
                return _ptr(path);
            }

            return std::nullopt;
        }

        auto is_existent(const ttstr& path) noexcept -> std::optional<bool>
        {
            std::optional<ttstr> _path{ get_placed_path(path) };
            if(_path.has_value())
            {
                return !_path.value().IsEmpty();
            }
            return std::nullopt;
        }

        auto get_local_name(ttstr& name) noexcept -> std::optional<ttstr>
        {
            if(TJS_strchr(name.c_str(), u'>'))
            {
                return std::nullopt;
            }

            storage::StorageMediaManager* manager = storage::media_manager::get();
            if(manager == nullptr)
            {
                return std::nullopt;
            }

            return manager->GetLocallyAccessibleName(name);
        }

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
                size_t ext_len = str.length() - dot_pos;
                return ttstr{ name.c_str() + dot_pos, static_cast<tjs_int>(ext_len) };
            }
            return ttstr{};
        }

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

        auto chop_ext(const ttstr & name) noexcept -> ttstr
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
        static extraction_filter_t* extraction_filter{};
        static content_filter_t*       content_filter{};

        auto get_content_filter() noexcept -> content_filter_t
        {
            if(content_filter == nullptr)
            {
                content_filter = cast_ptr<content_filter_t*>(rva::XP3Archive::ContentFilter);
            }
            return content_filter_t{ content_filter ? (*content_filter) : nullptr  };
        }

        auto get_extraction_filter() noexcept -> extraction_filter_t
        {
            if(extraction_filter == nullptr)
            {
                extraction_filter = cast_ptr<extraction_filter_t*>(rva::XP3Archive::ExtractionFilter);
            }
            return extraction_filter_t{ extraction_filter ? (*extraction_filter) : nullptr  };
        }

        auto set_content_filter(content_filter_t filter) noexcept -> bool
        {
            if(get_content_filter() != nullptr)
            {
                *content_filter = filter;
                return true;
            }
            return false;
        }

        auto set_extraction_filter(extraction_filter_t filter) noexcept -> bool
        {
            if(get_extraction_filter() != nullptr)
            {
                *extraction_filter = filter;
                return true;
            }
            return false;
        }
    }

    namespace stream
    {

        auto create_text_for_read(const ttstr& name, const ttstr& modestr) noexcept -> iTJSTextReadStream*
        {
            static decltype(&create_text_for_read) _ptr{};
            if(_ptr == nullptr)
            {
                _ptr = cast_ptr<decltype(_ptr)>(rva::CreateTextStreamForRead);
            }
            return (iTJSTextReadStream*){ _ptr ? _ptr(name, modestr) : nullptr };
        }

        auto create_text_for_write(const ttstr& name, const ttstr& modestr) noexcept -> iTJSTextWriteStream*
        {
            static decltype(&create_text_for_write) _ptr{};
            if(_ptr == nullptr)
            {
                _ptr = cast_ptr<decltype(_ptr)>(rva::CreateTextStreamForWrite);
            }
            return (iTJSTextWriteStream*){ _ptr ? _ptr(name, modestr) : nullptr };
        }

        auto create_binary_for_read(const ttstr& name, const ttstr& modestr) noexcept -> tTJSBinaryStream*
        {
            static decltype(&create_binary_for_read) _ptr{};
            if(_ptr == nullptr)
            {
                _ptr = cast_ptr<decltype(_ptr)>(rva::CreateBinaryStreamForRead);
            }
            return (tTJSBinaryStream*){ _ptr ? _ptr(name, modestr) : nullptr };
        }

        auto create_binary_for_write(const ttstr& name, const ttstr& modestr) noexcept -> tTJSBinaryStream*
        {
            static decltype(&create_binary_for_write) _ptr{};
            if(_ptr == nullptr)
            {
                _ptr = cast_ptr<decltype(_ptr)>(rva::CreateBinaryStreamForWrite);
            }
            return (tTJSBinaryStream*){ _ptr ? _ptr(name, modestr) : nullptr };
        }
    }

    namespace graphic
    {
        auto type::get() noexcept -> graphic::GraphicType*
        {
            static graphic::GraphicType* _ptr{};
            if(_ptr == nullptr)
            {
                _ptr = k2a::cast_ptr<graphic::GraphicType*>(rva::Graphic::GraphicType);
            }
            return _ptr;
        }

        auto register_loading_handler(const HandlerType& handler) noexcept -> bool
        {
            graphic::GraphicType* graphic_type{ type::get() };
            if(graphic_type == nullptr)
            {
                return false;
            }

            graphic_type->Register(handler);
            return true;
        }

        auto unregister_loading_handler(const HandlerType& handler) noexcept -> bool
        {
            graphic::GraphicType* graphic_type{ type::get() };
            if(graphic_type == nullptr)
            {
                return false;
            }

            graphic_type->Unregister(handler);
            return true;
        }

        auto clear_cache() noexcept -> bool
        {
            static void(*_ptr)(void){};
            if(_ptr == nullptr)
            {
                _ptr = cast_ptr<decltype(_ptr)>(rva::Graphic::ClearGraphicCache);
            }
            return bool{ _ptr ? (_ptr(), true) : false };
        }
    }

    namespace script
    {
        auto get_engine() noexcept -> tTJS*
        {
            static tTJS* _ptr{};
            if(_ptr == nullptr)
            {
                _ptr = cast_ptr<tTJS*>(rva::Script::ScriptEngine);
            }
            return _ptr;
        }

        auto get_dispatch() noexcept -> iTJSDispatch2*
        {
            tTJS* const engine{ get_engine() };
            if(engine != nullptr)
            {
                return engine->GetGlobal();
            }
            return nullptr;
        }

        auto dump_engine() noexcept -> bool
        {
            tTJS* const engine{ get_engine() };
            if(engine != nullptr)
            {
            }
            return false;
        }

        auto execute(const ttstr& content, iTJSDispatch2* context, tTJSVariant* result) noexcept -> bool
        {
            tTJS* const engine{ get_engine() };
            if(engine != nullptr)
            {
                try
                {
                    engine->ExecScript(content, result, context);
                    return true;
                }
                catch(...) {}
            }
            return false;
        }

        auto execute(const ttstr& content, const ttstr& name, tjs_int lineofs, iTJSDispatch2* context, tTJSVariant* result) noexcept -> bool
        {
            tTJS* const engine{ get_engine() };
            if(engine != nullptr)
            {
                try
                {
                    engine->ExecScript(content, result, context, &name, lineofs);
                    return true;
                }
                catch(...) {}
            }
            return false;
        }

        auto execexpr(const ttstr& content, iTJSDispatch2* context, tTJSVariant* result) noexcept -> bool
        {
            tTJS* const engine{ get_engine() };
            if(engine != nullptr)
            {
                bool success{};
                iTJSConsoleOutput* const output{ engine->GetConsoleOutput() };
                engine->SetConsoleOutput(nullptr); // once set TJS console to null
                try
                {
                    engine->EvalExpression(content, result, context);
                    success = true;
                }
                catch(...)
                {
                    success = false;
                }
                engine->SetConsoleOutput(output);
                return success;
            }
            return false;
        }

        auto execexpr(const ttstr& content, const ttstr& name, tjs_int lineofs, iTJSDispatch2* context, tTJSVariant* result) noexcept -> bool
        {
            tTJS* const engine{ get_engine() };
            if(engine != nullptr)
            {
                bool success{};
                iTJSConsoleOutput* const output{ engine->GetConsoleOutput() };
                engine->SetConsoleOutput(nullptr); // once set TJS console to null
                try
                {
                    engine->EvalExpression(content, result, context, &name, lineofs);
                    success = true;
                }
                catch(...)
                {
                    success = false;
                }
                engine->SetConsoleOutput(output);
                return success;
            }
            return false;
        }

        auto load(const ttstr& name, iTJSDispatch2* context, tTJSVariant* result, bool isexpression, const tjs_char* modestr) noexcept -> bool
        {
            tTJS* const engine{ get_engine() };
            if(engine == nullptr)
            {
                return false;
            }

            const std::optional<ttstr> place{ storage::get_placed_path(name) };
            if(!place.has_value() || (*place).IsEmpty())
            {
                return false;
            }

            const std::optional<ttstr> shortname{ storage::extract_name(*place) };
            if(!shortname.has_value() || shortname->IsEmpty())
            {
                return false;
            }

            tTJSBinaryStream* binary_stream{ stream::create_binary_for_read(*place, modestr) };
            if(binary_stream != nullptr)
            {
                bool is_bytecode{}, success{};
                try
                {
                    is_bytecode = engine->LoadByteCode(binary_stream, result, context, shortname->c_str());
                    success = true;
                }
                catch(...)
                {
                    success = false;
                }
                delete binary_stream;

                if(!success)
                {
                    return false;
                }

                if(is_bytecode)
                {
                    return true;
                }
            }

            iTJSTextReadStream* text_stream{ stream::create_text_for_read(*place, modestr) };
            if(text_stream != nullptr)
            {
                bool success{};
                ttstr buffer{};
                try
                {
                    text_stream->Read(buffer, 0);
                    success = true;
                }
                catch(...)
                {
                    success = false;
                }
                text_stream->Destruct();
                text_stream = nullptr;

                if(!success)
                {
                    return false;
                }

                try
                {
                    if(isexpression)
                    {
                        engine->EvalExpression(buffer, result, context, &(*shortname));
                    }
                    else
                    {
                        engine->ExecScript(buffer, result, context, &(*shortname));
                    }
                    return true;
                }
                catch(...){}
            }

            return false;
        }

        auto loadbytes(const tjs_uint8* content, size_t length, iTJSDispatch2* context, tTJSVariant* result, const tjs_char* name) noexcept -> bool
        {
            tTJS* const engine{ get_engine() };
            if(engine != nullptr)
            {
                try
                {
                    engine->LoadByteCode(content, length, result, context, name);
                    return true;
                }
                catch(...){}
            }
            return false;
        }

        auto execute(const ttstr& content, tTJSVariant* result) noexcept -> bool
        {
            return script::execute(content, nullptr, result);
        }

        auto execute(const ttstr& content, const ttstr& name, tjs_int lineofs, tTJSVariant* result) noexcept -> bool
        {
            return script::execute(content, name, lineofs, nullptr, result);
        }

        auto execexpr(const ttstr& content, tTJSVariant* result) noexcept -> bool
        {
            return script::execexpr(content, nullptr, result);
        }

        auto execexpr(const ttstr& content, const ttstr& name, tjs_int lineofs, tTJSVariant* result) noexcept -> bool
        {
            return script::execexpr(content, name, lineofs, nullptr, result);
        }

        auto load(const ttstr& name, tTJSVariant* result, bool isexpression, const tjs_char* modestr) noexcept -> bool
        {
            script::load(name, nullptr, result, isexpression, modestr);
        }

    }

    namespace scripts
    {
        auto get_text_encoding() noexcept -> const tjs_char*
        {
            static decltype(&get_text_encoding) _ptr{};
            if(_ptr == nullptr)
            {
                _ptr = cast_ptr<decltype(_ptr)>(rva::GetDefaultReadEncoding);
            }
            return (const tjs_char*){ _ptr ? _ptr() : nullptr };
        }

        auto set_text_encoding(const ttstr& name) noexcept -> bool
        {
            static decltype(&set_text_encoding) _ptr{};
            if(_ptr == nullptr)
            {
                _ptr = cast_ptr<decltype(_ptr)>(rva::SetDefaultReadEncoding);
            }
            return bool{ _ptr ? (_ptr(name), true) : false };
        }
    }

    auto get_command_line(const tjs_char* name, tTJSVariant* value) -> std::optional<bool>
    {
        static bool(*_ptr)(const tjs_char*, tTJSVariant*){};
        if(_ptr == nullptr)
        {
            _ptr = cast_ptr<decltype(_ptr)>(rva::GetCommandLine);
        }

        if(_ptr != nullptr)
        {
            return _ptr(name, value);
        }

        return std::nullopt;
    }

    auto set_command_line(const tjs_char* name, const ttstr& value) -> bool
    {
        static void(*_ptr)(const tjs_char*, const ttstr&){};

        if(_ptr == nullptr)
        {
            _ptr = cast_ptr<decltype(_ptr)>(rva::SetCommandLine);
        }

        if(_ptr != nullptr)
        {
            return _ptr(name, value), true;
        }

        return false;
    }

    auto get_tick_count() noexcept -> std::optional<tjs_uint64>
    {
        static tjs_uint64(*_ptr)(void){};
        if(_ptr == nullptr)
        {
            _ptr = cast_ptr<decltype(_ptr)>(rva::GetTickCount);
        }
        if(_ptr != nullptr)
        {
            return _ptr();
        }
        return std::nullopt;
    }
}

