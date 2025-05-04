#pragma once

#include "Platform/Detection.hpp"
#include "Platform/Window.hpp"

#ifdef QURB_PLATFORM_MACOS

@class NSWindow;
@class WindowDelegate;
@class View;
@class CAMetalLayer;

namespace qurb
{
    struct Window::NativeHandle
    {
        NSWindow*       window;
        WindowDelegate* delegate;
        View*           view;
        CAMetalLayer*   layer;
    };
}

#else
    #error "Trying to include a MacOS specific header"
#endif
