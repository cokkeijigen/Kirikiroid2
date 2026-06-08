#pragma once
#include <cstdint>
#include <tjs.h>

#define TVPRVA kr2android::tvp::rva
#define tvprva kr2android::tvp::rva

namespace kr2android::tvp
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

    static inline constexpr uintptr_t RVA_TVP_GRAPHIC_TYPE{ TVPRVA(0x1AD84B8, 0) };

    static inline constexpr uintptr_t RVA_TVP_PROJECT_DIR { TVPRVA(0x1AF01A8, 0) };
}