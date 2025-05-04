#include "Platform/MacOS/WindowDelegate.hpp"

#include "Platform/MacOS/NativeWindow.hpp"
#include "Platform/MacOS/View.hpp"

#import <QuartzCore/QuartzCore.h>

using namespace qurb;

@implementation WindowDelegate

- (instancetype)initWithWindow:(Window*)initWindow
{
    self = [super init];
    if (self)
    {
        baseWindow = initWindow;
    }
    return self;
}

- (BOOL)windowShouldClose:(NSWindow*)sender
{
    baseWindow->close();

    return NO;
}

- (void)windowDidResize:(NSNotification*)notification
{
    auto& nativeWindow = baseWindow->nativeHandle();

    View*         view  = nativeWindow.view;
    CAMetalLayer* layer = nativeWindow.layer;

    CGSize viewSize     = view.bounds.size;
    NSSize drawableSize = [view convertSizeToBacking:viewSize];

    layer.drawableSize  = drawableSize;
    layer.contentsScale = view.window.backingScaleFactor;

    baseWindow->sendEvent<WindowResizeEvent>(*baseWindow, drawableSize.width, drawableSize.height);
}

- (void)windowDidChangeScreen:(NSNotification*)notification
{
    auto& nativeWindow = baseWindow->nativeHandle();

    View*         view  = nativeWindow.view;
    CAMetalLayer* layer = nativeWindow.layer;

    CGSize viewSize     = view.bounds.size;
    NSSize drawableSize = [view convertSizeToBacking:viewSize];

    layer.drawableSize  = drawableSize;
    layer.contentsScale = view.window.backingScaleFactor;

    baseWindow->sendEvent<WindowResizeEvent>(*baseWindow, drawableSize.width, drawableSize.height);
}

- (void)windowDidMiniaturize:(NSNotification*)notification
{
    // Send a size of 0, which tells the application it was minimized.

    auto& nativeWindow = baseWindow->nativeHandle();

    baseWindow->sendEvent<WindowResizeEvent>(*baseWindow, 0, 0);

    [nativeWindow.window miniaturize:nil];
}

- (void)windowDidDeminiaturize:(NSNotification*)notification
{
    auto& nativeWindow = baseWindow->nativeHandle();

    View*         view  = nativeWindow.view;
    CAMetalLayer* layer = nativeWindow.layer;

    CGSize viewSize     = view.bounds.size;
    NSSize drawableSize = [view convertSizeToBacking:viewSize];

    layer.drawableSize  = drawableSize;
    layer.contentsScale = view.window.backingScaleFactor;

    baseWindow->sendEvent<WindowResizeEvent>(*baseWindow, drawableSize.width, drawableSize.height);

    [nativeWindow.window deminiaturize:nil];
}

@end
