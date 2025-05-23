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

    baseWindow->setSize(math::Vector2f(drawableSize.width, drawableSize.height));
    baseWindow->sendEvent<WindowResizeEvent>(*baseWindow);
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

    baseWindow->setSize(math::Vector2f(drawableSize.width, drawableSize.height));
    baseWindow->sendEvent<WindowResizeEvent>(*baseWindow);
}

- (void)windowDidMiniaturize:(NSNotification*)notification
{
    // Send a size of 0, which tells the application it was minimized.

    auto& nativeWindow = baseWindow->nativeHandle();

    baseWindow->setSize({0, 0});
    baseWindow->sendEvent<WindowResizeEvent>(*baseWindow);

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

    baseWindow->setSize(math::Vector2f(drawableSize.width, drawableSize.height));
    baseWindow->sendEvent<WindowResizeEvent>(*baseWindow);

    [nativeWindow.window deminiaturize:nil];
}

@end
