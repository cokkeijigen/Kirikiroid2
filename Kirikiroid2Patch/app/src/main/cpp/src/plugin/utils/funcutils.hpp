#pragma once

namespace func
{
    template <class ...Args, class R>
    [[nodiscard]] constexpr auto of(R(*func)(Args...)) noexcept -> R(*)(Args...)
    {
        return func;
    }

    template <class... Args, class ClassType, class R>
    [[nodiscard]] constexpr auto of(R(ClassType::* func)(Args...) const) noexcept -> R(ClassType::*)(Args...) const
    {
        return func;
    }

    template <class ...Args, class ClassType, class R>
    [[nodiscard]] constexpr auto of(R(ClassType::* func)(Args...)) noexcept -> R(ClassType::*)(Args...)
    {
        return func;
    }

    template <class ClassType, class R>
    [[nodiscard]] constexpr auto of(R(ClassType::* func)()) noexcept -> R(ClassType::*)()
    {
        return func;
    }

    template <class ClassType, class R>
    [[nodiscard]] constexpr auto of(R(ClassType::* func)() const) noexcept -> R(ClassType::*)() const
    {
        return func;
    }

    template <class R>
    [[nodiscard]] constexpr auto of(R(*func)()) noexcept -> R(*)()
    {
        return func;
    }

    template <class... Args>
    struct args
    {
        template <class R>
        [[nodiscard]] static constexpr auto ret(R(*func)(Args...)) noexcept -> R(*)(Args...)
        {
            return func;
        }

        template <class R>
        [[nodiscard]] static constexpr auto ret(R(*func)(Args...) noexcept) noexcept -> R(*)(Args...) noexcept
        {
            return func;
        }

        template <class R, class ClassType>
        [[nodiscard]] static constexpr auto ret(R(ClassType::*func)(Args...)) noexcept -> R(ClassType::*)(Args...)
        {
            return func;
        }

        template <class R, class ClassType>
        [[nodiscard]] static constexpr auto ret(R(ClassType::*func)(Args...) noexcept) noexcept -> R(ClassType::*)(Args...) noexcept
        {
            return func;
        }

        template <class R, class ClassType>
        [[nodiscard]] static constexpr auto ret(R(ClassType::*func)(Args...) const) noexcept -> R(ClassType::*)(Args...) const
        {
            return func;
        }

        template <class R, class ClassType>
        [[nodiscard]] static constexpr auto ret(R(ClassType::*func)(Args...) const noexcept) noexcept -> R(ClassType::*)(Args...) const noexcept
        {
            return func;
        }

        template <class R>
        [[nodiscard]] constexpr auto operator()(R(*func)(Args...)) const noexcept -> R(*)(Args...)
        {
            return func;
        }

        template <class R>
        [[nodiscard]] constexpr auto operator()(R(*func)(Args...) noexcept) const noexcept -> R(*)(Args...) noexcept
        {
            return func;
        }

        template <class R, class ClassType>
        [[nodiscard]] constexpr auto operator()(R(ClassType::*func)(Args...)) const noexcept -> R(ClassType::*)(Args...)
        {
            return func;
        }

        template <class R, class ClassType>
        [[nodiscard]] constexpr auto operator()(R(ClassType::*func)(Args...) noexcept) const noexcept -> R(ClassType::*)(Args...) noexcept
        {
            return func;
        }

        template <class R, class ClassType>
        [[nodiscard]] constexpr auto operator()(R(ClassType::*func)(Args...) const) const noexcept -> R(ClassType::*)(Args...) const
        {
            return func;
        }

        template <class R, class ClassType>
        [[nodiscard]] constexpr auto operator()(R(ClassType::*func)(Args...) const noexcept) const noexcept -> R(ClassType::*)(Args...) const noexcept
        {
            return func;
        }
    };

    template <class R>
    struct ret
    {
        template <class... Args>
        [[nodiscard]] static constexpr auto args(R(*func)(Args...)) noexcept -> R(*)(Args...)
        {
            return func;
        }

        template <class... Args>
        [[nodiscard]] static constexpr auto args(R(*func)(Args...) noexcept) noexcept -> R(*)(Args...) noexcept
        {
            return func;
        }

        template <class... Args, class ClassType>
        [[nodiscard]] static constexpr auto args(R(ClassType::*func)(Args...)) noexcept -> R(ClassType::*)(Args...)
        {
            return func;
        }

        template <class... Args, class ClassType>
        [[nodiscard]] static constexpr auto args(R(ClassType::*func)(Args...) noexcept) noexcept -> R(ClassType::*)(Args...) noexcept
        {
            return func;
        }

        template <class... Args, class ClassType>
        [[nodiscard]] static constexpr auto args(R(ClassType::*func)(Args...) const) noexcept -> R(ClassType::*)(Args...) const
        {
            return func;
        }

        template <class... Args, class ClassType>
        [[nodiscard]] static constexpr auto args(R(ClassType::*func)(Args...) const noexcept) noexcept -> R(ClassType::*)(Args...) const noexcept
        {
            return func;
        }
    };
}