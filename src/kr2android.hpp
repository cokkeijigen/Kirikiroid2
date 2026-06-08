#pragma once
#include <kr2base.hpp>
#include <tjsString.h>

namespace kr2android
{
    template<class T>
    concept is_pointer = std::is_pointer<T>::value || std::is_member_function_pointer_v<std::remove_reference_t<T>> ||
                         std::is_function_v<std::remove_pointer_t<std::remove_reference_t<T>>>;

    union uniptr_t
    {
        void*     ptr;
        intptr_t  intptr;
        uintptr_t uintptr;

        inline uniptr_t() noexcept : ptr{ nullptr }{}
        inline uniptr_t(is_pointer    auto _ptr) noexcept :     ptr { *reinterpret_cast<void**>(&_ptr) } {}
        inline uniptr_t(std::integral auto _val) noexcept : uintptr { static_cast<uintptr_t>(_val)     } {}
        inline auto operator+(uniptr_t other) noexcept -> uniptr_t { return other.uintptr + this->uintptr; }
    };

    extern auto get_base() noexcept -> uniptr_t;
    extern auto init(const uniptr_t libbase) noexcept -> bool;
    extern auto init() noexcept -> bool;

    namespace tvp
    {
        struct project_dir
        {
            static auto get() noexcept -> const TJS::ttstr*;
        };

        extern auto get_game_path() noexcept -> TJS::ttstr;
        extern auto get_app_path () noexcept -> TJS::ttstr;
    }
}

namespace tvp = kr2android::tvp;
namespace k2a = kr2android;