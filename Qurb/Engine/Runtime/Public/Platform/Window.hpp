/// \file Window.hpp

#pragma once

#include "Events/EventDispatcher.hpp"
#include "Events/WindowEvents.hpp"
#include "Log/Log.hpp"

#include <memory>
#include <string>
#include <tuple>

namespace qurb
{
    /// \brief The `WindowDescriptor` struct.
    struct WindowDescriptor final
    {
        std::string name;
    };

    /// \brief The `Window` class.
    class Window final
    {
    public:
        struct NativeHandle;

    public:
        explicit Window(const WindowDescriptor& descriptor);
        ~Window();

        Window(const Window&)                    = delete;
        auto operator=(const Window&) -> Window& = delete;

        Window(Window&& other) noexcept;
        auto operator=(Window&& other) noexcept -> Window&;

    public:
        [[nodiscard]] auto shouldClose() const -> bool;

        auto close() -> void;

        auto nativeHandle() -> NativeHandle&;

        template <Dispatchable E, typename... Args>
        auto sendEvent(Args&&... args) -> void
        {
            std::get<EventDispatcher<E>>(_dispatchers).dispatch(std::forward<Args>(args)...);
        }

        template <Dispatchable E>
        auto listenEvent(EventDispatcher<E>::Listener listener) -> void
        {
            std::get<EventDispatcher<E>>(_dispatchers).registerListener(listener);
        }

    private:
        using Dispatchers = std::tuple<EventDispatcher<WindowResizeEvent>>;

    private:
        std::unique_ptr<NativeHandle> _nativeHandle;
        Dispatchers                   _dispatchers;
        bool                          _shouldClose;
    };

    inline auto Window::shouldClose() const -> bool
    {
        return _shouldClose;
    }

    inline auto Window::close() -> void
    {
        _shouldClose = true;
    }

    inline auto Window::nativeHandle() -> NativeHandle&
    {
        return *_nativeHandle;
    }
}
