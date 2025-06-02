/// \file Vector2.hpp

#pragma once

#include "CoreTypes.hpp"
#include "Debug/Ensure.hpp"
#include "Math/TypeTraits.hpp"

#include <format>
#include <span>

namespace qurb::math
{
    /// \brief A 2D vector class template.
    /// \tparam T The numeric type of the vector components.
    template <Numeric T>
    struct Vector2
    {
        T x;
        T y;

    public:
        static inline const Vector2 zero  = {0, 0};
        static inline const Vector2 one   = {1, 1};
        static inline const Vector2 left  = {-1, 0};
        static inline const Vector2 right = {1, 0};
        static inline const Vector2 up    = {0, 1};
        static inline const Vector2 down  = {0, -1};

    public:
        constexpr explicit Vector2(T scalar = 0) noexcept;
        constexpr Vector2(T x, T y) noexcept;

    public:
        [[nodiscard]] constexpr auto size() const noexcept -> usize;

        constexpr auto operator[](usize index) const noexcept -> T;
        constexpr auto operator[](usize index) noexcept -> T&;

        constexpr operator std::span<const T, 2>() const noexcept;
        constexpr operator std::span<T, 2>() noexcept;
    };

    using Vector2d = Vector2<float64>;
    using Vector2f = Vector2<float32>;
    using Vector2i = Vector2<int32>;

    template <Numeric T>
    constexpr Vector2<T>::Vector2(T scalar) noexcept
        : Vector2(scalar, scalar)
    {}

    template <Numeric T>
    constexpr Vector2<T>::Vector2(T x, T y) noexcept
        : x(x)
        , y(y)
    {}

    template <Numeric T>
    constexpr auto Vector2<T>::size() const noexcept -> usize
    {
        return 2;
    }

    template <Numeric T>
    constexpr auto Vector2<T>::operator[](usize index) const noexcept -> T
    {
        ensure(index < 2, "Index out of bounds");
        return (&x)[index];
    }

    template <Numeric T>
    constexpr auto Vector2<T>::operator[](usize index) noexcept -> T&
    {
        ensure(index < 2, "Index out of bounds");
        return (&x)[index];
    }

    template <Numeric T>
    constexpr Vector2<T>::operator std::span<const T, 2>() const noexcept
    {
        return std::span<const T, 2>(&x, 2);
    }

    template <Numeric T>
    constexpr Vector2<T>::operator std::span<T, 2>() noexcept
    {
        return std::span<T, 2>(&x, 2);
    }

    template <Numeric T>
    constexpr auto operator+=(Vector2<T>& lhs, const Vector2<T>& rhs) noexcept -> Vector2<T>&
    {
        lhs.x += rhs.x;
        lhs.y += rhs.y;
        return lhs;
    }

    template <Numeric T>
    constexpr auto operator+(Vector2<T> lhs, const Vector2<T>& rhs) noexcept -> Vector2<T>
    {
        return lhs += rhs;
    }

    template <Numeric T>
    constexpr auto operator-=(Vector2<T>& lhs, const Vector2<T>& rhs) noexcept -> Vector2<T>&
    {
        lhs.x -= rhs.x;
        lhs.y -= rhs.y;
        return lhs;
    }

    template <Numeric T>
    constexpr auto operator-(Vector2<T> lhs, const Vector2<T>& rhs) noexcept -> Vector2<T>
    {
        return lhs -= rhs;
    }

    template <Numeric T>
    constexpr auto operator-(const Vector2<T>& v) noexcept -> Vector2<T>
    {
        return Vector2<T>(-v.x, -v.y);
    }

    template <Numeric T, Numeric U>
    constexpr auto operator*(const Vector2<T>& v, U scalar) noexcept -> Vector2<T>
    {
        return Vector2<T>(scalar * v.x, scalar * v.y);
    }

    template <Numeric T, Numeric U>
    constexpr QURB_API auto operator*=(Vector2<T>& lhs, U rhs) noexcept -> Vector2<T>&
    {
        lhs.x *= static_cast<T>(rhs);
        lhs.y *= static_cast<T>(rhs);
        return lhs;
    }

    template <Numeric T, Numeric U>
    constexpr QURB_API auto operator*(Vector2<T> lhs, U rhs) noexcept -> Vector2<T>
    {
        return lhs *= rhs;
    }

    template <Numeric T, Numeric U>
    constexpr QURB_API auto operator*(U lhs, const Vector2<T>& rhs) noexcept -> Vector2<T>
    {
        return rhs * lhs;
    }

    template <Numeric T, Numeric U>
    constexpr QURB_API auto operator/=(Vector2<T>& lhs, U rhs) noexcept -> Vector2<T>&
    {
        lhs.x /= static_cast<T>(rhs);
        lhs.y /= static_cast<T>(rhs);
        return lhs;
    }

    template <Numeric T, Numeric U>
    constexpr QURB_API auto operator/(Vector2<T> lhs, U rhs) noexcept -> Vector2<T>
    {
        return lhs /= rhs;
    }

    template <Numeric T>
    constexpr QURB_API auto dot(const Vector2<T>& lhs, const Vector2<T>& rhs) -> T
    {
        return lhs.x * rhs.x + lhs.y * rhs.y;
    }
}

template <qurb::math::Numeric T>
struct QURB_API std::formatter<qurb::math::Vector2<T>>
{
    constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }

    template <typename FormatContext>
    auto format(const qurb::math::Vector2<T>& v, FormatContext& ctx) const
    {
        return std::format_to(ctx.out(), "[{}, {}]", v.x, v.y);
    }
};
