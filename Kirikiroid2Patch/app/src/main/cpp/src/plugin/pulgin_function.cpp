#include <pulgin_function.hpp>

namespace TVP
{

    auto GetAppPath() noexcept -> ttstr
    {
        return k2a::tvp::system::app_path();
    }

    auto GetBasePath() noexcept -> ttstr
    {
        return k2a::tvp::system::base_path();
    }

    auto GetLocalName(ttstr& name) noexcept -> std::optional<ttstr>
    {
        return k2a::tvp::storage::get_local_name(name);
    }

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

    namespace Scripts
    {
        auto GetScriptEngine() noexcept -> tTJS*
        {
            return k2a::tvp::scripts::get_engine();
        }

        auto GetScriptDispatch() noexcept -> iTJSDispatch2*
        {
            return k2a::tvp::scripts::get_dispatch();
        }

        auto ExecuteScript(const ttstr& content, tTJSVariant* result) noexcept -> bool
        {
            return k2a::tvp::scripts::execute(content, result);
        }

        auto ExecuteScript(const ttstr& content, iTJSDispatch2* context, tTJSVariant* result) noexcept -> bool
        {
            return k2a::tvp::scripts::execute(content, context, result);
        }

        auto ExecuteScript(const ttstr& content, const ttstr& name, tjs_int lineofs, tTJSVariant* result) noexcept -> bool
        {
            return k2a::tvp::scripts::execute(content, name, lineofs, result);
        }

        auto ExecuteScript(const ttstr& content, const ttstr& name, tjs_int lineofs, iTJSDispatch2* context, tTJSVariant* result) noexcept -> bool
        {
            return k2a::tvp::scripts::execute(content, name, lineofs, context, result);
        }

        auto ExecuteExpression(const ttstr& content, tTJSVariant* result) noexcept -> bool
        {
            return k2a::tvp::scripts::execexpr(content, result);
        }

        auto ExecuteExpression(const ttstr& content, iTJSDispatch2* context, tTJSVariant* result) noexcept -> bool
        {
            return k2a::tvp::scripts::execexpr(content, context, result);
        }

        auto ExecuteExpression(const ttstr& content, const ttstr& name, tjs_int lineofs, tTJSVariant* result) noexcept -> bool
        {
            return k2a::tvp::scripts::execexpr(content, name, lineofs, result);
        }

        auto ExecuteExpression(const ttstr& content, const ttstr& name, tjs_int lineofs, iTJSDispatch2* context, tTJSVariant* result) noexcept -> bool
        {
            return k2a::tvp::scripts::execexpr(content, name, lineofs, context, result);
        }

        auto ExecuteStorage(const ttstr& name, tTJSVariant* result, bool isexpression, const tjs_char* modestr) noexcept -> bool
        {
            return k2a::tvp::scripts::load(name, result, isexpression, modestr);
        }

        auto ExecuteStorage(const ttstr& name, iTJSDispatch2* context, tTJSVariant* result, bool isexpression, const tjs_char* modestr) noexcept -> bool
        {
            return k2a::tvp::scripts::load(name, context, result, isexpression, modestr);
        }

        auto ExecuteBytecode(const tjs_uint8* content, size_t length, iTJSDispatch2* context, tTJSVariant* result, const tjs_char* name) noexcept -> bool
        {
            return k2a::tvp::scripts::loadbytes(content, length, context, result, name);
        }

        auto DumpScriptEngine(std::string_view name, bool global) noexcept -> bool
        {
            return k2a::tvp::scripts::dump_engine(name, global);
        }

        auto DumpScriptEngine(std::string_view name) noexcept -> bool
        {
            return k2a::tvp::scripts::dump_engine(name);
        }

        auto DumpScriptEngine(bool global) noexcept -> bool
        {
            return k2a::tvp::scripts::dump_engine(global);
        }

        auto DumpScriptEngine() noexcept -> bool
        {
            return k2a::tvp::scripts::dump_engine();
        }

        auto RegisterGlobalObject(const tjs_char* name,iTJSDispatch2* dsp) noexcept -> bool
        {
            return k2a::tvp::scripts::global::register_object(name, dsp);
        }

        auto RemoveGlobalObject(const tjs_char* name) noexcept -> bool
        {
            return k2a::tvp::scripts::global::remove_object(name);
        }

        auto GetDefaultReadEncoding() noexcept -> std::optional<ttstr>
        {
            return k2a::tvp::scripts::get_text_encoding();
        }

        auto SetDefaultReadEncoding(const ttstr& name) noexcept -> bool
        {
            return k2a::tvp::scripts::set_text_encoding(name);
        }

    }

    namespace Events
    {

        auto PostEvent(iTJSDispatch2* source, iTJSDispatch2* target, const ttstr& eventname,
             tjs_uint32 tag, tjs_uint32 flag, tjs_uint numargs, tTJSVariant* args) noexcept -> bool
        {
            const k2a::tvp::event e
            {
                .source    = source,
                .target    = target,
                .eventname = eventname,
                .tag       = tag,
                .flag      = flag,
                .numargs   = numargs,
                .args      = args
            };
            return k2a::tvp::events::post(e);
        }

        auto AreEventsInQueue(iTJSDispatch2* source, iTJSDispatch2* target, const ttstr& eventname,
             tjs_uint32 tag) noexcept -> std::optional<bool>
        {
            const k2a::tvp::event_base e
            {
                .source    = source,
                .target    = target,
                .eventname = eventname,
                .tag       = tag,
            };
            return k2a::tvp::events::in_queue(e);
        }

        auto CountEventsInQueue(iTJSDispatch2* source, iTJSDispatch2* target, const ttstr& eventname,
               tjs_uint32 tag) noexcept -> std::optional<tjs_int>
        {
            const k2a::tvp::event_base e
            {
                .source    = source,
                .target    = target,
                .eventname = eventname,
                .tag       = tag,
            };
            return k2a::tvp::events::get_count(e);
        }

        auto CancelEvents(iTJSDispatch2* source, iTJSDispatch2* target, const ttstr& eventname,
             tjs_uint32 tag) noexcept -> std::optional<tjs_int>
        {
            const k2a::tvp::event_base e
            {
                .source    = source,
                .target    = target,
                .eventname = eventname,
                .tag       = tag,
            };
            return k2a::tvp::events::cancel(e);
        }

        auto CancelEventsByTag(iTJSDispatch2* source, iTJSDispatch2* target, tjs_uint32 tag) noexcept
              -> std::optional<tjs_int>
        {
            return k2a::tvp::events::cancel_tag(source, target, tag);
        }

        auto CancelSourceEvents(iTJSDispatch2* source) noexcept -> std::optional<tjs_int>
        {
            return k2a::tvp::events::cancel_source(source);
        }

        auto CreateEventObject(const tjs_char* type, iTJSDispatch2* targthis, iTJSDispatch2* targ)
             noexcept ->  std::optional<iTJSDispatch2*>
        {
            return k2a::tvp::events::create_object(type, targthis, targ);
        }

        auto AddContinuousEventHook(const ContinuousEventCallbackIntf* hook) noexcept -> bool
        {
            return k2a::tvp::events::add_continuous_hook(hook);
        }

        auto RemoveContinuousEventHook(const ContinuousEventCallbackIntf* hook) noexcept -> bool
        {
            return k2a::tvp::events::remove_continuous_hook(hook);
        }

        auto AddCompactEventHook(const CompactEventCallbackIntf* hook) noexcept -> bool
        {
            return k2a::tvp::events::add_compact_hook(hook);
        }

        auto RemoveCompactEventHook(const CompactEventCallbackIntf* hook) noexcept -> bool
        {
            return k2a::tvp::events::remove_compact_hook(hook);
        }

        auto SetSystemEventDisabledState(bool state) noexcept -> bool
        {
            return k2a::tvp::events::set_system_disabled_state(state);
        }

        auto GetSystemEventDisabledState() noexcept -> std::optional<bool>
        {
            return k2a::tvp::events::get_system_disabled_state();
        }

    }

    namespace Sound
    {
        auto ConvertPCMTo16bits(tjs_int16* output, const void* input, const tTVPWaveFormat& format,
             tjs_int count, bool downmix) noexcept -> bool
        {
            return k2a::tvp::pcm::to_16bits(output, input, format, count, downmix);
        }

        auto ConvertPCMTo16bits(tjs_int16* output, const void* input, tjs_int channels, tjs_int bytespersample,
             tjs_int bitspersample, bool isfloat, tjs_int count, bool downmix) noexcept -> bool
        {
            return k2a::tvp::pcm::to_16bits(output, input, channels, bytespersample, bitspersample, isfloat, count, downmix);
        }

        auto ConvertPCMToFloat(float* output, const void* input, const tTVPWaveFormat& format, tjs_int count) noexcept -> bool
        {
            return k2a::tvp::pcm::to_float(output, input, format, count);
        }

        auto ConvertPCMToFloat(float* output, const void* input, tjs_int channels, tjs_int bytespersample,
             tjs_int bitspersample, bool isfloat, tjs_int count) noexcept -> bool
        {
            return k2a::tvp::pcm::to_float(output, input, channels, bytespersample, bitspersample, isfloat, count);
        }

    }

    auto AddLog(const ttstr& line, bool appendtoimportant) -> bool
    {
        return k2a::tvp::log(line, appendtoimportant);
    }

    auto AddImportantLog(const ttstr& line) -> bool
    {
        return k2a::tvp::important_log(line);
    }

    auto ShowSimpleInputBox(ttstr& text, const ttstr& caption) noexcept -> std::optional<bool>
    {
         return k2a::tvp::inputbox(text, caption);
    }

    auto ShowSimpleInputBox(ttstr& text, const ttstr& caption, const ttstr& prompt) noexcept -> std::optional<bool>
    {
         return k2a::tvp::inputbox(text, caption, prompt);
    }

    auto ShowSimpleInputBox(ttstr& text, const ttstr& caption, const ttstr& prompt, const std::vector<ttstr>& vecButtons) noexcept -> std::optional<int>
    {
         return k2a::tvp::inputbox(text, caption, prompt, vecButtons);
    }

    auto ShowSimpleInputBox(ttstr& text, const ttstr& caption, const std::vector<ttstr>& vecButtons) noexcept -> std::optional<int>
    {
         return k2a::tvp::inputbox(text, caption, vecButtons);
    }

    auto ShowSimpleMessageBox(const ttstr& text, const ttstr& caption) noexcept -> std::optional<bool>
    {
         return k2a::tvp::messagebox(text, caption);
    }

    auto ShowSimpleMessageBox(const ttstr& text, const ttstr& caption, const std::vector<ttstr>& vecButtons) noexcept -> std::optional<int>
    {
         return k2a::tvp::messagebox(text, caption, vecButtons);
    }

    extern auto ThrowExceptionMessage(const ttstr& msg, bool exit) noexcept -> void
    {
        k2a::tvp::throw_exception_message(msg, exit);
    }

    auto GetAboutString() noexcept -> std::optional<ttstr>
    {
        return k2a::tvp::get_about_string();
    }

    auto GetVersionString() noexcept -> std::optional<ttstr>
    {
        return k2a::tvp::get_version_string();
    }

    auto GetVersionInformation() noexcept -> std::optional<ttstr>
    {
        return k2a::tvp::get_version_information();
    }

    auto GetTJSVersion(tjs_int& major, tjs_int& minor, tjs_int& release) noexcept -> void
    {
        k2a::tvp::get_tjs_version(major, minor, release);
    }

    auto GetSystemVersion(tjs_int& major, tjs_int& minor, tjs_int& release, tjs_int& build) noexcept -> bool
    {
        return k2a::tvp::get_system_version(major, major, release, build);
    }

    auto GetCommandLineArgumentGeneration() noexcept -> std::optional<tjs_int>
    {
        return k2a::tvp::get_command_line_argument_generation();
    }

    auto GetRandomBits128(void* dest) noexcept -> bool
    {
        return k2a::tvp::get_random_bits128(dest);
    }

    auto PushEnvironNoise(const void* buf, const tjs_int bufsize) noexcept -> bool
    {
        return k2a::tvp::push_environ_noise(buf, bufsize);
    }

    auto GetCommandLine(const tjs_char* name, tTJSVariant* value) -> std::optional<bool>
    {
        return k2a::tvp::get_command_line(name, value);
    }

    auto SetCommandLine(const tjs_char* name, const ttstr& value) -> bool
    {
        return k2a::tvp::set_command_line(name, value);
    }

    auto GetAsyncKeyState(const tjs_uint keycode, const bool getcurrent) noexcept -> std::optional<bool>
    {
        return k2a::tvp::get_async_key_state(keycode, getcurrent);
    }

    auto GetCurrentShiftKeyState() noexcept -> std::optional<tjs_uint32>
    {
        return k2a::tvp::get_current_shift_key_state();
    }

    auto GetTickCount() noexcept -> std::optional<tjs_uint64>
    {
        return k2a::tvp::get_tick_count();
    }

    auto ExitApplication() noexcept -> void
    {
        k2a::tvp::exit();
    }
}