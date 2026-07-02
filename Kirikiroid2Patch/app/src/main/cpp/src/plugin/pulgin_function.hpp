#pragma once
#include <optional>
#include <pulgin_type.hpp>

namespace TVP
{

    extern auto   GetAppPath() noexcept -> ttstr;
    extern auto  GetBasePath() noexcept -> ttstr;
    extern auto GetLocalName(ttstr& name) noexcept -> std::optional<ttstr>;

    extern auto       AddAutoPath(const ttstr& path) noexcept -> bool;
    extern auto    RemoveAutoPath(const ttstr& path) noexcept -> bool;
    extern auto     GetPlacedPath(const ttstr& path) noexcept -> std::optional<ttstr>;
    extern auto IsExistentStorage(const ttstr& path) noexcept -> std::optional<bool>;

    extern auto  ExtractStorageExt(const ttstr& name) noexcept -> ttstr;
    extern auto ExtractStorageName(const ttstr& name) noexcept -> ttstr;
    extern auto ExtractStoragePath(const ttstr& name) noexcept -> ttstr;
    extern auto     ChopStorageExt(const ttstr& name) noexcept -> ttstr;

    extern auto             IsExistentStorageNoSearch(const ttstr& name) noexcept -> std::optional<bool>;
    extern auto  IsExistentStorageNoSearchNoNormalize(const ttstr& name) noexcept -> std::optional<bool>;

    extern auto   ClearStorageCaches() noexcept -> bool;
    extern auto  SetCurrentDirectory(const ttstr& directory) noexcept -> bool;
    extern auto NormalizeStorageName(const ttstr&      name) noexcept -> std::optional<ttstr>;

    extern auto    CreateTextStreamForRead(const ttstr& name, const ttstr& modestr) noexcept -> iTJSTextReadStream*;
    extern auto   CreateTextStreamForWrite(const ttstr& name, const ttstr& modestr) noexcept -> iTJSTextWriteStream*;
    extern auto  CreateBinaryStreamForRead(const ttstr& name, const ttstr& modestr) noexcept -> tTJSBinaryStream*;
    extern auto CreateBinaryStreamForWrite(const ttstr& name, const ttstr& modestr) noexcept -> tTJSBinaryStream*;

    namespace StorageMedia
    {
        using iTVPStorageLister = k2a::tvp::storage::iStorageLister;
        using iTVPStorageMedia  = k2a::tvp::storage::iStorageMedia;
        extern auto   RegisterStorageMedia(iTVPStorageMedia* media) noexcept -> bool;
        extern auto UnregisterStorageMedia(iTVPStorageMedia* media) noexcept -> bool;
    }
    using namespace StorageMedia;

    namespace XP3Archive
    {
        using tTVPXP3ExtractionFilterInfo    = k2a::tvp::xp3::ExtractionFilterInfo;
        using tTVPXP3ArchiveExtractionFilter = k2a::tvp::xp3::ExtractionFilterType;
        using tTVPXP3ArchiveContentFilter    = k2a::tvp::xp3::ContentFilterType;
        extern auto GetXP3ArchiveExtractionFilter() noexcept -> tTVPXP3ArchiveExtractionFilter;
        extern auto    GetXP3ArchiveContentFilter() noexcept -> tTVPXP3ArchiveContentFilter;
        extern auto SetXP3ArchiveExtractionFilter(tTVPXP3ArchiveExtractionFilter filter) noexcept -> bool;
        extern auto    SetXP3ArchiveContentFilter(tTVPXP3ArchiveContentFilter    filter) noexcept -> bool;
    }
    using namespace XP3Archive;

    namespace Graphic
    {
        using tTVPGraphicLoadingHandler       = Graphic::LoadingHandler;
        using tTVPGraphicHeaderLoadingHandler = Graphic::HeaderLoadingHandler;
        using tTVPGraphicSaveHandler          = Graphic::SaveHandler;
        using tTVPGraphicAcceptSaveHandler    = Graphic::AcceptSaveHandler;

        extern auto RegisterGraphicLoadingHandler
        (
            const ttstr&                      name,
            tTVPGraphicLoadingHandler      loading,
            tTVPGraphicHeaderLoadingHandler header,
            tTVPGraphicSaveHandler            save,
            tTVPGraphicAcceptSaveHandler    accept,
            void*                       formatdata
        ) noexcept -> bool;

        extern auto UnregisterGraphicLoadingHandler
        (
            const ttstr&                      name,
            tTVPGraphicLoadingHandler      loading,
            tTVPGraphicHeaderLoadingHandler header,
            tTVPGraphicSaveHandler            save,
            tTVPGraphicAcceptSaveHandler    accept,
            void*                       formatdata
        ) noexcept -> bool;

        extern auto ClearGraphicCache() noexcept -> bool;
    }

    using namespace Graphic;

    namespace Scripts
    {
        extern auto   GetScriptEngine() noexcept -> tTJS*;
        extern auto GetScriptDispatch() noexcept -> iTJSDispatch2*;

        extern auto ExecuteScript(const ttstr& content, tTJSVariant* result) noexcept -> bool;
        extern auto ExecuteScript(const ttstr& content, iTJSDispatch2* context, tTJSVariant* result) noexcept -> bool;

        extern auto ExecuteScript(const ttstr& content, const ttstr& name, tjs_int lineofs,
               tTJSVariant* result) noexcept -> bool;

        extern auto ExecuteScript(const ttstr& content, const ttstr& name, tjs_int lineofs,
               iTJSDispatch2* context, tTJSVariant* result) noexcept -> bool;

        extern auto ExecuteExpression(const ttstr& content, tTJSVariant* result) noexcept -> bool;

        extern auto ExecuteExpression(const ttstr& content, iTJSDispatch2* context,
               tTJSVariant* result) noexcept -> bool;

        extern auto ExecuteExpression(const ttstr& content, const ttstr& name, tjs_int lineofs,
               tTJSVariant* result) noexcept -> bool;

        extern auto ExecuteExpression(const ttstr& content, const ttstr& name, tjs_int lineofs,
               iTJSDispatch2* context, tTJSVariant* result) noexcept -> bool;

        extern auto  ExecuteStorage(const ttstr& name, tTJSVariant* result, bool isexpression,
               const tjs_char* modestr) noexcept -> bool;

        extern auto  ExecuteStorage(const ttstr& name, iTJSDispatch2* context, tTJSVariant* result,
               bool isexpression, const tjs_char* modestr) noexcept -> bool;

        extern auto ExecuteBytecode(const tjs_uint8* content, size_t length, iTJSDispatch2* context,
               tTJSVariant* result, const tjs_char* name) noexcept -> bool;

        extern auto DumpScriptEngine(std::string_view name, bool global) noexcept -> bool;
        extern auto DumpScriptEngine(std::string_view name) noexcept -> bool;
        extern auto DumpScriptEngine(bool global) noexcept -> bool;
        extern auto DumpScriptEngine() noexcept -> bool;

        extern auto RegisterGlobalObject(const tjs_char* name,iTJSDispatch2* dsp) noexcept -> bool;
        extern auto RemoveGlobalObject  (const tjs_char* name) noexcept -> bool;

        extern auto GetDefaultReadEncoding() noexcept -> std::optional<ttstr>;
        extern auto SetDefaultReadEncoding(const ttstr& name) noexcept -> bool;

    }
    using namespace Scripts;

    namespace Events
    {
        using Event = k2a::tvp::event::flag_t;

        extern auto PostEvent(iTJSDispatch2*     source, iTJSDispatch2* target, const ttstr& eventname,
               tjs_uint32 tag, tjs_uint32 flag, tjs_uint numargs, tTJSVariant* args) noexcept -> bool;

        extern auto CancelEvents(iTJSDispatch2* source, iTJSDispatch2* target, const ttstr& eventname,
               tjs_uint32 tag) noexcept -> std::optional<tjs_int>;

        extern auto AreEventsInQueue(iTJSDispatch2*   source, iTJSDispatch2* target, const ttstr& eventname,
               tjs_uint32 tag) noexcept -> std::optional<bool>;

        extern auto CountEventsInQueue(iTJSDispatch2* source, iTJSDispatch2* target, const ttstr& eventname,
               tjs_uint32 tag) noexcept -> std::optional<tjs_int>;

        extern auto CancelEventsByTag(iTJSDispatch2*  source, iTJSDispatch2* target, tjs_uint32 tag)
               noexcept -> std::optional<tjs_int>;

        extern auto CancelSourceEvents(iTJSDispatch2* source) noexcept -> std::optional<tjs_int>;

        extern auto CreateEventObject(const tjs_char* type, iTJSDispatch2* targthis, iTJSDispatch2* targ)
               noexcept -> std::optional<iTJSDispatch2*>;

        using ContinuousEventCallbackIntf = k2a::tvp::events::ContinuousCallback;
        using CompactEventCallbackIntf    = k2a::tvp::events::CompactCallback;
        extern auto    AddContinuousEventHook(const ContinuousEventCallbackIntf* hook) noexcept -> bool;
        extern auto RemoveContinuousEventHook(const ContinuousEventCallbackIntf* hook) noexcept -> bool;
        extern auto       AddCompactEventHook(const CompactEventCallbackIntf*    hook) noexcept -> bool;
        extern auto    RemoveCompactEventHook(const CompactEventCallbackIntf*    hook) noexcept -> bool;

        extern auto SetSystemEventDisabledState(bool state) noexcept -> bool;
        extern auto GetSystemEventDisabledState() noexcept -> std::optional<bool>;
    }
    using namespace Events;

    namespace Sound
    {
        using tTVPWaveFormat = k2a::tvp::sound::wave_format;

        extern auto ConvertPCMTo16bits(tjs_int16* output, const void* input, const tTVPWaveFormat& format,
                    tjs_int count, bool downmix) noexcept -> bool;

        extern auto ConvertPCMTo16bits(tjs_int16* output, const void* input, tjs_int channels, tjs_int bytespersample,
                    tjs_int bitspersample, bool isfloat, tjs_int count, bool downmix) noexcept -> bool;

        extern auto ConvertPCMToFloat(float* output, const void* input, const tTVPWaveFormat& format,
                    tjs_int count) noexcept -> bool;
        extern auto ConvertPCMToFloat(float* output, const void* input, tjs_int channels, tjs_int bytespersample,
                    tjs_int bitspersample, bool isfloat, tjs_int count) noexcept -> bool;
    }
    using namespace Sound;

    // ========== 剪贴板 ==========
    bool ClipboardHasFormat(tTVPClipboardFormat);
    void ClipboardSetText(const ttstr &);
    bool ClipboardGetText(ttstr &);

    // ========== 日志/消息 ==========
    void AddLog(const ttstr &);
    void AddImportantLog(const ttstr &);
    ttstr FormatMessage(const tjs_char *,const ttstr &);
    ttstr FormatMessage(const tjs_char *,const ttstr &,const ttstr &);
    void ThrowExceptionMessage(const tjs_char *);
    void ThrowExceptionMessage(const tjs_char *,const ttstr &,tjs_int);
    void ThrowExceptionMessage(const tjs_char *,const ttstr &);
    void ThrowExceptionMessage(const tjs_char *,const ttstr &,const ttstr &);
    void CreateMessageMapFile(const ttstr &);
    int TVPShowSimpleMessageBox(const ttstr & text, const ttstr & caption, const std::vector<ttstr> &vecButtons);
    int TVPShowSimpleInputBox(ttstr &text, const ttstr &caption, const ttstr &prompt, const std::vector<ttstr> &vecButtons);

    // ========== 平台/版本 ==========
    ttstr GetPlatformName();
    ttstr GetOSName();
    ttstr GetAboutString();
    ttstr GetVersionInformation();
    ttstr GetVersionString();
    void GetSystemVersion(tjs_int &,tjs_int &,tjs_int &,tjs_int &);
    void GetTJSVersion(tjs_int &,tjs_int &,tjs_int &);
    tjs_uint32 GetCPUType();
    tjs_int GetProcessorNum();
    tjs_int GetThreadNum();
    bool GetFileVersionOf(const wchar_t *,tjs_int &,tjs_int &,tjs_int &,tjs_int &);

    // ========== 命令行 ==========
    extern auto GetCommandLine(const tjs_char* name, tTJSVariant* value) -> std::optional<bool>;
    extern auto SetCommandLine(const tjs_char* name, const ttstr& value) -> bool;

    tjs_int GetCommandLineArgumentGeneration();

    // ========== 随机数 ==========
    void PushEnvironNoise(const void *,tjs_int);
    extern auto GetRandomBits128(void* dest) noexcept -> bool;

    // ========== 时间 ==========
    extern auto GetTickCount() -> std::optional<tjs_uint64>;

    // ========== 线程/任务 ==========
    void BeginThreadTask(tjs_int);
    void EndThreadTask();

    // ========== 输入 ==========
    bool GetAsyncKeyState(tjs_uint,bool);
    tjs_uint32 GetCurrentShiftKeyState();

    // ========== 杂项 ==========
    ttstr GetTemporaryName();
    void Breathe();
    bool GetBreathing();

}