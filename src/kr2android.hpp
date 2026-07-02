#pragma once
#include <optional>
#include <tjs.h>
#include <k2atvp.hpp>

namespace kr2android
{
    template<class T>
    concept is_pointer = std::is_pointer<T>::value || std::is_member_function_pointer_v<std::remove_reference_t<T>> ||
                         std::is_function_v<std::remove_pointer_t<std::remove_reference_t<T>>>;

    template<is_pointer T = void*>
    union unirawptr_t
    {
        T raw;
        void* ptr;

        inline constexpr unirawptr_t() noexcept : ptr{ nullptr } {}
        inline constexpr unirawptr_t(std::nullptr_t) noexcept : ptr{ nullptr }{}
        inline constexpr unirawptr_t(void* _ptr) noexcept : ptr{ _ptr } {}
        inline constexpr unirawptr_t(T     _raw) noexcept requires (!std::is_same_v<T, void*>) : raw{ _raw }{ }
        inline constexpr unirawptr_t(std::integral auto _ptr) noexcept
        {
            this->ptr = reinterpret_cast<void*>(static_cast<uintptr_t>(_ptr));
        }
    };

    union uniptr_t
    {
        void*     ptr;
        intptr_t  intptr;
        uintptr_t uintptr;

        inline constexpr uniptr_t() noexcept : ptr{ nullptr }{}
        inline constexpr uniptr_t(std::nullptr_t) noexcept : ptr{ nullptr }{}
        inline constexpr uniptr_t(std::integral auto _val) noexcept : ptr { unirawptr_t{ _val }.ptr } {}
        inline constexpr uniptr_t(is_pointer    auto _ptr) noexcept : ptr { unirawptr_t{ _ptr }.ptr } {}
        inline auto operator+(uniptr_t other) noexcept -> uniptr_t { return other.uintptr + this->uintptr; }
    };

    namespace symbol_hash
    {
        static inline consteval auto operator""_hash(const char* str, size_t size) noexcept -> uint64_t
        {
            constexpr uint64_t fnv1a_prime { 0x00000100000001B3 };
            constexpr uint64_t fnv1a_offset{ 0xCBF29CE484222325 };
            uint64_t hash{ fnv1a_offset };
            for (size_t i{}; i < size; i++)
            {
                if(str[i] ==  ' ') continue;
                if(str[i] == '\n') continue;
                if(str[i] == '\r') continue;
                hash ^= static_cast<uint64_t>(str[i]);
                hash *= fnv1a_prime;
            }
            return hash;
        }
    }

    namespace symbol
    {
        template<size_t size>
        static inline consteval auto hash(const char(&str)[size]) noexcept -> uint64_t
        {
            return symbol_hash::operator""_hash(str, size - 1);
        }
    }

    class k2aplugin
    {
        void*    m_base{};
        void*(*m_query)(uint64_t hash){};

    public:

        inline k2aplugin() noexcept{};
        inline k2aplugin(void* base, void*(*query)(uint64_t)) noexcept: m_base{ base }, m_query{ query }{}
        inline k2aplugin(const k2aplugin& k2a) noexcept: k2aplugin{ &k2a }{};
        inline k2aplugin(const k2aplugin* k2a) noexcept
        {
            if(k2a != nullptr)
            {
                this->m_base  = k2a->m_base;
                this->m_query = k2a->m_query;
            }
        }

        inline auto is_vaild() const noexcept -> bool
        {
            return bool
            {
                static_cast<const void*>(this) != nullptr &&
                this->m_base != nullptr && this->m_query != nullptr
            };
        }

        template<is_pointer T = void*>
        inline auto query(uint64_t hash) noexcept -> T
        {
            unirawptr_t<T> result{};
            if(static_cast<void*>(this) != nullptr && this->m_query != nullptr)
            {
                result.ptr = this->m_query(hash);
            }
            return result.raw;
        }

        inline auto base() noexcept -> uniptr_t
        {
            if(static_cast<void*>(this) != nullptr)
            {
                return this->m_base;
            }
            return nullptr;
        }
    };

    extern k2aplugin plugin;
    inline auto plugin_init(const k2aplugin* k2a) noexcept -> bool
    {
        if(k2a->is_vaild())
        {
            plugin = k2a;
            return true;
        }
        return false;
    }

    inline auto plugin_init(const k2aplugin& k2a) noexcept -> bool
    {
        if(k2a.is_vaild())
        {
            plugin = k2a;
            return true;
        }
        return false;
    }

    template<is_pointer T = void*>
    inline auto cast_ptr(const uintptr_t rva) noexcept -> T
    {
        unirawptr_t<T> result{};
        if(rva != 0)
        {
            const uniptr_t base{ plugin.base() };
            if(base.ptr != nullptr)
            {
                result = base.uintptr + rva;
            }
        }
        return result.raw;
    }

    template<is_pointer T = void*>
    inline auto cast_ptr(T& val, const uintptr_t rva) noexcept -> void
    {
        val = cast_ptr<T>(rva);
    }
}
namespace tvp = kr2android::tvp;
namespace k2a = kr2android;