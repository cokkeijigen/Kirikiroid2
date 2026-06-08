#include <kr2android.hpp>
#include <link.h>
#include <string.h>

namespace kr2android
{
    static uniptr_t modbase{};

    auto init() noexcept -> bool
    {
        if(kr2android::modbase.ptr != nullptr)
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

        kr2android::modbase.uintptr = ctx.addr;
        return true;
    }

    auto init(const uniptr_t libbase) noexcept -> bool
    {
        if(kr2android::modbase.ptr != nullptr)
        {
            return false;
        }

        if(libbase.ptr != nullptr)
        {
            kr2android::modbase.ptr = libbase.ptr;
            return true;
        }
    }

    auto get_base() noexcept -> uniptr_t
    {
        return kr2android::modbase;
    }

    auto tvp::project_dir::get() noexcept -> const TJS::ttstr*
    {
        static TJS::ttstr* _ptr{};
        if(_ptr == nullptr && kr2android::modbase.ptr != nullptr)
        {
            const auto ptr{ kr2android::modbase.uintptr + tvp::RVA_TVP_PROJECT_DIR };
            _ptr = reinterpret_cast<TJS::ttstr*>(ptr);
        }
        return _ptr;
    }

    auto tvp::extract_storage_path(const TJS::ttstr& name) noexcept -> TJS::ttstr
    {
        const tjs_char * s = name.c_str();
        tjs_int slen = name.GetLen();
        const tjs_char * p = s + slen;
        p--;
        while(p >= s)
        {
            if(*p == TJS_W('\\')) break;
            if(*p == TJS_W('/') ) break;
            if(*p == TJS_W('>') ) break;
            p--;
        }
        p++;
        return TJS::ttstr{ s,  static_cast<int>(p-s) };
    }

    auto tvp::get_app_path() noexcept -> TJS::ttstr
    {
        const TJS::ttstr* dir { project_dir::get() };
        if(dir != nullptr)
        {
            return extract_storage_path(*dir);
        }
        return TJS::ttstr{};
    }

    auto tvp::get_game_path() noexcept -> TJS::ttstr
    {
        const TJS::ttstr* dir { project_dir::get() };
        if(dir != nullptr && !dir->IsEmpty())
        {
            std::u16string_view str{ dir->c_str(), static_cast<size_t>(dir->length()) };
            auto offset{ str.find_last_of(u"\\/>") };
            if(offset != std::u16string_view::npos)
            {
                str = str.substr(0, offset);
            }
            offset = str.find_last_of(u"/\\");
            if(offset != std::u16string_view::npos)
            {
                return TJS::ttstr{ *dir,  static_cast<int>(offset) };
            }
            return TJS::ttstr{ *dir, static_cast<int>(str.size()) };
        }
        return TJS::ttstr{};
    }
}