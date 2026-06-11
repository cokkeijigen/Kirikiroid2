#pragma once
#include <optional>
#include <kr2rva.hpp>
#include <kr2type.hpp>
#define _kr2android

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

    template<is_pointer T = void*>
    union unirawptr_t
    {
        T raw;
        void* ptr;

        inline unirawptr_t() noexcept : ptr{ nullptr } {}
        inline unirawptr_t(void* _ptr) noexcept : ptr{ _ptr } {}
        inline unirawptr_t(T _raw) noexcept requires (!std::is_same_v<T, void*>) : raw{ _raw }{ }
        inline unirawptr_t(std::integral auto _ptr) noexcept
        {
            this->ptr = reinterpret_cast<void*>(static_cast<uintptr_t>(_ptr));
        }
    };

    struct kr2android
    {
        void* base;
        virtual auto query(const char* name) noexcept -> void* = 0;

        template<is_pointer T>
        inline auto query_cast(const char* name) noexcept -> T
        {
            unirawptr_t<T> result{ .ptr = this->query(name) };
            return result.raw;
        }
    };

    extern auto get_base() noexcept -> uniptr_t;
    extern auto init(const uniptr_t libbase) noexcept -> bool;
    extern auto init() noexcept -> bool;

    template<is_pointer T>
    inline auto cast_ptr(const uintptr_t rva) noexcept -> T
    {
        unirawptr_t<T> result{};
        const uniptr_t base{ get_base() };
        if(base.ptr != nullptr)
        {
            result = base.uintptr + rva;
        }
        return result.raw;
    }
}

namespace tvp = kr2android::tvp;
namespace k2a = kr2android;