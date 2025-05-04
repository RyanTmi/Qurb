#pragma once

#include "Platform/Window.hpp"

#import <AppKit/NSWindow.h>

@interface WindowDelegate : NSObject <NSWindowDelegate>
{
    qurb::Window* baseWindow;
}

- (instancetype)initWithWindow:(qurb::Window*)initWindow;

@end
