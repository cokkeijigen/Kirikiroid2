#pragma once
#include <cstdint>
#include <tjs.h>

namespace kr2android::tvp::rva
{
    consteval auto TargetRVA(uintptr_t arm64v8a, uintptr_t armeabiv7a) -> uintptr_t
    {
        #if defined(__aarch64__)
        return arm64v8a;
        #elif defined(__arm__)
        return armeabiv7a;
        #else
        return 0;
        #endif
    }

    namespace Scripts
    {
        static inline constexpr uintptr_t           ScriptEngine{ TargetRVA(0x1ADFFD0, 0) };
        static inline constexpr uintptr_t      GetScriptDispatch{ TargetRVA(0x08E4000, 0) };
        static inline constexpr uintptr_t ScriptEngine_tTJS_Dump{ TargetRVA(0x097DF60, 0) };
        static inline constexpr uintptr_t GetDefaultReadEncoding{ TargetRVA(0x08F72C4, 0) };
        static inline constexpr uintptr_t SetDefaultReadEncoding{ TargetRVA(0x08F6EDC, 0) };
    }

    namespace TJSString
    {
        static inline constexpr uintptr_t       ProjectDir{ TargetRVA(0x1AF01A8, 0) };
        static inline constexpr uintptr_t NativeProjectDir{ TargetRVA(0x1AF1300, 0) };
    };

    namespace Graphic
    {
        static inline constexpr uintptr_t       GraphicType{ TargetRVA(0x1AD84B8, 0) };
        static inline constexpr uintptr_t ClearGraphicCache{ TargetRVA(0x07EC31C, 0) };

        namespace NativeBaseBitmap
        {
            static inline constexpr uintptr_t     GetWidth{ TargetRVA(0x0A74E90, 0) };
            static inline constexpr uintptr_t    GetHeight{ TargetRVA(0x0A75020, 0) };
            static inline constexpr uintptr_t  GetScanLine{ TargetRVA(0x0A75330, 0) };
        }
    };

    namespace StorageMediaManager
    {
        static inline constexpr uintptr_t             MediaManager{ TargetRVA(0x1AE0008, 0) };
        static inline constexpr uintptr_t     NormalizeStorageName{ TargetRVA(0x08E93D0, 0) };
        static inline constexpr uintptr_t      SetCurrentDirectory{ TargetRVA(0x08EA130, 0) };
        static inline constexpr uintptr_t GetLocallyAccessibleName{ TargetRVA(0x08EA5E0, 0) };
    };

    namespace XP3Archive
    {
        static inline constexpr uintptr_t ExtractionFilter{ TargetRVA(0x1AF0240, 0) };
        static inline constexpr uintptr_t    ContentFilter{ TargetRVA(0x1AF0248, 0) };
    };

    namespace Storage
    {
        static inline constexpr uintptr_t    AddAutoPath{ TargetRVA(0x08EB894, 0) };
        static inline constexpr uintptr_t RemoveAutoPath{ TargetRVA(0x08EBA70, 0) };
        static inline constexpr uintptr_t  GetPlacedPath{ TargetRVA(0x08EBC80, 0) };

        static inline constexpr uintptr_t                  SetCurrentDirectory{ TargetRVA(0x08EA6F8, 0) };
        static inline constexpr uintptr_t                   ClearStorageCaches{ TargetRVA(0x08FD444, 0) };
        static inline constexpr uintptr_t            IsExistentStorageNoSearch{ TargetRVA(0x08EB4C0, 0) };
        static inline constexpr uintptr_t IsExistentStorageNoSearchNoNormalize{ TargetRVA(0x08EAF88, 0) };
    }

    namespace Stream
    {
        static inline constexpr uintptr_t    CreateTextStreamForRead{ TargetRVA(0x8F6438, 0) };
        static inline constexpr uintptr_t   CreateTextStreamForWrite{ TargetRVA(0x8F6B14, 0) };
        static inline constexpr uintptr_t  CreateBinaryStreamForRead{ TargetRVA(0x8DBE98, 0) };
        static inline constexpr uintptr_t CreateBinaryStreamForWrite{ TargetRVA(0x8DBFB4, 0) };
    }

    namespace Events
    {
        static inline constexpr uintptr_t        PostEvent{ TargetRVA(0x08DC704, 0) };
        static inline constexpr uintptr_t       EventQueue{ TargetRVA(0x1ADFEC0, 0) };
        static inline constexpr uintptr_t        BeginContinuousEvent{ TargetRVA(0x0906284, 0) };
        static inline constexpr uintptr_t       ContinuousEventVector{ TargetRVA(0x1ADFF48, 0) };
        static inline constexpr uintptr_t          CompactEventVector{ TargetRVA(0x1ADFF80, 0) };
        static inline constexpr uintptr_t SetSystemEventDisabledState{ TargetRVA(0x905EC8, 0) };
        static inline constexpr uintptr_t GetSystemEventDisabledState{ TargetRVA(0x905EEC, 0) };
    }

    static inline constexpr uintptr_t GetRandomBits128{ TargetRVA(0x0A28F38, 0) };
    static inline constexpr uintptr_t   GetCommandLine{ TargetRVA(0x090DE30, 0) };
    static inline constexpr uintptr_t   SetCommandLine{ TargetRVA(0x090FCA0, 0) };
    static inline constexpr uintptr_t     GetTickCount{ TargetRVA(0x0A2A4DC, 0) };
}

namespace             TVP::RVA { using namespace kr2android::tvp::rva; };
namespace kr2android::tvp::RVA { using namespace kr2android::tvp::rva; }

#define tvprva(arm64v8a, armeabiv7a) TVP::RVA::TargetRVA(arm64v8a, armeabiv7a)
#define TVPRVA(arm64v8a, armeabiv7a) TVP::RVA::TargetRVA(arm64v8a, armeabiv7a)