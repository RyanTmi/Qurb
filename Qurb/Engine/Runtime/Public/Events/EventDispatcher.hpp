/// \file EventDispatcher.hpp

#pragma once

#include "Containers/Vector.hpp"
#include "Delegates/Delegate.hpp"
#include "Events/Event.hpp"

#include <algorithm>
#include <type_traits>

namespace qurb
{
    template <typename T>
    concept Dispatchable = std::is_base_of_v<Event, T>;

    /// \brief The `EventDispatcher` class.
    /// \tparam E The type of event to dispatch.
    template <Dispatchable E>
    class EventDispatcher
    {
    public:
        using Listener = Delegate<bool(E&)>;

    public:
        EventDispatcher() = default;

    public:
        auto registerListener(Listener listener) -> void;
        auto unregisterListener(Listener listener) -> void;
        auto unregisterAllListeners() -> void;

        template <typename... Args>
        auto dispatch(Args&&... args) -> void;

        auto dispatch(E& event) -> void;

    private:
        Vector<Listener> _listeners;
    };

    template <Dispatchable E>
    auto EventDispatcher<E>::registerListener(Listener listener) -> void
    {
        _listeners.pushBack(listener);
    }

    template <Dispatchable E>
    auto EventDispatcher<E>::unregisterListener(Listener listener) -> void
    {
        auto res = std::ranges::remove_if(_listeners, [&listener](const Listener& l) { return l == listener; });
        _listeners.erase(res.begin(), res.end());
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
