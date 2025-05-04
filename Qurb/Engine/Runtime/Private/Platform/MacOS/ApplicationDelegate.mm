#include "Platform/MacOS/ApplicationDelegate.hpp"

@implementation ApplicationDelegate

- (NSApplicationTerminateReply)applicationShouldTerminate:(NSApplication*)sender
{
    return NSTerminateCancel;
}

- (void)applicationWillFinishLaunching:(NSNotification*)notification
{}

- (void)applicationDidFinishLaunching:(NSNotification*)notification
{
    // Posting an empty event at start
    @autoreleasepool
    {
        NSEvent* event = [NSEvent otherEventWithType:NSEventTypeApplicationDefined
                                            location:NSMakePoint(0, 0)
                                       modifierFlags:0
                                           timestamp:0
                                        windowNumber:0
                                             context:nil
                                             subtype:0
                                               data1:0
                                               data2:0];
        [NSApp postEvent:event atStart:YES];
    }

    [NSApp stop:nil];
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication*)sender
{
    return YES;
}

@end
