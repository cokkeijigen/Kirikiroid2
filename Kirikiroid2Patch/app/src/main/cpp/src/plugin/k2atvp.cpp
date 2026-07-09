#include <filesystem>
#include <vector>
#include <fstream>
#include <algorithm>
#include <tjsObject.h>
#include <TJSDumpFileOutput.hpp>
#include <kr2android.hpp>
#include <kr2rva.hpp>
#include <k2atvp.hpp>
#include <xstr.hpp>
#include <tjsDictionary.h>
#include <k2atvp_sound.hpp>

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
                _ptr = k2a::cast_ptr<TJS::ttstr*>(RVA::TJSString::ProjectDir);
            }
            return _ptr;
        }

        [[gnu::noinline]]
        auto get_native_dir() noexcept -> const ttstr*
        {
            static ttstr* _ptr{};
            if(_ptr == nullptr)
            {
                _ptr = k2a::cast_ptr<TJS::ttstr*>(RVA::TJSString::NativeProjectDir);
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
                _ptr = k2a::cast_ptr<decltype(_ptr)>(RVA::StorageMediaManager::MediaManager);
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

        auto unregister_media(storage::iStorageMedia* media) noexcept -> bool
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
                _ptr = k2a::cast_ptr<decltype(_ptr)>(RVA::Storage::ClearStorageCaches);
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
                _ptr = k2a::cast_ptr<decltype(_ptr)>(RVA::Storage::IsExistentStorageNoSearch);
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
                _ptr = k2a::cast_ptr<decltype(_ptr)>(RVA::Storage::IsExistentStorageNoSearchNoNormalize);
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
                _ptr = k2a::cast_ptr<decltype(_ptr)>(RVA::Storage::SetCurrentDirectory);
            }
            return bool{ _ptr ? (_ptr(directory), true) : false  };
        }

        [[gnu::noinline]]
        auto add_auto_path(const ttstr& path) noexcept -> bool
        {
            static void(*_ptr)(const ttstr&){};
            if(_ptr == nullptr)
            {
                _ptr = k2a::cast_ptr<decltype(_ptr)>(RVA::Storage::AddAutoPath);
            }
            return bool{ _ptr ? (_ptr(path), true) : false };
        }

        [[gnu::noinline]]
        auto remove_auto_path(const ttstr& path) noexcept -> bool
        {
            static void(*_ptr)(const ttstr&){};
            if(_ptr == nullptr)
            {
                _ptr = k2a::cast_ptr<decltype(_ptr)>(RVA::Storage::RemoveAutoPath);
            }
            return bool{ _ptr ? (_ptr(path), true) : false };
        }

        [[gnu::noinline]]
        auto get_placed_path(const ttstr& path) noexcept -> std::optional<ttstr>
        {
            static ttstr(*_ptr)(const ttstr&){};
            if(_ptr == nullptr)
            {
                _ptr = k2a::cast_ptr<decltype(_ptr)>(RVA::Storage::GetPlacedPath);
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

        auto get_local_name(const ttstr& name) noexcept -> std::optional<ttstr>
        {
            if(TJS_strchr(name.c_str(), u'>'))
            {
                return "";
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
                content_filter = k2a::cast_ptr<content_filter_t*>(RVA::XP3Archive::ContentFilter);
            }
            return content_filter_t{ content_filter ? (*content_filter) : nullptr  };
        }

        [[gnu::noinline]]
        auto get_extraction_filter() noexcept -> extraction_filter_t
        {
            if(extraction_filter == nullptr)
            {
                extraction_filter = k2a::cast_ptr<extraction_filter_t*>(RVA::XP3Archive::ExtractionFilter);
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
                _ptr = k2a::cast_ptr<decltype(_ptr)>(RVA::Stream::CreateTextStreamForRead);
            }
            return (iTJSTextReadStream*){ _ptr ? _ptr(name, modestr) : nullptr };
        }

        [[gnu::noinline]]
        auto create_text_for_write(const ttstr& name, const ttstr& modestr) noexcept -> iTJSTextWriteStream*
        {
            static decltype(&create_text_for_write) _ptr{};
            if(_ptr == nullptr)
            {
                _ptr = k2a::cast_ptr<decltype(_ptr)>(RVA::Stream::CreateTextStreamForWrite);
            }
            return (iTJSTextWriteStream*){ _ptr ? _ptr(name, modestr) : nullptr };
        }

        [[gnu::noinline]]
        auto create_binary_for_read(const ttstr& name, const ttstr& modestr) noexcept -> tTJSBinaryStream*
        {
            static decltype(&create_binary_for_read) _ptr{};
            if(_ptr == nullptr)
            {
                _ptr = k2a::cast_ptr<decltype(_ptr)>(RVA::Stream::CreateBinaryStreamForRead);
            }
            return (tTJSBinaryStream*){ _ptr ? _ptr(name, modestr) : nullptr };
        }

        [[gnu::noinline]]
        auto create_binary_for_write(const ttstr& name, const ttstr& modestr) noexcept -> tTJSBinaryStream*
        {
            static decltype(&create_binary_for_write) _ptr{};
            if(_ptr == nullptr)
            {
                _ptr = k2a::cast_ptr<decltype(_ptr)>(RVA::Stream::CreateBinaryStreamForWrite);
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
                _ptr = k2a::cast_ptr<graphic::GraphicType*>(RVA::Graphic::GraphicType);
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
                _ptr = k2a::cast_ptr<decltype(_ptr)>(RVA::Graphic::ClearGraphicCache);
            }
            return bool{ _ptr ? (_ptr(), true) : false };
        }
    }

    namespace scripts
    {

        struct __tTJS
        {
        private:

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
                    _ptr = k2a::cast_ptr<decltype(_ptr)>(RVA::Scripts::ScriptEngine_tTJS_Dump);
                }
                return bool{ _ptr != nullptr ? (_ptr(this, width), true) : false };
            }
        };

        struct tTJS__ : public ::tTJS
        {
            inline auto SetGlobal(tTJSCustomObject* global) noexcept -> void
            {
                if(global == nullptr)
                {
                    return;
                }

                if(this->Global != nullptr)
                {
                    this->Global->Release();
                }

                this->Global = global;
            }
        };

        [[gnu::noinline]]
        auto __get_engine() noexcept -> __tTJS*
        {
            static __tTJS** _pptr{};
            if(_pptr == nullptr)
            {
                _pptr = k2a::cast_ptr<__tTJS**>(RVA::Scripts::ScriptEngine);
            }
            return (__tTJS*){ _pptr != nullptr ? *_pptr : nullptr };
        }

        [[gnu::noinline]]
        auto get_engine() noexcept -> tTJS*
        {
            static union{ tTJS* tjs{}; tTJS__* tjs__; };

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
                    that_Global->AddRef();
                    tjs__->SetGlobal(__tjs->Global);
                }
            }
            return tjs;
        }

        [[gnu::noinline]]
        auto get_dispatch(bool addref) noexcept -> iTJSDispatch2*
        {
            iTJSDispatch2* _global{};
            __tTJS* const  _tjs{ scripts::__get_engine() };

            if(_tjs != nullptr && _tjs->Global != nullptr)
            {
                _global = reinterpret_cast<iTJSDispatch2*>( _tjs->Global);
            }

            if(addref)
            {
                if(_global == nullptr)
                {
                    const auto _call{ cast_ptr<iTJSDispatch2*(*)(void)>(RVA::Scripts::GetScriptDispatch) };
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
                _engine = scripts::__get_engine();
            }
            else
            {
                engine = scripts::get_engine();
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

        namespace global
        {
            auto get(bool addref) noexcept -> iTJSDispatch2*
            {
                scripts::get_dispatch(addref);
            }

            auto register_object(const tjs_char* name, iTJSDispatch2* dsp) noexcept -> bool
            {
                iTJSDispatch2* const global{ scripts::get_dispatch(false) };
                if(global == nullptr)
                {
                    return false;
                }
                try
                {
                    tTJSVariant val{ dsp };
                    const tjs_error error
                    {
                        global->PropSet(TJS_MEMBERENSURE, name, NULL, &val, global)
                    };
                    return TJS_SUCCEEDED(error);
                }
                catch(...) { }
                return false;
            }

            auto remove_object(const tjs_char* name) noexcept -> bool
            {
                iTJSDispatch2* const global{ scripts::get_dispatch(false) };
                if(global == nullptr)
                {
                    return false;
                }

                try
                {
                    const tjs_error error
                    {
                        global->DeleteMember(0, name, NULL, global)
                    };
                    return TJS_SUCCEEDED(error);
                }
                catch(...) { }
                return false;
            }
        }

        [[gnu::noinline]]
        auto get_text_encoding() noexcept -> std::optional<ttstr>
        {
            static const tjs_char*(*_ptr)(void){};
            if(_ptr == nullptr)
            {
                _ptr = k2a::cast_ptr<decltype(_ptr)>(RVA::Scripts::GetDefaultReadEncoding);
            }

            if(_ptr != nullptr)
            {
                return ttstr{ _ptr() };
            }
            return std::nullopt;
        }

        [[gnu::noinline]]
        auto set_text_encoding(const ttstr& name) noexcept -> bool
        {
            static decltype(&set_text_encoding) _ptr{};
            if(_ptr == nullptr)
            {
                _ptr = k2a::cast_ptr<decltype(_ptr)>(RVA::Scripts::SetDefaultReadEncoding);
            }
            return bool{ _ptr ? (_ptr(name), true) : false };
        }
    }

    namespace events
    {

        struct tTVPEvent
        {
            iTJSDispatch2* Target;
            iTJSDispatch2* Source;
            ttstr       EventName;
            tjs_uint32        Tag;
            tjs_uint      NumArgs;
            tTJSVariant*     Args;
            tjs_uint32      Flags;
            tjs_uint64   Sequence;

            inline ~tTVPEvent() noexcept
            {
                if(this->Args != nullptr) delete[] this->Args;
                if(this->Target != nullptr ) this->Target->Release();
                if(this->Source != nullptr ) this->Source->Release();
            }

            static auto GetEventQueue() noexcept -> std::vector<tTVPEvent*>*
            {
                static std::vector<tTVPEvent*>* _ptr{};
                if(_ptr == nullptr)
                {
                    _ptr = k2a::cast_ptr<decltype(_ptr)>(RVA::Events::EventQueue);
                }
                return _ptr;
            }
        };

        [[gnu::noinline]]
        auto post(const event& e) noexcept -> bool
        {
            static void(*_ptr)(iTJSDispatch2*, iTJSDispatch2*, const ttstr&, tjs_uint32, tjs_uint32, tjs_uint, tTJSVariant*){};
            if(_ptr == nullptr)
            {
                _ptr = k2a::cast_ptr<decltype(_ptr)>(RVA::Events::PostEvent);
            }
            return bool{ _ptr != nullptr ? (_ptr(e.source, e.target, *e.eventname, e.tag, e.flag, e.numargs, e.args), true) : false };
        }

        [[gnu::noinline]]
        auto in_queue(const uniref_event e) noexcept -> std::optional<bool>
        {
            std::vector<tTVPEvent*>* queue{ tTVPEvent::GetEventQueue() };
            if(queue == nullptr)
            {
                return std::nullopt;
            }

            for (auto i = queue->begin(); i != queue->end(); i++)
            {
                const bool equals
                {
                    e->Source    == (*i)->Source    &&
                    e->Target    == (*i)->Target    &&
                    e->EventName == (*i)->EventName &&
                    ((e->tag == 0) ? true : (e->tag == (*i)->Tag))
                };

                if (equals)
                {
                    return true;
                }
            }
            return false;
        }

        [[gnu::noinline]]
        auto get_count(const uniref_event e) noexcept -> std::optional<tjs_int>
        {
            std::vector<tTVPEvent*>* queue{ tTVPEvent::GetEventQueue() };
            if(queue == nullptr)
            {
                return std::nullopt;
            }

            tjs_int result{};
            for (auto i = queue->begin(); i != queue->end(); i++)
            {
                const bool equals
                {
                    e->Source    == (*i)->Source    &&
                    e->Target    == (*i)->Target    &&
                    e->EventName == (*i)->EventName &&
                    ((e->tag == 0) ? true : (e->tag == (*i)->Tag))
                };

                if (equals)
                {
                    result++;
                }
            }
            return result;
        }

        [[gnu::noinline]]
        auto cancel(const uniref_event e) noexcept-> std::optional<tjs_int>
        {
            std::vector<tTVPEvent*>* queue{ tTVPEvent::GetEventQueue() };
            if(queue == nullptr)
            {
                return std::nullopt;
            }
            tjs_int count{};
            for (auto i = queue->begin(); i !=  queue->end();)
            {
                const bool equals
                {
                    e->Source    == (*i)->Source    &&
                    e->Target    == (*i)->Target    &&
                    e->EventName == (*i)->EventName &&
                    ((e->Tag == 0) ? true : (e->Tag == (*i)->Tag))
                };

                if (equals)
                {
                    tTVPEvent* const ev{ *i };
                    i = queue->erase(i);
                    delete ev;
                    count++;
                }
                else
                {
                    i++;
                }
            }
            return count;
        }

        [[gnu::noinline]]
        auto cancel_tag(iTJSDispatch2* source, iTJSDispatch2* target, tjs_uint32 tag) noexcept -> std::optional<tjs_int>
        {
            std::vector<tTVPEvent*>* queue{ tTVPEvent::GetEventQueue() };
            if(queue == nullptr)
            {
                return std::nullopt;
            }

            tjs_int count{};
            for (auto i = queue->begin(); i != queue->end();)
            {
                const bool equals
                {
                    source == (*i)->Source &&
                    target == (*i)->Target &&
                    ((tag == 0) ? true : (tag == (*i)->Tag))
                };

                if (equals)
                {
                    tTVPEvent* const ev{ *i };
                    i = queue->erase(i);
                    delete ev;
                    count++;
                }
                else
                {
                    i++;
                }
            }
            return count;
        }

        [[gnu::noinline]]
        auto cancel_source(iTJSDispatch2* source) noexcept -> std::optional<tjs_int>
        {
           std::vector<tTVPEvent*>* queue{ tTVPEvent::GetEventQueue() };
           if(queue == nullptr)
           {
               return std::nullopt;
           }

           tjs_int count{};
           for (auto i = queue->begin(); i != queue->end();)
           {
               if (source == (*i)->Source)
               {
                   tTVPEvent* const ev{ *i };
                   i = queue->erase(i);
                   delete ev;
                   count++;
               }
               else
               {
                   i++;
               }
           }
           return count;
        }

        [[gnu::noinline]]
        auto create_object(const tjs_char* type, iTJSDispatch2* targthis, iTJSDispatch2* targ)
             noexcept -> std::optional<iTJSDispatch2*>
        {

            static ttstr   type_name{ TJS_W("type")   };
            static ttstr target_name{ TJS_W("target") };

            iTJSDispatch2* object{ ::TJSCreateDictionaryObject() };

            {
                tTJSVariant val{ type };
                const tjs_error error
                {
                    object->PropSet(TJS_MEMBERENSURE|TJS_IGNOREPROP, type_name.c_str(), type_name.GetHint(), &val, object)
                };

                if(TJS_FAILED(error))
                {
                    object->Release();
                    return std::nullopt;
                }
            }

            {
                tTJSVariant val{ targthis, targ };
                const tjs_error error
                {
                    object->PropSet(TJS_MEMBERENSURE|TJS_IGNOREPROP, target_name.c_str(), target_name.GetHint(), &val, object)
                };

                if(TJS_FAILED(error))
                {
                    object->Release();
                    return std::nullopt;
                }
            }

            return object;
        }

        template<class T, uintptr_t ptr>
        struct event_vector
        {
            using vector_t = std::vector<T>;

             [[gnu::noinline]]
            static auto get() noexcept -> vector_t*
            {
                static vector_t* _ptr{};
                if(_ptr == nullptr)
                {
                    _ptr = k2a::cast_ptr<vector_t*>(ptr);
                }
                return _ptr;
            };

            [[gnu::noinline]]
            static auto add(const T hook) noexcept -> bool
            {
                if(hook == nullptr)
                {
                    return false;
                }

                vector_t* const vector{ event_vector<T, ptr>::get() };
                if(vector == nullptr)
                {
                    return false;
                }

                auto it{ std::ranges::find(*vector, nullptr) };
                if (it != vector->end())
                {
                    *it = hook;
                    return true;
                }
                vector->push_back(hook);
                return true;
            }

            [[gnu::noinline]]
            static auto remove(const T hook) noexcept -> bool
            {
                if(hook == nullptr)
                {
                    return false;
                }
                vector_t* const vector{ event_vector<T, ptr>::get() };
                if(vector == nullptr)
                {
                    return false;
                }

                auto it{ std::ranges::find(*vector, hook) };
                if (it != vector->end())
                {
                    *it = nullptr;
                    return true;
                }
                return false;
            }
        };

        using continuous_event_vector = event_vector<const continuous_callback*, RVA::Events::ContinuousEventVector>;
        using compact_event_vector    = event_vector<const compact_callback*,    RVA::Events::CompactEventVector>;

        [[gnu::noinline]]
        auto add_continuous_hook(const continuous_callback* hook) noexcept -> bool
        {
            static void(*begin_continuous_event)(void){};
            if(begin_continuous_event == nullptr)
            {
                k2a::cast_ptr(RVA::Events::BeginContinuousEvent, begin_continuous_event);
            }

            if(begin_continuous_event != nullptr)
            {
                begin_continuous_event();
            }
            return continuous_event_vector::add(hook);
        }

        auto remove_continuous_hook(const continuous_callback* hook) noexcept -> bool
        {
            return continuous_event_vector::remove(hook);
        }

        auto add_compact_hook(const compact_callback* hook) noexcept -> bool
        {
            return compact_event_vector::add(hook);
        }

        auto remove_compact_hook(const compact_callback* hook) noexcept -> bool
        {
            return compact_event_vector::remove(hook);
        }

        auto set_system_disabled_state(bool state) noexcept -> bool
        {
            static void(*_ptr)(bool){};
            if(_ptr == nullptr)
            {
                _ptr = k2a::cast_ptr<decltype(_ptr)>(RVA::Events::SetSystemEventDisabledState);
            }
            return bool{ _ptr != nullptr ? (_ptr(state), true): false };
        }

        auto get_system_disabled_state() noexcept -> std::optional<bool>
        {
            static bool(*_ptr)(void ){};
            if(_ptr == nullptr)
            {
                _ptr = k2a::cast_ptr<decltype(_ptr)>(RVA::Events::GetSystemEventDisabledState);
            }
            if( _ptr != nullptr)
            {
                return _ptr();
            }
            return std::nullopt;
        }
    }

    namespace sound
    {
        [[gnu::noinline]]
        auto pcm::to_16bits(tjs_int16* output, const void* input, tjs_int channels, tjs_int bytespersample,
             tjs_int bitspersample, bool isfloat, tjs_int count, bool downmix) noexcept -> bool
        {
            if(output == nullptr || input == nullptr || count == 0)
            {
                return false;
            }

            if(isfloat)
            {
                TVP::Sound::ConvertFloatPCMTo16bits(output, (const float *)input, channels, count, downmix);
                return true;
            }
            else
            {
                return TVP::Sound::ConvertIntegerPCMTo16bits(output, input, bytespersample, bitspersample, channels, count, downmix);
            }
        }

        [[gnu::noinline]]
        auto pcm::to_float(float* output, const void* input, tjs_int channels, tjs_int bytespersample,
             tjs_int bitspersample, bool isfloat, tjs_int count) noexcept -> bool
        {
            if(output == nullptr || input == nullptr || count == 0)
            {
                return false;
            }
            if(isfloat)
            {
                std::memcpy(output, input, sizeof(float)*channels * count);
                return true;
            }
            else
            {
                return TVP::Sound::ConvertIntegerPCMToFloat(output, input, bytespersample, bitspersample, channels, count);
            }
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
    auto log(const ttstr &line, bool appendtoimportant) noexcept -> bool
    {
        static void(*_ptr)(const ttstr&, bool){};
        if(_ptr == nullptr)
        {
            _ptr = k2a::cast_ptr<decltype(_ptr)>(RVA::AddLog);
        }
        return bool{ _ptr != nullptr ? (_ptr(line, appendtoimportant), true) : false };
    }

    auto important_log(const ttstr& line) noexcept -> bool
    {
        return log(line, true);
    }

    auto inputbox(ttstr& text, const ttstr& caption, const ttstr& prompt, const std::vector<ttstr>& vecButtons) noexcept -> std::optional<int>
    {
        static int(*_ptr)(ttstr&, const ttstr&, const ttstr&, const std::vector<ttstr>&){};
        if(_ptr == nullptr && !k2a::cast_ptr(_ptr, RVA::ShowSimpleInputBox))
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
        static int(*_ptr)(const char*, const char*, unsigned int, const char**){};
        if(_ptr == nullptr && !k2a::cast_ptr(_ptr, RVA::ShowSimpleMessageBox))
        {
           return std::nullopt;
        }

        std::string  pszText{    text.AsNarrowStdString() };
        std::string pszTitle{ caption.AsNarrowStdString() };
        std::vector<const char*> btnText{};
        std::vector<std::string> btnTextHold{};
        btnText.reserve(vecButtons.size());
        btnTextHold.reserve(vecButtons.size());
        for (const ttstr &btn : vecButtons)
        {
            btnTextHold.emplace_back(btn.AsStdString());
            btnText.emplace_back(btnTextHold.back().c_str());
        }
        return _ptr(pszText.c_str(), pszTitle.c_str(), btnText.size(), btnText.data());
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
        static ttstr(*_ptr)(void){};
        if(_ptr == nullptr && !k2a::cast_ptr(_ptr, RVA::GetAboutString))
        {
            return std::nullopt;
        }
        return _ptr();
    }

    [[gnu::noinline]]
    auto get_version_string() noexcept -> std::optional<ttstr>
    {
        static ttstr(*_ptr)(void){};
        if(_ptr == nullptr && !k2a::cast_ptr(_ptr, RVA::GetVersionString))
        {
            return std::nullopt;
        }
        return _ptr();
    }

    [[gnu::noinline]]
    auto get_version_information() noexcept -> std::optional<ttstr>
    {
        static ttstr(*_ptr)(void){};
        if(_ptr == nullptr && !k2a::cast_ptr(_ptr, RVA::GetVersionInformation))
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
        tjs_int* _major{};
        if(k2a::cast_ptr(_major, RVA::VersionMajor))
        {
            major = *_major;
        }

        tjs_int* _minor{};
        if(k2a::cast_ptr(_minor, RVA::VersionMinor))
        {
            minor = *_minor;
        }

        tjs_int* _release{};
        if(k2a::cast_ptr(_release, RVA::VersionRelease))
        {
            release = *_release;
        }

        tjs_int* _build{};
        if(k2a::cast_ptr(_build, RVA::VersionBuild))
        {
            build = *_build;
        }

        return bool
        {
            _major   == nullptr || _minor == nullptr ||
            _release == nullptr || _build == nullptr
        };
    }

    [[gnu::noinline]]
    auto get_random_bits128(void* dest) noexcept -> bool
    {
        static void(*_ptr)(void*){};
        if(_ptr == nullptr)
        {
            _ptr = k2a::cast_ptr<decltype(_ptr)>(RVA::GetRandomBits128);
        }
        return bool{ _ptr != nullptr ? (_ptr(dest), true) : false };
    }

    [[gnu::noinline]]
    auto get_command_line(const tjs_char* name, tTJSVariant* value) noexcept -> std::optional<bool>
    {
        static bool(*_ptr)(const tjs_char*, tTJSVariant*){};
        if(_ptr == nullptr)
        {
            _ptr = k2a::cast_ptr<decltype(_ptr)>(RVA::GetCommandLine);
        }

        if(_ptr != nullptr)
        {
            return _ptr(name, value);
        }

        return std::nullopt;
    }

    [[gnu::noinline]]
    auto set_command_line(const tjs_char* name, const ttstr& value) noexcept -> bool
    {
        static void(*_ptr)(const tjs_char*, const ttstr&){};

        if(_ptr == nullptr)
        {
            _ptr = k2a::cast_ptr<decltype(_ptr)>(RVA::SetCommandLine);
        }

        if(_ptr != nullptr)
        {
            return _ptr(name, value), true;
        }

        return false;
    }

    [[gnu::noinline]]
    auto get_command_line_argument_generation() noexcept -> std::optional<tjs_int>
    {
        static tjs_int* _ptr{};
        if(_ptr == nullptr && !k2a::cast_ptr(_ptr, RVA::CommandLineArgumentGeneration))
        {
            return std::nullopt;
        }
        return *_ptr;
    }

    [[gnu::noinline]]
    auto get_tick_count() noexcept -> std::optional<tjs_uint64>
    {
        static tjs_uint64(*_ptr)(void){};
        if(_ptr == nullptr)
        {
            _ptr = k2a::cast_ptr<decltype(_ptr)>(RVA::GetTickCount);
        }
        if(_ptr != nullptr)
        {
            return _ptr();
        }
        return std::nullopt;
    }
}

