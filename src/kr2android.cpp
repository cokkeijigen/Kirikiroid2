#include <kr2android.hpp>
#include <link.h>
#include <string.h>

namespace kr2android
{
    static uniptr_t modbase{};

    auto get_base() noexcept -> uniptr_t
    {
        return modbase;
    }

    auto init(const uniptr_t libbase) noexcept -> bool
    {
        if(modbase.ptr != nullptr)
        {
            return false;
        }

        if(libbase.ptr != nullptr)
        {
            modbase = libbase;
            return true;
        }
    }

    auto init() noexcept -> bool
    {
        if(modbase.ptr != nullptr)
        {
            return false;
        }

        struct context
        {
            const char* name; uintptr_t addr;
            static auto call(dl_phdr_info* info, size_t, void* data) -> int
            {
                const auto ctx { reinterpret_cast<context*>(data) };
                if (info->dlpi_name != nullptr && strstr(info->dlpi_name, ctx->name) != nullptr)
                {
                    ctx->addr = info->dlpi_addr;
                    return 1;
                }
                return 0;
            }
        };

        context ctx{ "libgame.so", 0 };
        ::dl_iterate_phdr(context::call, &ctx);

        if (ctx.addr == 0)
        {
            return false;
        }

        modbase.uintptr = ctx.addr;
        return true;
    }


}