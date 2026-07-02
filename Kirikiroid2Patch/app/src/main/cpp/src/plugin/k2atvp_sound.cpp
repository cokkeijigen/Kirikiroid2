#include <k2atvp_sound.hpp>

namespace TVP::Sound
{
    #define GET_24BIT(p) (p[0] + (p[1] << 8) + (p[2] << 16))

    auto ConvertIntegerPCMTo16bits(tjs_int16 *output, const void *input, tjs_int bytespersample,
         tjs_int validbits, tjs_int channels, tjs_int count, bool downmix)  noexcept -> bool
    {
        // convert integer PCMs to 16bit integer PCM
        #define PROCESS_BY_CHANNELS \
            switch(channels) \
            { \
            case 2: PROCESS(2); break; \
            case 4: PROCESS(4); break; \
            case 8: PROCESS(8); break; \
            default: PROCESS(channels); break; \
            }

        if(bytespersample == 1)
        {
            // here assumes that the input 8bit PCM has always 8bit valid data
            const tjs_int8 *p = (tjs_int8 *)input;
            if(!downmix || channels == 1)
            {
                tjs_int total = channels * count;
                while(total--)
                    *(output++) = (tjs_int16)( ((tjs_int)*(p++)-0x80) * 0x100);
            }
            else
            {
                #define PROCESS(channels) \
                    while(count--) \
                    { \
                        tjs_int v = 0; \
                        tjs_int n = channels; \
                        while(n--) \
                            v += (tjs_int16)( ((tjs_int)*(p++)-0x80) * 0x100); \
                        v = v / channels; \
                        *(output++) = (tjs_int16)v; \
                    }
                PROCESS_BY_CHANNELS
                #undef PROCESS
            }
            return true;
        }

        if(bytespersample == 2)
        {
            tjs_uint16 mask =  ~( (1 << (16 - validbits)) - 1);
            const tjs_int16 *p = (const tjs_int16 *)input;
            if(!downmix || channels == 1)
            {
                tjs_int total = channels * count;
                while(total--) *(output++) = (tjs_int16)(*(p++) & mask);
            }
            else
            {
                #define PROCESS(channels) \
                    while(count--) \
                    { \
                        tjs_int v = 0; \
                        tjs_int n = channels; \
                        while(n--) \
                            v += (tjs_int16)(*(p++) & mask); \
                        v = v / channels; \
                        *(output++) = (tjs_int16)v; \
                    }
                PROCESS_BY_CHANNELS
                #undef PROCESS
            }
            return true;
        }

        if(bytespersample == 3)
        {
            tjs_uint32 mask = ~( (1 << (24 - validbits)) - 1);
            const tjs_uint8 *p = (const tjs_uint8 *)input;

            if(!downmix || channels == 1)
            {
                tjs_int total = channels * count;
                while(total--)
                {
                    tjs_int32 t = GET_24BIT(p);
                    p += 3;
                    t |= -(t&0x800000); // extend sign
                    t &= mask; // apply mask
                    t >>= 8;
                    *(output++) = (tjs_int16)t;
                }
            }
            else
            {
                #define PROCESS(channels) \
                    while(count--) \
                    { \
                        tjs_int v = 0; \
                        tjs_int n = channels; \
                        while(n--) \
                        { \
                            tjs_int32 t = GET_24BIT(p); \
                            p += 3; \
                            t |= -(t&0x800000); \
                            t &= mask; \
                            t >>= 8; \
                            v += t; \
                        } \
                        v = v / channels; \
                        *(output++) = (tjs_int16)v; \
                    }
                PROCESS_BY_CHANNELS
                #undef PROCESS
            }
            return true;
        }

        if(bytespersample == 4)
        {
            tjs_int32 mask = ~( (1 << (32 - validbits)) - 1);
            const tjs_int32 *p = (const tjs_int32 *)input;
            if(!downmix || channels == 1)
            {
                tjs_int total = channels * count;
                while(total--)
                    *(output++) = (tjs_int16)((*(p++) & mask) >> 16);
            }
            else
            {
                #define PROCESS(channels) \
                    while(count--) \
                    { \
                        tjs_int v = 0; \
                        tjs_int n = channels; \
                        while(n--) \
                            v += (tjs_int16)((*(p++) & mask) >> 16); \
                        v = v / channels; \
                        *(output++) = (tjs_int16)v; \
                    }
                PROCESS_BY_CHANNELS
                #undef PROCESS
            }
            return true;
        }
        #undef PROCESS_BY_CHANNELS
        return false;
    }

    auto ConvertFloatPCMTo16bits(tjs_int16 *output, const float *input, tjs_int channels,
         tjs_int count, bool downmix) noexcept -> void
    {
        // convert 32bit float to 16bit integer

        // float PCM is in range of +1.0 ... 0 ... -1.0
        // clip sample which is out of the range.

        if(!downmix)
        {
            tjs_int total   = channels * count;
            tjs_uint16 * d  = reinterpret_cast<tjs_uint16*>(output);
            const float * s = static_cast<const float*>(input);
            const float * s_lim = s + total;

            while(s < s_lim)
            {
                float v = *s * 32767.0f;
                *d =
                     v > (float) 32767 ?  32767 :
                     v < (float)-32768 ? -32768 :
                        v < 0 ? (tjs_int16)(v - 0.5) : (tjs_int16)(v + 0.5);
                d += 1; s += 1;
            }
        }
        else
        {
            float nc = 32768.0f / (float)channels;
            while(count--)
            {
                tjs_int n = channels;
                float t = 0;
                while(n--) t += *(input++) * nc;
                if(t > 0)
                {
                    int i = (int)(t + 0.5);
                    if(i > 32767) i = 32767;
                    *(output++) = (tjs_int16)i;
                }
                else
                {
                    int i = (int)(t - 0.5);
                    if(i < -32768) i = -32768;
                    *(output++) = (tjs_int16)i;
                }
            }
        }
    }

    auto ConvertIntegerPCMToFloat(float *output, const void *input, tjs_int bytespersample,
         tjs_int validbits, tjs_int channels, tjs_int count) noexcept -> bool
    {

        if(bytespersample == 1)
        {
            // here assumes that the input 8bit PCM has always 8bit valid data
            const tjs_int8 *p = (tjs_int8 *)input;
            tjs_int total = channels * count;
            while(total--)
                *(output++) = (float)( ((tjs_int)*(p++)- 0x80) * (1.0 / 128) );
            return true;
        }

        if(bytespersample == 2)
        {
            const tjs_int16 *p = (const tjs_int16 *)input;
            tjs_int total = channels * count;

            if(validbits == 16)
            {
                float * d = static_cast<float*>(output);
                const tjs_int16 * s = static_cast<const tjs_int16*>(p);
                const tjs_int16 * s_lim = s + total;

                while(s < s_lim)
                {
                    *d = *s * (1.0f/32768.0f);
                    d += 1; s += 1;
                }
            }
            else
            {
                // generic
                tjs_uint16 mask =  ~( (1 << (16 - validbits)) - 1);

                while(total--) *(output++) = (float)((*(p++) & mask) * (1.0 / 32768));
            }
            return true;
        }

        if(bytespersample == 3)
        {
            tjs_uint32 mask = ~( (1 << (24 - validbits)) - 1);
            const tjs_uint8 *p = (const tjs_uint8 *)input;

            tjs_int total = channels * count;
            while(total--)
            {
                tjs_int32 t = GET_24BIT(p);
                p += 3;
                t |= -(t&0x800000); // extend sign
                t &= mask; // apply mask
                *(output++) = (float)(t * (1.0 / (1<<23)));
            }
            return true;
        }

        if(bytespersample == 4)
        {
            tjs_int32 mask = ~( (1 << (32 - validbits)) - 1);
            const tjs_int32 *p = (const tjs_int32 *)input;
            tjs_int total = channels * count;
            while(total--)
                *(output++) = (float)(((*(p++) & mask) >> 0) * (1.0 / (1<<31)));
            return true;
        }

        return false;
    }
}