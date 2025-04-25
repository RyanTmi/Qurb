/// \file Log.hpp

#pragma once

#include "CoreDefines.hpp"
#include "CoreTypes.hpp"
#include "Platform/Console.hpp"

#include <format>
#include <unordered_map>

namespace qurb
{
    enum class QURB_API LogLevel : uint8
    {
        Fatal,
        Error,
        Warn,
        Info,
        Debug,
        Trace
    };

    class QURB_API Log final
    {
    public:
        Log() = delete;

    public:
        template <typename... Args>
        static auto fatal(std::format_string<Args...> fmt, Args&&... args) -> void;

        template <typename... Args>
        static auto error(std::format_string<Args...> fmt, Args&&... args) -> void;

        template <typename... Args>
        static auto warn(std::format_string<Args...> fmt, Args&&... args) -> void;

        template <typename... Args>
        static auto info(std::format_string<Args...> fmt, Args&&... args) -> void;

        template <typename... Args>
        static auto debug(std::format_string<Args...> fmt, Args&&... args) -> void;

        template <typename... Args>
        static auto trace(std::format_string<Args...> fmt, Args&&... args) -> void;

    private:
        struct LogInfo
        {
            ConsoleColor consoleColor;
            const char*  header;
            bool         isError;
        };

        static const std::unordered_map<LogLevel, LogInfo> logInfoMap;

    private:
        template <typename... Args>
        static auto logMessage(LogLevel level, std::format_string<Args...> fmt, Args&&... args) -> void;
    };

    template <typename... Args>
    auto Log::fatal(std::format_string<Args...> fmt, Args&&... args) -> void
    {
        logMessage(LogLevel::Fatal, fmt, std::forward<Args...>(args)...);
    }

    template <typename... Args>
    auto Log::error(std::format_string<Args...> fmt, Args&&... args) -> void
    {
        logMessage(LogLevel::Error, fmt, std::forward<Args...>(args)...);
    }

    template <typename... Args>
    auto Log::warn(std::format_string<Args...> fmt, Args&&... args) -> void
    {
        logMessage(LogLevel::Warn, fmt, std::forward<Args...>(args)...);
    }

    template <typename... Args>
    auto Log::info(std::format_string<Args...> fmt, Args&&... args) -> void
    {
        logMessage(LogLevel::Info, fmt, std::forward<Args...>(args)...);
    }

    template <typename... Args>
    auto Log::debug(std::format_string<Args...> fmt, Args&&... args) -> void
    {
        logMessage(LogLevel::Debug, fmt, std::forward<Args...>(args)...);
    }

    template <typename... Args>
    auto Log::trace(std::format_string<Args...> fmt, Args&&... args) -> void
    {
        logMessage(LogLevel::Trace, fmt, std::forward<Args...>(args)...);
    }

    template <typename... Args>
    auto Log::logMessage(LogLevel level, std::format_string<Args...> fmt, Args&&... args) -> void
    {
        const auto info        = logInfoMap.at(level);
        const auto message     = std::format(fmt, std::forward<Args...>(args)...);
        const auto fullMessage = std::format("[{}]: {}", info.header, message);

        Console::writeLine(fullMessage.c_str(), info.isError, info.consoleColor);
    }
}
