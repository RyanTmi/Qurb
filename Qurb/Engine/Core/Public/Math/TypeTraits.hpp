/// \file TypeTraits.hpp

#pragma once

#include <concepts>
#include <numbers>
#include <type_traits>

namespace qurb::math
{
    template <typename T>
    concept Integral = std::signed_integral<T>;

    template <typename T>
    concept Real = std::floating_point<T>;

    template <typename T>
    concept Numeric = Integral<T> or Real<T>;

    template <Real T>
    constexpr auto toRadians(T degrees) noexcept -> T
    {
        return degrees * std::numbers::pi_v<T> / 180.0;
    }

    template <Real T>
    constexpr auto toDegrees(T radians) noexcept -> T
    {
        return radians * 180.0 / std::numbers::pi_v<T>;
    }
}
