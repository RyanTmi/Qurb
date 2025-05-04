/// \file EventDispatcher.hpp

#pragma once

#include "Delegates/Delegate.hpp"
#include "Events/Event.hpp"

#include <type_traits>
#include <vector>

namespace qurb
{
    template <typename T>
    concept Dispatchable = std::is_base_of_v<Event, T>;

    template <Dispatchable E>
    class EventDispatcher
    {
    public:
        using Listener = Delegate<bool(E&)>;

    public:
        EventDispatcher() = default;

    public:
        auto registerListener(Listener listener) -> void;
        auto unregisterAllListeners() -> void;

        template <typename... Args>
        auto dispatch(Args&&... args) -> void;

        auto dispatch(E& event) -> void;

    private:
        std::vector<Listener> _listeners;
    };

    template <Dispatchable E>
    auto EventDispatcher<E>::registerListener(Listener listener) -> void
    {
        _listeners.push_back(listener);
    }

    template <Dispatchable E>
    auto EventDispatcher<E>::unregisterAllListeners() -> void
    {
        _listeners.clear();
    }

    template <Dispatchable E>
    template <typename... Args>
    auto EventDispatcher<E>::dispatch(Args&&... args) -> void
    {
        auto event = E(std::forward<Args>(args)...);
        dispatch(event);
    }

    template <Dispatchable E>
    auto EventDispatcher<E>::dispatch(E& event) -> void
    {
        for (auto listener : _listeners)
        {
            if (listener(event))
            {
                return;
            }
        }
    }
}
