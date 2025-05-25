#include "Platform/Window.hpp"

#include "Debug/Ensure.hpp"
#include "Log/Log.hpp"
#include "Platform/MacOS/NativeWindow.hpp"
#include "Platform/MacOS/View.hpp"
#include "Platform/MacOS/WindowDelegate.hpp"
#include "RHI/RenderContext.hpp"

#import <AppKit/AppKit.h>
#import <QuartzCore/QuartzCore.h>

namespace qurb
{
    Window::Window(const WindowDescriptor& descriptor)
        : _nativeHandle(std::make_unique<NativeHandle>())
        , _renderContext(nullptr)
        , _title(descriptor.title)
        , _size(descriptor.size)
        , _shouldClose(false)
    {
        @autoreleasepool
        {
            NSRect contentRect = NSMakeRect(0, 0, _size.x, _size.y);
            // TODO: Handle window style using the descriptor
            NSUInteger styleMask = NSWindowStyleMaskMiniaturizable | NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskResizable;

            auto* window = [[NSWindow alloc] initWithContentRect:contentRect styleMask:styleMask backing:NSBackingStoreBuffered defer:NO];
            ensure(window != nil, "Can not allocate NSWindow");

            auto* delegate = [[WindowDelegate alloc] initWithWindow:this];
            ensure(delegate != nil, "Can not allocate WindowDelegate");

            auto* view = [[View alloc] initWithWindow:this frame:contentRect];
            ensure(view != nil, "Can not allocate View");

            auto* layer = [CAMetalLayer layer];
            ensure(layer != nil, "Can not allocate CAMetalLayer");

            [window setDelegate:delegate];
            [window setContentView:view];
            [window setAcceptsMouseMovedEvents:YES];
            [window setTitle:@(_title.data())];
            [window setMinSize:NSMakeSize(540, 360)];
            [window setLevel:NSNormalWindowLevel];
            [window center];
            [window makeFirstResponder:view];
            // Show the window
            [window makeKeyAndOrderFront:nil];

            [view setWantsLayer:YES];
            [view setLayer:layer];

            [layer setBounds:view.bounds];
            [layer setDrawableSize:[view convertSizeToBacking:view.bounds.size]];
            [layer setContentsScale:window.backingScaleFactor];
            [layer setOpaque:YES];

            _nativeHandle->window   = window;
            _nativeHandle->delegate = delegate;
            _nativeHandle->view     = view;
            _nativeHandle->layer    = layer;
        }

        Log::trace("Window created");
    }

    Window::~Window()
    {
        if (_nativeHandle)
        {
            [_nativeHandle->window orderOut:nil];
            [_nativeHandle->window setDelegate:nil];
            [_nativeHandle->window close];

            [_nativeHandle->layer release];
            [_nativeHandle->view release];
            [_nativeHandle->delegate release];
            [_nativeHandle->window release];
        }

        if (_renderContext)
        {
            _renderContext->release();
        }

        Log::trace("Window destroyed");
    }

    Window::Window(Window&&) noexcept                          = default;
    auto Window::operator=(Window&& other) noexcept -> Window& = default;
}
