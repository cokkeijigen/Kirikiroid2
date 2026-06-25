#pragma once

namespace func
{
    template <class ...Args, class R>
    [[nodiscard]] constexpr auto request(R(*func)(Args...)) noexcept -> R(*)(Args...)
    {
        return func;
    }

    template <class... Args, class ClassType, class R>
    [[nodiscard]] constexpr auto request(R(ClassType::* func)(Args...) const) noexcept -> R(ClassType::*)(Args...) const
    {
        return func;
    }

    template <class ...Args, class ClassType, class R>
    [[nodiscard]] constexpr auto request(R(ClassType::* func)(Args...)) noexcept -> R(ClassType::*)(Args...)
    {
        return func;
    }

    template <class ClassType, class R>
    [[nodiscard]] constexpr auto request(R(ClassType::* func)()) noexcept -> R(ClassType::*)()
    {
        return func;
    }

    template <class ClassType, class R>
    [[nodiscard]] constexpr auto request(R(ClassType::* func)() const) noexcept -> R(ClassType::*)() const
    {
        return func;
    }

    template <class R>
    [[nodiscard]] constexpr auto request(R(*func)()) noexcept -> R(*)()
    {
        return func;
    }
}