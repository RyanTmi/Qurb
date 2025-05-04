#pragma once

#include "Platform/Window.hpp"

#import <AppKit/AppKit.h>

@interface View : NSView <NSTextInputClient>
{
    qurb::Window*              baseWindow;
    NSTrackingArea*            trackingArea;
    NSMutableAttributedString* markedText;
}

- (instancetype)initWithWindow:(qurb::Window*)initWindow frame:(NSRect)initFrame;

@end
