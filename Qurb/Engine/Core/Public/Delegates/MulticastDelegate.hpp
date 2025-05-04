/// \file MulticastDelegate.hpp

#pragma once

#include "Delegate.hpp"
#include "Log/Log.hpp"

#include <algorithm>
#include <unordered_set>

namespace qurb
{
    //==================================================================================================================
    // Class : MulticastDelegate
    //==================================================================================================================

    template <typename... Args>
    struct MulticastDelegate
    {
    public:
        using DelegateType = Delegate<void(Args...)>;

    public:
        constexpr MulticastDelegate() noexcept = default;

        constexpr MulticastDelegate(const MulticastDelegate& other) noexcept = default;

    public:
        constexpr auto operator=(const MulticastDelegate& other) noexcept -> MulticastDelegate& = default;

        template <typename... UArgs>
        constexpr auto operator()(UArgs&&... args) const -> void;

        auto operator+=(DelegateType delegate) noexcept -> void;
        auto operator-=(DelegateType delegate) noexcept -> void;

        auto clear() noexcept -> void;

    private:
        std::unordered_set<DelegateType> delegates_;
    };

    //==================================================================================================================
    // Class : MulticastDelegate
    //==================================================================================================================

    template <typename... Args>
    template <typename... UArgs>
    constexpr auto MulticastDelegate<Args...>::operator()(UArgs&&... args) const -> void
    {
        std::ranges::for_each(delegates_, [&](auto& delegate) { delegate(std::forward<UArgs>(args)...); });
    }

    template <typename... Args>
    auto MulticastDelegate<Args...>::operator+=(DelegateType delegate) noexcept -> void
    {
        delegates_.insert(delegate);
    }

    template <typename... Args>
    auto MulticastDelegate<Args...>::operator-=(DelegateType delegate) noexcept -> void
    {
        auto it = delegates_.find(delegate);
        if (it == delegates_.end())
        {
            Log::warn("Delegate not found, cannot remove it.");
            return;
        }

        delegates_.erase(it);
    }

    template <typename... Args>
    auto MulticastDelegate<Args...>::clear() noexcept -> void
    {
        delegates_.clear();
    }
}
