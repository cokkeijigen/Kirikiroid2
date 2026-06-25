#include "AndroidUtils.h"
#include "tjsTypes.h"
#include "tjsString.h"
#include <string>

tjs_uint32 TVPGetRoughTickCount32()
{
    tjs_uint32 uptime = 0;
    struct timespec on;
    if (::clock_gettime(CLOCK_MONOTONIC, &on) == 0)
        uptime = on.tv_sec * 1000 + on.tv_nsec / 1000000;
    return uptime;
}
namespace TJS
{
    __attribute__((noinline, used))
    void TVPConsoleLog(const ttstr &l, bool important)
    {
        return;
    }

    __attribute__((noinline, used))
    void TVPConsoleLog(const tjs_char *l)
    {
        return;
    }
}