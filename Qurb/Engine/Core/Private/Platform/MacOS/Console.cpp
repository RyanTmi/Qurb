#include "Platform/Console.hpp"

#include <print>

namespace qurb
{
    static constexpr auto getColorCode(ConsoleColor color) -> const char*
    {
        switch (color)
        {
            using enum ConsoleColor;

            default:
            case Default:            return "\033[0m";
            case Black:              return "\033[30m";
            case Red:                return "\033[31m";
            case Green:              return "\033[32m";
            case Yellow:             return "\033[33m";
            case Blue:               return "\033[34m";
            case Magenta:            return "\033[35m";
            case Cyan:               return "\033[36m";
            case White:              return "\033[37m";
            case Black_Background:   return "\033[40m";
            case Red_Background:     return "\033[41m";
            case Green_Background:   return "\033[42m";
            case Yellow_Background:  return "\033[43m";
            case Blue_Background:    return "\033[44m";
            case Magenta_Background: return "\033[45m";
            case Cyan_Background:    return "\033[46m";
            case White_Background:   return "\033[47m";
        }
    }

    auto Console::writeLine(const char* message, bool isError, ConsoleColor consoleColor) -> void
    {
        const auto colorCode   = getColorCode(consoleColor);
        const auto defaultCode = getColorCode(ConsoleColor::Default);

        const auto stream = isError ? stderr : stdout;

        std::println(stream, "{}{}{}", colorCode, message, defaultCode);
    }
}
