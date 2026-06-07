#pragma once
#include <kr2base.hpp>
#include <tjsString.h>


namespace kr2android
{
    union ptr_t
    {
        void*     ptr;
        intptr_t  intptr;
        uintptr_t uintptr;
    };

    extern auto get_base() noexcept -> ptr_t;
    extern auto init(const ptr_t libbase = {}) noexcept -> bool;

    namespace tvp
    {
        class project_dir
        {
            static inline TJS::ttstr* _ptr{};
        public:
            static auto get() noexcept -> const TJS::ttstr*;
        };

        extern auto extract_storage_path(const TJS::ttstr& name) noexcept -> TJS::ttstr;
        extern auto get_game_path() noexcept -> TJS::ttstr;
        extern auto get_app_path () noexcept -> TJS::ttstr;
    }
}

namespace tvp = kr2android::tvp;