/// \file Window.hpp

#pragma once

#include "Events/EventDispatcher.hpp"
#include "Events/WindowEvents.hpp"
#include "Math/Vector2.hpp"

#include <memory>
#include <string>
#include <tuple>

namespace qurb
{
    namespace rhi
    {
        class RenderContext;
    }

    /// \brief The `WindowDescriptor` struct.
    struct WindowDescriptor final
    {
        std::string    title;
        math::Vector2f size;
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
        [[nodiscard]] auto size() const -> math::Vector2f;
        [[nodiscard]] auto shouldClose() const -> bool;

        auto close() -> void;

        template <Dispatchable E, typename... Args>
        auto sendEvent(Args&&... args) -> void;

        template <Dispatchable E>
        auto registerEvent(EventDispatcher<E>::Listener listener) -> void;

        template <Dispatchable E>
        auto unregisterEvent(EventDispatcher<E>::Listener listener) -> void;

        auto setSize(math::Vector2f size) -> void;

        auto nativeHandle() -> NativeHandle&;
        auto renderContext() -> rhi::RenderContext*;

    private:
        friend class Renderer;

        using Dispatchers = std::tuple<EventDispatcher<WindowResizeEvent>>;

    private:
        std::unique_ptr<NativeHandle> _nativeHandle;
        rhi::RenderContext*           _renderContext;
        std::string                   _title;
        math::Vector2f                _size;
        bool                          _shouldClose;
        Dispatchers                   _dispatchers;
    };

    inline auto Window::size() const -> math::Vector2f
    {
        return _size;
    }

    inline auto Window::shouldClose() const -> bool
    {
        return _shouldClose;
    }

    inline auto Window::close() -> void
    {
        _shouldClose = true;
    }

    template <Dispatchable E, typename... Args>
    auto Window::sendEvent(Args&&... args) -> void
    {
        std::get<EventDispatcher<E>>(_dispatchers).dispatch(std::forward<Args>(args)...);
    }

    template <Dispatchable E>
    auto Window::registerEvent(typename EventDispatcher<E>::Listener listener) -> void
    {
        std::get<EventDispatcher<E>>(_dispatchers).registerListener(listener);
    }

    template <Dispatchable E>
    auto Window::unregisterEvent(typename EventDispatcher<E>::Listener listener) -> void
    {
        std::get<EventDispatcher<E>>(_dispatchers).unregisterListener(listener);
    }

    inline auto Window::setSize(math::Vector2f size) -> void
    {
        _size = size;
    }

    inline auto Window::nativeHandle() -> NativeHandle&
    {
        return *_nativeHandle;
    }

    inline auto Window::renderContext() -> rhi::RenderContext*
    {
        return _renderContext;
    }
}
