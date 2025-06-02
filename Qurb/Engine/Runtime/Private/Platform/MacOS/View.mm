#include "Platform/MacOS/View.hpp"

#include "Input/Input.hpp"
#include "Platform/MacOS/NativeWindow.hpp"

using namespace qurb;

static auto translateKey(uint16 key) -> KeyCode;

@implementation View

- (instancetype)initWithWindow:(Window*)initWindow frame:(NSRect)initFrame
{
    self = [super initWithFrame:initFrame];
    if (self != nil)
    {
        baseWindow   = initWindow;
        trackingArea = nil;
        markedText   = [[NSMutableAttributedString alloc] init];

        [self updateTrackingAreas];
        [self registerForDraggedTypes:@[NSPasteboardTypeURL]];
    }

    return self;
}

- (void)dealloc
{
    [trackingArea release];
    [markedText release];
    [super dealloc];
}

- (BOOL)isOpaque
{
    return [baseWindow->nativeHandle().window isOpaque];
}

- (BOOL)canBecomeKeyView
{
    return YES;
}

- (BOOL)acceptsFirstResponder
{
    return YES;
}

- (BOOL)wantsUpdateLayer
{
    return YES;
}

- (void)updateLayer
{}

- (void)cursorUpdate:(NSEvent*)event
{}

- (BOOL)acceptsFirstMouse:(NSEvent*)event
{
    return YES;
}

- (void)mouseDown:(NSEvent*)event
{
    Input::setMouseButtonPress(MouseButton::Left, true);
}

- (void)mouseDragged:(NSEvent*)event
{
    [self mouseMoved:event];
}

- (void)mouseUp:(NSEvent*)event
{
    Input::setMouseButtonPress(MouseButton::Left, false);
}

- (void)mouseMoved:(NSEvent*)event
{
    NSPoint position = [event locationInWindow];
    Input::setMousePosition(math::Vector2f(position.x, position.y));
}

- (void)rightMouseDown:(NSEvent*)event
{
    Input::setMouseButtonPress(MouseButton::Right, true);
}

- (void)rightMouseDragged:(NSEvent*)event
{
    [self mouseMoved:event];
}

- (void)rightMouseUp:(NSEvent*)event
{
    Input::setMouseButtonPress(MouseButton::Right, false);
}

- (void)otherMouseDown:(NSEvent*)event
{
    auto button = static_cast<MouseButton>([event buttonNumber]);
    Input::setMouseButtonPress(button, true);
}

- (void)otherMouseDragged:(NSEvent*)event
{
    [self mouseMoved:event];
}

- (void)otherMouseUp:(NSEvent*)event
{
    auto button = static_cast<MouseButton>([event buttonNumber]);
    Input::setMouseButtonPress(button, false);
}

- (void)mouseExited:(NSEvent*)event
{}

- (void)mouseEntered:(NSEvent*)event
{}

- (void)viewDidChangeBackingProperties
{}

- (void)updateTrackingAreas
{
    if (trackingArea)
    {
        [self removeTrackingArea:trackingArea];
        [trackingArea release];
    }

    const NSTrackingAreaOptions options = NSTrackingMouseEnteredAndExited | NSTrackingActiveInKeyWindow | NSTrackingEnabledDuringMouseDrag |
                                          NSTrackingCursorUpdate | NSTrackingInVisibleRect | NSTrackingAssumeInside;
    trackingArea = [[NSTrackingArea alloc] initWithRect:self.bounds options:options owner:self userInfo:nil];

    [self addTrackingArea:trackingArea];
    [super updateTrackingAreas];
}

- (void)keyDown:(NSEvent*)event
{
    const KeyCode key = translateKey([event keyCode]);
    Input::setKeyPress(key, true);
}

- (void)flagsChanged:(NSEvent*)event
{}

- (void)keyUp:(NSEvent*)event
{
    const KeyCode key = translateKey([event keyCode]);
    Input::setKeyPress(key, false);
}

- (void)scrollWheel:(NSEvent*)event
{}

- (NSDragOperation)draggingEntered:(id<NSDraggingInfo>)sender
{
    return NSDragOperationGeneric;
}

- (BOOL)performDragOperation:(id<NSDraggingInfo>)sender
{
    return YES;
}

- (BOOL)hasMarkedText
{
    return [markedText length] > 0;
}

- (NSRange)markedRange
{
    return NSMakeRange(NSNotFound, 0);
}

- (NSRange)selectedRange
{
    return NSMakeRange(NSNotFound, 0);
}

- (void)setMarkedText:(id)string selectedRange:(NSRange)selectedRange replacementRange:(NSRange)replacementRange
{
    [markedText release];

    if ([string isKindOfClass:[NSAttributedString class]])
    {
        markedText = [[NSMutableAttributedString alloc] initWithAttributedString:string];
    }
    else
    {
        markedText = [[NSMutableAttributedString alloc] initWithString:string];
    }
}

- (void)unmarkText
{
    [[markedText mutableString] setString:@""];
}

- (NSArray*)validAttributesForMarkedText
{
    return [NSArray array];
}

- (NSAttributedString*)attributedSubstringForProposedRange:(NSRange)range actualRange:(NSRangePointer)actualRange
{
    return nil;
}

- (NSUInteger)characterIndexForPoint:(NSPoint)point
{
    return 0;
}

- (NSRect)firstRectForCharacterRange:(NSRange)range actualRange:(NSRangePointer)actualRange
{
    const NSRect frame = [[baseWindow->nativeHandle().window contentView] frame];
    return NSMakeRect(frame.origin.x, frame.origin.y, 0.0, 0.0);
}

- (void)insertText:(id)string replacementRange:(NSRange)replacementRange
{}

- (void)doCommandBySelector:(SEL)selector
{}

@end

auto translateKey(uint16 key) -> KeyCode
{
    switch (key)
    {
        using enum KeyCode;

        case 0x1D: return Alpha0;
        case 0x12: return Alpha1;
        case 0x13: return Alpha2;
        case 0x14: return Alpha3;
        case 0x15: return Alpha4;
        case 0x17: return Alpha5;
        case 0x16: return Alpha6;
        case 0x1A: return Alpha7;
        case 0x1C: return Alpha8;
        case 0x19: return Alpha9;

        case 0x00: return A;
        case 0x0B: return B;
        case 0x08: return C;
        case 0x02: return D;
        case 0x0E: return E;
        case 0x03: return F;
        case 0x05: return G;
        case 0x04: return H;
        case 0x22: return I;
        case 0x26: return J;
        case 0x28: return K;
        case 0x25: return L;
        case 0x2E: return M;
        case 0x2D: return N;
        case 0x1F: return O;
        case 0x23: return P;
        case 0x0C: return Q;
        case 0x0F: return R;
        case 0x01: return S;
        case 0x11: return T;
        case 0x20: return U;
        case 0x09: return V;
        case 0x0D: return W;
        case 0x07: return X;
        case 0x10: return Y;
        case 0x06: return Z;

        case 0x27: return Apostrophe;
        case 0x2a: return Backslash;
        case 0x2b: return Comma;
        case 0x18: return Equal;
        case 0x32: return GraveAccent;
        case 0x21: return LeftBracket;
        case 0x1b: return Minus;
        case 0x2f: return Period;
        case 0x1e: return RightBracket;
        case 0x29: return Semicolon;
        case 0x2c: return Slash;


        case 0x52: return Keypad0;
        case 0x53: return Keypad1;
        case 0x54: return Keypad2;
        case 0x55: return Keypad3;
        case 0x56: return Keypad4;
        case 0x57: return Keypad5;
        case 0x58: return Keypad6;
        case 0x59: return Keypad7;
        case 0x5B: return Keypad8;
        case 0x5C: return Keypad9;
        case 0x45: return KeypadAdd;
        case 0x41: return KeypadPeriod;
        case 0x4B: return KeypadDivide;
        case 0x4C: return KeypadEnter;
        case 0x51: return KeypadEqual;
        case 0x43: return KeypadMultiply;
        case 0x4E: return KeypadSubtract;

        case 0x7E: return Up;
        case 0x7D: return Down;
        case 0x7C: return Right;
        case 0x7B: return Left;

        case 0x7A: return F1;
        case 0x78: return F2;
        case 0x63: return F3;
        case 0x76: return F4;
        case 0x60: return F5;
        case 0x61: return F6;
        case 0x62: return F7;
        case 0x64: return F8;
        case 0x65: return F9;
        case 0x6D: return F10;
        case 0x67: return F11;
        case 0x6F: return F12;
        case 0x69: return F13;
        case 0x6B: return F14;
        case 0x71: return F15;
        case 0x6A: return F16;
        case 0x40: return F17;
        case 0x4F: return F18;
        case 0x50: return F19;
        case 0x5A: return F20;

        case 0x33: return Backspace;
        case 0x39: return CapsLock;
        case 0x75: return Delete;
        case 0x77: return End;
        case 0x24: return Enter;
        case 0x35: return Escape;

        default: return None;
    }
}
