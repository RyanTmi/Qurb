/// \file Clock.hpp

#pragma once

#include "CoreTypes.hpp"

#include <chrono>

namespace qurb
{
    /// \brief The `Clock` class.
    class Clock final
    {
    public:
        Clock() = default;

    public:
        auto start() -> void;
        auto update() -> void;

        [[nodiscard]] auto deltaTime() const -> float64;
        [[nodiscard]] auto time() const -> float64;

    private:
        using BaseClock = std::chrono::high_resolution_clock;
        using TimePoint = std::chrono::time_point<BaseClock>;
        using Duration  = std::chrono::duration<float64, std::milli>;

    private:
        TimePoint _startTime;
        TimePoint _lastFrameTime;
        TimePoint _currentTime;
    };

    inline auto Clock::start() -> void
    {
        _startTime     = BaseClock::now();
        _lastFrameTime = _startTime;
        _currentTime   = _startTime;
    }

    inline auto Clock::update() -> void
    {
        _lastFrameTime = _currentTime;
        _currentTime   = BaseClock::now();
    }

    inline auto Clock::deltaTime() const -> float64
    {
        return Duration(_currentTime - _lastFrameTime).count() / 1000.0;
    }

    inline auto Clock::time() const -> float64
    {
        return Duration(_currentTime - _startTime).count() / 1000.0;
    }
}
