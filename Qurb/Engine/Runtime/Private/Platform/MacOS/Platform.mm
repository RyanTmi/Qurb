#include "Platform/Platform.hpp"

#include "Platform/MacOS/ApplicationDelegate.hpp"

namespace qurb
{
    struct Platform::NativeHandle
    {
        ApplicationDelegate* applicationDelegate;
    };

    Platform::Platform()
        : _nativeHandle(new NativeHandle)
    {
        @autoreleasepool
        {
            // Create the NSApp
            [NSApplication sharedApplication];

            _nativeHandle->applicationDelegate = [[ApplicationDelegate alloc] init];
            [NSApp setDelegate:_nativeHandle->applicationDelegate];

            // Allow the app to appear in the doc
            [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];

            // Run the application
            [NSApp run];
            [NSApp finishLaunching];

            [NSApp activate];
        }
    }

    Platform::~Platform()
    {
        @autoreleasepool
        {
            [NSApp setDelegate:nil];
            [_nativeHandle->applicationDelegate release];
        }

        delete _nativeHandle;
    }

    auto Platform::pollEvents() -> void
    {
        @autoreleasepool
        {
            NSEvent* event;
            while (true)
            {
                event = [NSApp nextEventMatchingMask:NSEventMaskAny untilDate:[NSDate distantPast] inMode:NSDefaultRunLoopMode dequeue:YES];
                if (event == nil)
                {
                    break;
                }

                [NSApp sendEvent:event];
            }
        }
    }
}
