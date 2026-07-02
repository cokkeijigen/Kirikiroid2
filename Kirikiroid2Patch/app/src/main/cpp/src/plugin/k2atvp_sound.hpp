#pragma once
#include <tjs.h>
namespace TVP::Sound
{
    extern auto ConvertIntegerPCMTo16bits(tjs_int16 *output, const void *input, tjs_int bytespersample,
                tjs_int validbits, tjs_int channels, tjs_int count, bool downmix) noexcept -> bool;

    extern auto ConvertFloatPCMTo16bits(tjs_int16 *output, const float *input, tjs_int channels,
                tjs_int count, bool downmix) noexcept -> void;

    extern auto ConvertIntegerPCMToFloat(float *output, const void *input, tjs_int bytespersample,
            	tjs_int validbits, tjs_int channels, tjs_int count) noexcept -> bool;

}