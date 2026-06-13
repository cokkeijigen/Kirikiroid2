#pragma once
#include <optional>
#include <pulgin_type.hpp>

namespace TVP
{

    extern auto       AddAutoPath(const ttstr& path) noexcept -> bool;
    extern auto    RemoveAutoPath(const ttstr& path) noexcept -> bool;
    extern auto     GetPlacedPath(const ttstr& path) noexcept -> std::optional<ttstr>;
    extern auto IsExistentStorage(const ttstr& path) noexcept -> std::optional<bool>;

    extern auto   GetAppPath() noexcept -> std::optional<ttstr>;
    extern auto  GetGamePath() noexcept -> std::optional<ttstr>;
    extern auto GetLocalName(ttstr& name) noexcept -> std::optional<ttstr>;

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

    extern auto GetDefaultReadEncoding() noexcept -> const tjs_char*;
    extern auto SetDefaultReadEncoding(const ttstr& name) noexcept -> bool;

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


//    IStream * CreateIStream(const ttstr &,tjs_uint32);
//    tTJSBinaryStream * CreateBinaryStreamAdapter(IStream *);


    // ========== 脚本执行 ==========
    iTJSDispatch2* GetScriptDispatch();
    void ExecuteScript(const ttstr &,tTJSVariant *);
    void ExecuteScript(const ttstr &,iTJSDispatch2 *,tTJSVariant *);
    void ExecuteExpression(const ttstr &,tTJSVariant *);
    void ExecuteExpression(const ttstr &,iTJSDispatch2 *,tTJSVariant *);
    void ExecuteScript(const ttstr &,const ttstr &,tjs_int,tTJSVariant *);
    void ExecuteScript(const ttstr &,const ttstr &,tjs_int,iTJSDispatch2 *,tTJSVariant *);
    void ExecuteExpression(const ttstr &,const ttstr &,tjs_int,tTJSVariant *);
    void ExecuteExpression(const ttstr &,const ttstr &,tjs_int,iTJSDispatch2 *,tTJSVariant *);
    void ExecuteStorage(const ttstr &,tTJSVariant *,bool,const tjs_char *);
    void ExecuteStorage(const ttstr &,iTJSDispatch2 *,tTJSVariant *,bool,const tjs_char *);
    void DumpScriptEngine();
    void ExecuteBytecode(const tjs_uint8 *,size_t,iTJSDispatch2 *,tTJSVariant *,const tjs_char *);

    // ========== 事件系统 ==========
    void PostEvent(iTJSDispatch2 *,iTJSDispatch2 *,ttstr &,tjs_uint32,tjs_uint32,tjs_uint,tTJSVariant *);
    tjs_int CancelEvents(iTJSDispatch2 *,iTJSDispatch2 *,const ttstr &,tjs_uint32);
    bool AreEventsInQueue(iTJSDispatch2 *,iTJSDispatch2 *,const ttstr &,tjs_uint32);
    tjs_int CountEventsInQueue(iTJSDispatch2 *,iTJSDispatch2 *,const ttstr &,tjs_uint32);
    void CancelEventsByTag(iTJSDispatch2 *,iTJSDispatch2 *,tjs_uint32);
    void CancelSourceEvents(iTJSDispatch2 *);
    iTJSDispatch2 * CreateEventObject(const tjs_char *,iTJSDispatch2 *,iTJSDispatch2 *);
    void AddContinuousEventHook(tTVPContinuousEventCallbackIntf *);
    void RemoveContinuousEventHook(tTVPContinuousEventCallbackIntf *);
    void AddCompactEventHook(tTVPCompactEventCallbackIntf *);
    void RemoveCompactEventHook(tTVPCompactEventCallbackIntf *);

    // ========== 图形/图像加载 ==========



    iTVPScanLineProvider * SLPLoadImage(const ttstr &,tjs_int,tjs_uint32,tjs_uint,tjs_uint);
    void AddTransHandlerProvider(iTVPTransHandlerProvider *);
    void RemoveTransHandlerProvider(iTVPTransHandlerProvider *);

    // ========== 音频/视频 ==========
    void ConvertPCMTo16bits(tjs_int16 *,const void *,const tTVPWaveFormat &,tjs_int,bool);
    void ConvertPCMTo16bits(tjs_int16 *,const void *,tjs_int,tjs_int,tjs_int,bool,tjs_int,bool);
    void ConvertPCMToFloat(float *,const void *,tjs_int,tjs_int,tjs_int,bool,tjs_int);
    void ConvertPCMToFloat(float *,const void *,const tTVPWaveFormat &,tjs_int);
    void ReleaseDirectSound();

    // ========== 窗口/应用消息 ==========
    void ProcessApplicationMessages();
    void HandleApplicationMessage();
    void SetSystemEventDisabledState(bool);
    bool GetSystemEventDisabledState();

    // ========== 全局对象/注册 ==========
    bool RegisterGlobalObject(const tjs_char *,iTJSDispatch2 *);
    bool RemoveGlobalObject(const tjs_char *);
    void DoTryBlock(tTVPTryBlockFunction,tTVPCatchBlockFunction,tTVPFinallyBlockFunction,void *);

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
    void GetRandomBits128(void *);

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
    void PostEvent(iTJSDispatch2 *,iTJSDispatch2 *,ttstr &,tjs_uint32,tjs_uint32,tjs_uint,tTJSVariant *);

}