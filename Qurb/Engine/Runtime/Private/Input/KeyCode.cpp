#include "Input/KeyCode.hpp"

namespace qurb
{
    auto toString(KeyCode keyCode) -> std::string_view
    {
        switch (keyCode)
        {
            using enum KeyCode;

            case Alpha0:         return "Alpha0";
            case Alpha1:         return "Alpha1";
            case Alpha2:         return "Alpha2";
            case Alpha3:         return "Alpha3";
            case Alpha4:         return "Alpha4";
            case Alpha5:         return "Alpha5";
            case Alpha6:         return "Alpha6";
            case Alpha7:         return "Alpha7";
            case Alpha8:         return "Alpha8";
            case Alpha9:         return "Alpha9";
            case A:              return "A";
            case B:              return "B";
            case C:              return "C";
            case D:              return "D";
            case E:              return "E";
            case F:              return "F";
            case G:              return "G";
            case H:              return "H";
            case I:              return "I";
            case J:              return "J";
            case K:              return "K";
            case L:              return "L";
            case M:              return "M";
            case N:              return "N";
            case O:              return "O";
            case P:              return "P";
            case Q:              return "Q";
            case R:              return "R";
            case S:              return "S";
            case T:              return "T";
            case U:              return "U";
            case V:              return "V";
            case W:              return "W";
            case X:              return "X";
            case Y:              return "Y";
            case Z:              return "Z";
            case Apostrophe:     return "Apostrophe";
            case Backslash:      return "Backslash";
            case Comma:          return "Comma";
            case Equal:          return "Equal";
            case GraveAccent:    return "GraveAccent";
            case LeftBracket:    return "LeftBracket";
            case Minus:          return "Minus";
            case Period:         return "Period";
            case RightBracket:   return "RightBracket";
            case Semicolon:      return "Semicolon";
            case Slash:          return "Slash";
            case LeftAlt:        return "LeftAlt";
            case LeftControl:    return "LeftControl";
            case LeftShift:      return "LeftShift";
            case LeftSuper:      return "LeftSuper";
            case RightAlt:       return "RightAlt";
            case RightControl:   return "RightControl";
            case RightShift:     return "RightShift";
            case RightSuper:     return "RightSuper";
            case Keypad0:        return "Keypad0";
            case Keypad1:        return "Keypad1";
            case Keypad2:        return "Keypad2";
            case Keypad3:        return "Keypad3";
            case Keypad4:        return "Keypad4";
            case Keypad5:        return "Keypad5";
            case Keypad6:        return "Keypad6";
            case Keypad7:        return "Keypad7";
            case Keypad8:        return "Keypad8";
            case Keypad9:        return "Keypad9";
            case KeypadAdd:      return "KeypadAdd";
            case KeypadPeriod:   return "KeypadPeriod";
            case KeypadDivide:   return "KeypadDivide";
            case KeypadEnter:    return "KeypadEnter";
            case KeypadEqual:    return "KeypadEqual";
            case KeypadMultiply: return "KeypadMultiply";
            case KeypadSubtract: return "KeypadSubtract";
            case Up:             return "Up";
            case Down:           return "Down";
            case Right:          return "Right";
            case Left:           return "Left";
            case F1:             return "F1";
            case F2:             return "F2";
            case F3:             return "F3";
            case F4:             return "F4";
            case F5:             return "F5";
            case F6:             return "F6";
            case F7:             return "F7";
            case F8:             return "F8";
            case F9:             return "F9";
            case F10:            return "F10";
            case F11:            return "F11";
            case F12:            return "F12";
            case F13:            return "F13";
            case F14:            return "F14";
            case F15:            return "F15";
            case F16:            return "F16";
            case F17:            return "F17";
            case F18:            return "F18";
            case F19:            return "F19";
            case F20:            return "F20";
            case Backspace:      return "Backspace";
            case CapsLock:       return "CapsLock";
            case Delete:         return "Delete";
            case End:            return "End";
            case Enter:          return "Enter";
            case Escape:         return "Escape";
            default:             return "None";
        }
    }
}
