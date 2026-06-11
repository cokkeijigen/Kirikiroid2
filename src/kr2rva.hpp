#pragma once
#include <cstdint>
#include <tjs.h>

#define TVPRVA kr2android::tvp::rva::rva
#define tvprva kr2android::tvp::rva::rva

namespace kr2android::tvp::rva
{
    consteval auto rva(uintptr_t arm64v8a, uintptr_t armeabiv7a) -> uintptr_t
    {
        #if defined(__aarch64__)
        return arm64v8a;
        #elif defined(__arm__)
        return armeabiv7a;
        #else
        return 0;
        #endif
    }

    struct TJSString
    {
        static inline constexpr uintptr_t            ProjectDir{ TVPRVA(0x1AF01A8, 0) };
    };

    struct GraphicType
    {
        static inline constexpr uintptr_t               Global{ TVPRVA(0x1AD84B8, 0) };
    };

    struct StorageMediaManager
    {
        static inline constexpr uintptr_t                   Global{ TVPRVA(0x1AE0008, 0) };
        static inline constexpr uintptr_t     NormalizeStorageName{ TVPRVA(0x08E93D0, 0) };
        static inline constexpr uintptr_t      SetCurrentDirectory{ TVPRVA(0x08EA130, 0) };
        static inline constexpr uintptr_t GetLocallyAccessibleName{ TVPRVA(0x08EA5E0, 0) };
    };

    static inline constexpr uintptr_t                          AddAutoPath{ TVPRVA(0x08EB894, 0) };
    static inline constexpr uintptr_t                       RemoveAutoPath{ TVPRVA(0x08EBA70, 0) };
    static inline constexpr uintptr_t                        GetPlacedPath{ TVPRVA(0x08EBC80, 0) };

    static inline constexpr uintptr_t            IsExistentStorageNoSearch{ TVPRVA(0x08EB4C0, 0) };
    static inline constexpr uintptr_t IsExistentStorageNoSearchNoNormalize{ TVPRVA(0x08EAF88, 0) };
    static inline constexpr uintptr_t                  SetCurrentDirectory{ TVPRVA(0x08EA6F8, 0) };
    static inline constexpr uintptr_t                   ClearStorageCaches{ TVPRVA(0x08FD444, 0) };

    static inline constexpr uintptr_t              CreateTextStreamForRead{ TVPRVA(0x8F6438, 0) };
    static inline constexpr uintptr_t             CreateTextStreamForWrite{ TVPRVA(0x8F6B14, 0) };
    static inline constexpr uintptr_t            CreateBinaryStreamForRead{ TVPRVA(0x8DBE98, 0) };
    static inline constexpr uintptr_t           CreateBinaryStreamForWrite{ TVPRVA(0x8DBFB4, 0) };

    static inline constexpr uintptr_t               GetDefaultReadEncoding{ TVPRVA(0x08F72C4, 0) };
    static inline constexpr uintptr_t               SetDefaultReadEncoding{ TVPRVA(0x08F6EDC, 0) };

    static inline constexpr uintptr_t                       GetCommandLine{ TVPRVA(0x090DE30, 0) };
    static inline constexpr uintptr_t                       SetCommandLine{ TVPRVA(0x090FCA0, 0) };
    static inline constexpr uintptr_t                         GetTickCount{ TVPRVA(0x0A2A4DC, 0) };

}

namespace TVP::RVA
{
    using namespace kr2android::tvp::rva;
};