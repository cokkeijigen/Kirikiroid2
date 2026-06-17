#include <filesystem>
#include <fstream>
#include <kr2android.hpp>
#include <kr2rva.hpp>
#include <k2atvp.hpp>
#include <TJSDumpFileOutput.hpp>
#include <xstr.hpp>
namespace kr2android::tvp
{

    namespace system
    {
        [[gnu::noinline]]
        auto get_dir() noexcept -> const ttstr*
        {
           static ttstr* _ptr{};
           if(_ptr == nullptr)
           {
               _ptr = k2a::cast_ptr<TJS::ttstr*>(rva::TJSString::ProjectDir);
           }
           return _ptr;
        }

        [[gnu::noinline]]
        auto get_native_dir() noexcept -> const ttstr*
        {
            static ttstr* _ptr{};
            if(_ptr == nullptr)
            {
                _ptr = k2a::cast_ptr<TJS::ttstr*>(rva::TJSString::NativeProjectDir);
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
            return ttstr{};
        }

    }

    namespace storage
    {

        [[gnu::noinline]]
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

        [[gnu::noinline]]
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

        [[gnu::noinline]]
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

        [[gnu::noinline]]
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

        [[gnu::noinline]]
        auto set_current_directory(const ttstr& directory) noexcept -> bool
        {
            static void(*_ptr)(const ttstr&){};
            if(_ptr == nullptr)
            {
                _ptr = k2a::cast_ptr<decltype(_ptr)>(rva::SetCurrentDirectory);
            }
            return bool{ _ptr ? (_ptr(directory), true) : false  };
        }

        [[gnu::noinline]]
        auto add_auto_path(const ttstr& path) noexcept -> bool
        {
            static void(*_ptr)(const ttstr&){};
            if(_ptr == nullptr)
            {
                _ptr = cast_ptr<decltype(_ptr)>(rva::AddAutoPath);
            }
            return bool{ _ptr ? (_ptr(path), true) : false };
        }

        [[gnu::noinline]]
        auto remove_auto_path(const ttstr& path) noexcept -> bool
        {
            static void(*_ptr)(const ttstr&){};
            if(_ptr == nullptr)
            {
                _ptr = cast_ptr<decltype(_ptr)>(rva::RemoveAutoPath);
            }
            return bool{ _ptr ? (_ptr(path), true) : false };
        }

        [[gnu::noinline]]
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

        [[gnu::noinline]]
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

        [[gnu::noinline]]
        auto get_content_filter() noexcept -> content_filter_t
        {
            if(content_filter == nullptr)
            {
                content_filter = cast_ptr<content_filter_t*>(rva::XP3Archive::ContentFilter);
            }
            return content_filter_t{ content_filter ? (*content_filter) : nullptr  };
        }

        [[gnu::noinline]]
        auto get_extraction_filter() noexcept -> extraction_filter_t
        {
            if(extraction_filter == nullptr)
            {
                extraction_filter = cast_ptr<extraction_filter_t*>(rva::XP3Archive::ExtractionFilter);
            }
            return extraction_filter_t{ extraction_filter ? (*extraction_filter) : nullptr  };
        }

        [[gnu::noinline]]
        auto set_content_filter(content_filter_t filter) noexcept -> bool
        {
            if(get_content_filter() != nullptr)
            {
                *content_filter = filter;
                return true;
            }
            return false;
        }

        [[gnu::noinline]]
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

        [[gnu::noinline]]
        auto create_text_for_read(const ttstr& name, const ttstr& modestr) noexcept -> iTJSTextReadStream*
        {
            static decltype(&create_text_for_read) _ptr{};
            if(_ptr == nullptr)
            {
                _ptr = cast_ptr<decltype(_ptr)>(rva::CreateTextStreamForRead);
            }
            return (iTJSTextReadStream*){ _ptr ? _ptr(name, modestr) : nullptr };
        }

        [[gnu::noinline]]
        auto create_text_for_write(const ttstr& name, const ttstr& modestr) noexcept -> iTJSTextWriteStream*
        {
            static decltype(&create_text_for_write) _ptr{};
            if(_ptr == nullptr)
            {
                _ptr = cast_ptr<decltype(_ptr)>(rva::CreateTextStreamForWrite);
            }
            return (iTJSTextWriteStream*){ _ptr ? _ptr(name, modestr) : nullptr };
        }

        [[gnu::noinline]]
        auto create_binary_for_read(const ttstr& name, const ttstr& modestr) noexcept -> tTJSBinaryStream*
        {
            static decltype(&create_binary_for_read) _ptr{};
            if(_ptr == nullptr)
            {
                _ptr = cast_ptr<decltype(_ptr)>(rva::CreateBinaryStreamForRead);
            }
            return (tTJSBinaryStream*){ _ptr ? _ptr(name, modestr) : nullptr };
        }

        [[gnu::noinline]]
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
        [[gnu::noinline]]
        auto type::get() noexcept -> graphic::GraphicType*
        {
            static graphic::GraphicType* _ptr{};
            if(_ptr == nullptr)
            {
                _ptr = k2a::cast_ptr<graphic::GraphicType*>(rva::Graphic::GraphicType);
            }
            return _ptr;
        }

        [[gnu::noinline]]
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

        [[gnu::noinline]]
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

        [[gnu::noinline]]
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

        class __tTJS
        {
            void*            __vtable;
            tjs_uint __unused_field00;
            void*    __unused_field01;
            void*    __unused_field02;
            void*    __unused_field03;
            void*    __unused_field04;
            void*    __unused_field05;
            void*    __unused_field06;
            void*    __unused_field07;

            static auto __dump(const __tTJS*, tjs_uint) noexcept -> void;

        public:

            iTJSConsoleOutput*     ConsoleOutput;
            tTJSCustomObject*      Global;
            tTJSScriptCache*       Cache;
            tTJSVariantArrayStack* VariantArrayStack;

            [[gnu::noinline]]
            auto Dump(tjs_uint width = 0x50) const noexcept -> bool
            {
                static decltype(&__tTJS::__dump) _ptr;
                if(_ptr == nullptr)
                {
                    _ptr = cast_ptr<decltype(_ptr)>(rva::Script::ScriptEngine_tTJS_Dump);
                }
                return bool{ _ptr != nullptr ? (_ptr(this, width), true) : false };
            }
        };

        [[gnu::noinline]]
        auto __get_engine() noexcept -> __tTJS*
        {
            static __tTJS** _pptr{};
            if(_pptr == nullptr)
            {
                _pptr = cast_ptr<__tTJS**>(rva::Script::ScriptEngine);
            }
            return (__tTJS*){ _pptr != nullptr ? *_pptr : nullptr };
        }

        [[gnu::noinline]]
        auto get_engine() noexcept -> tTJS*
        {
            static tTJS* tjs{};

            __tTJS* const __tjs{ __get_engine() };
            if(tjs == nullptr)
            {
                const auto this_Global{ reinterpret_cast<iTJSDispatch2*>(__tjs->Global) };
                this_Global->AddRef();

                tjs = new tTJS{ __tjs ? __tjs->Global : nullptr };
            }
            else if(__tjs != nullptr && __tjs->Global != nullptr)
            {
                iTJSDispatch2* const this_Global{ tjs->GetGlobalNoAddRef() };
                const auto that_Global{ reinterpret_cast<iTJSDispatch2*>(__tjs->Global) };
                if(this_Global != that_Global)
                {
                    if(this_Global != nullptr)
                    {
                        this_Global->Release();
                    }
                    delete tjs;

                    that_Global->AddRef();
                    tjs = new tTJS{ __tjs->Global };
                }
            }
            return tjs;
        }

        [[gnu::noinline]]
        auto get_dispatch(bool addref) noexcept -> iTJSDispatch2*
        {
            iTJSDispatch2* _global{};
            __tTJS* const  _tjs{ script::__get_engine() };

            if(_tjs != nullptr && _tjs->Global != nullptr)
            {
                _global = reinterpret_cast<iTJSDispatch2*>( _tjs->Global);
            }

            if(addref)
            {
                if(_global == nullptr)
                {
                    const auto _call{ cast_ptr<iTJSDispatch2*(*)(void)>(rva::Script::GetScriptDispatch) };
                    _global = (iTJSDispatch2*){ _call != nullptr ? _call() : nullptr };
                }
                else
                {
                    _global->AddRef();
                }
            }

            return _global;
        }

        [[gnu::noinline]]
        auto dump_engine(std::string_view name, bool global) noexcept -> bool
        {
            union { void* _tjs_engine; __tTJS* _engine; tTJS* engine; };
            if(global)
            {
                _engine = __get_engine();
            }
            else
            {
                engine = get_engine();
            }

            if(_tjs_engine == nullptr)
            {
                return false;
            }

            const ttstr base{ system::base_path() };
            if(base.IsEmpty())
            {
                return false;
            }

            name = xstr::trim(name);
            if(name.empty())
            {
                name = global ? "global.dump.txt" : "plugin.dump.txt";
            }

            std::filesystem::path outpu_file_path{ base.c_str() };
            auto&& ref_outpu_file_path{ const_cast<std::string&>(outpu_file_path.native()) };
            {
                size_t dirofs{ ref_outpu_file_path.size() };
                ref_outpu_file_path.reserve(name.size() + dirofs + 6);

                if(ref_outpu_file_path.back() == '\\')
                {
                    ref_outpu_file_path[dirofs - 1] = '/';
                }
                else if(ref_outpu_file_path.back() != '/')
                {
                    ref_outpu_file_path.push_back('/');
                }

                ref_outpu_file_path.append(name);

                if(name.size() <= 2 && (name == ".." || name == "."))
                {
                    ref_outpu_file_path.append(".txt");
                }
                else
                {
                    for(size_t i{ dirofs + 1 }; i < ref_outpu_file_path.size(); i++)
                    {
                        const char ch{ ref_outpu_file_path[i] };
                        const bool is_not_valid
                        {
                            ch == '/' || ch == '\\' || ch == ':' || ch == '*' ||
                            ch == '?' || ch == '"'  || ch == '<' || ch == '>' || ch == '|'
                        };
                        if(is_not_valid)
                        {
                            ref_outpu_file_path[i] = '_';
                        }
                    }
                }
            }

            TJSDumpFileOutput dump_output{ outpu_file_path };
            if(!dump_output.IsOpen())
            {
                return false;
            }

            bool success{};
            if(!global)
            {

                iTJSConsoleOutput* const output{ engine->GetConsoleOutput() };
                try
                {
                    engine->SetConsoleOutput(&dump_output);
                    engine->Dump();
                    success = true;
                }
                catch(...)
                {
                    success = false;
                }
                engine->SetConsoleOutput(output);
            }
            else
            {
                iTJSConsoleOutput* const output{ _engine->ConsoleOutput };
                _engine->ConsoleOutput = &dump_output;

                success = _engine->Dump();
                _engine->ConsoleOutput = output;
            }
            return success;
        }

        [[gnu::noinline]]
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

        [[gnu::noinline]]
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

        [[gnu::noinline]]
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

        [[gnu::noinline]]
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

        [[gnu::noinline]]
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

        [[gnu::noinline]]
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
        [[gnu::noinline]]
        auto get_text_encoding() noexcept -> const tjs_char*
        {
            static decltype(&get_text_encoding) _ptr{};
            if(_ptr == nullptr)
            {
                _ptr = cast_ptr<decltype(_ptr)>(rva::GetDefaultReadEncoding);
            }
            return (const tjs_char*){ _ptr ? _ptr() : nullptr };
        }

        [[gnu::noinline]]
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

    [[gnu::noinline]]
    auto get_random_bits128(void* dest) noexcept -> bool
    {
        static void(*_ptr)(void*){};
        if(_ptr == nullptr)
        {
            _ptr = cast_ptr<decltype(_ptr)>(rva::GetRandomBits128);
        }
        return bool{ _ptr != nullptr ? (_ptr(dest), true) : false };
    }

    [[gnu::noinline]]
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

    [[gnu::noinline]]
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

    [[gnu::noinline]]
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

