/// \file WindowEvents.hpp

#pragma once

#include "Events/Event.hpp"

namespace qurb
{
    class Window;

    struct WindowEvent : public Event
    {
        Window& window;

    public:
        explicit WindowEvent(Window& window)
            : window(window)
        {}
    };

    struct WindowResizeEvent final : public WindowEvent
    {
    public:
        WindowResizeEvent(Window& window)
            : WindowEvent(window)
        {}
    };
}
