/// \file Console.hpp

#pragma once

#include "CoreDefines.hpp"
#include "CoreTypes.hpp"

namespace qurb
{
    enum class ConsoleColor : uint8
    {
        Default,

        Black,
        Red,
        Green,
        Yellow,
        Blue,
        Magenta,
        Cyan,
        White,

        Black_Background,
        Red_Background,
        Green_Background,
        Yellow_Background,
        Blue_Background,
        Magenta_Background,
        Cyan_Background,
        White_Background,
    };

    class QURB_API Console final
    {
    public:
        Console() = delete;

    public:
        static auto writeLine(const char* message, bool isError = false, ConsoleColor consoleColor = ConsoleColor::Default) -> void;
    };
}
