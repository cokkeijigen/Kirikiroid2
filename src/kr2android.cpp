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
            _ptr = k2a::cast_ptr<TJS::ttstr*>(tvp::RVA_TVP_PROJECT_DIR);
        }
        return _ptr;
    }

    auto tvp::get_app_path() noexcept -> TJS::ttstr
    {

        const TJS::ttstr* dir { project_dir::get() };
        if(dir != nullptr && !dir->IsEmpty())
        {
            size_t begin{}, length{};
            std::u16string_view str{ dir->c_str(), static_cast<size_t>(dir->length()) };

            if(str.starts_with(u"file://."))
            {
                str = str.substr(8);
                begin += 8;
            }

            size_t offset{ str.find_last_of(u"\\/>") };
            if(offset != std::u16string_view::npos)
            {
                str = str.substr(0, offset);
            }

            length = str.end() - str.begin();
            return dir->SubString(begin,static_cast<int>(length) );
        }
        return TJS::ttstr{};
    }

    auto tvp::get_game_path() noexcept -> TJS::ttstr
    {

        const TJS::ttstr* dir { project_dir::get() };
        if(dir != nullptr && !dir->IsEmpty())
        {
            size_t begin{}, length{};
            std::u16string_view str{ dir->c_str(), static_cast<size_t>(dir->length()) };

            if(str.starts_with(u"file://."))
            {
                str = str.substr(8);
                begin += 8;
            }

            size_t offset{ str.find_last_of(u"\\/>") };
            if(offset != std::u16string_view::npos)
            {
                str = str.substr(0, offset);
            }

            offset = str.find_last_of(u"/\\");
            if(offset != std::u16string_view::npos)
            {
                str = str.substr(0, offset);
            }

            length = str.end() - str.begin();
            return dir->SubString(begin, static_cast<int>(length) );
        }
        return TJS::ttstr{};
    }
}