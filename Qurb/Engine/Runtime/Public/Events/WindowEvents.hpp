/// \file WindowEvents.hpp

#pragma once

#include "CoreTypes.hpp"
#include "Events/Event.hpp"

namespace qurb
{
    class Window;

    struct WindowEvent : public Event
    {
        Window& window;

        explicit WindowEvent(Window& window)
            : window(window)
        {}
    };

    struct WindowResizeEvent final : public WindowEvent
    {
        uint16 width;
        uint16 height;

        WindowResizeEvent(Window& window, uint16 width, uint16 height)
            : WindowEvent(window)
            , width(width)
            , height(height)
        {}
    };
}
