#pragma once
#include <cstdint>
#include <tjs.h>

#if defined(__aarch64__)
#define tvprva(arm64v8a, armeabiv7a) arm64v8a
#elif defined(__arm__)
#define tvprva(arm64v8a, armeabiv7a) armeabiv7a
#else
#define tvprva(arm64v8a, armeabiv7a) 0
#endif
#define TVPRVA tvprva

namespace kr2android::tvp
{
    static inline constexpr uintptr_t RVA_TVP_GRAPHIC_TYPE{ TVPRVA(0x1AD84B8, 0) };

    static inline constexpr uintptr_t RVA_TVP_PROJECT_DIR { TVPRVA(0x1AF01A8, 0) };
}