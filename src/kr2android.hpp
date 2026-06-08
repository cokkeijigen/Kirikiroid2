#pragma once
#include <kr2base.hpp>
#include <tjsString.h>

namespace kr2android
{
    union uniptr_t
    {
        void*     ptr;
        intptr_t  intptr;
        uintptr_t uintptr;

        inline uniptr_t() noexcept : ptr{ nullptr }{}
        inline uniptr_t(void* _ptr) noexcept : ptr{ _ptr } {}
        inline uniptr_t(intptr_t   _intptr) noexcept :  intptr{ _intptr  } {}
        inline uniptr_t(uintptr_t _uintptr) noexcept : uintptr{ _uintptr } {}
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

        extern auto extract_storage_path(const TJS::ttstr& name) noexcept -> TJS::ttstr;
        extern auto get_game_path() noexcept -> TJS::ttstr;
        extern auto get_app_path () noexcept -> TJS::ttstr;
    }
}

namespace tvp = kr2android::tvp;