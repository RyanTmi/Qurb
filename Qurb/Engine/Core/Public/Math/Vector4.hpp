/// \file Vector4.hpp

#pragma once

#include "CoreDefines.hpp"
#include "CoreTypes.hpp"
#include "Debug/Ensure.hpp"
#include "Math/TypeTraits.hpp"

#include <format>
#include <numeric>
#include <span>

namespace qurb::math
{
    /// \brief A 4D vector class template.
    /// \tparam T The numeric type of the vector components.
    template <Numeric T>
    struct QURB_API Vector4
    {
        T x;
        T y;
        T z;
        T w;

    public:
        static inline const Vector4 zero  = {0, 0, 0, 0};
        static inline const Vector4 one   = {1, 1, 1, 1};
        static inline const Vector4 left  = {-1, 0, 0, 0};
        static inline const Vector4 right = {1, 0, 0, 0};
        static inline const Vector4 up    = {0, 1, 0, 0};
        static inline const Vector4 down  = {0, -1, 0, 0};
        static inline const Vector4 front = {0, 0, 1, 0};
        static inline const Vector4 back  = {0, 0, -1, 0};

    public:
        constexpr explicit Vector4(T scalar = 0) noexcept;
        constexpr Vector4(T x, T y, T z, T w) noexcept;

    public:
        [[nodiscard]] constexpr auto size() const noexcept -> usize;

        constexpr auto operator[](usize index) const noexcept -> T;
        constexpr auto operator[](usize index) noexcept -> T&;

        constexpr operator std::span<const T, 4>() const noexcept;
        constexpr operator std::span<T, 4>() noexcept;
    };

    using Vector4d = Vector4<float64>;
    using Vector4f = Vector4<float32>;
    using Vector4i = Vector4<int32>;

    template <Numeric T>
    constexpr Vector4<T>::Vector4(T scalar) noexcept
        : Vector4(scalar, scalar, scalar, scalar)
    {}

    template <Numeric T>
    constexpr Vector4<T>::Vector4(T x, T y, T z, T w) noexcept
        : x(x)
        , y(y)
        , z(z)
        , w(w)
    {}

    template <Numeric T>
    constexpr auto Vector4<T>::size() const noexcept -> usize
    {
        return 4;
    }

    template <Numeric T>
    constexpr auto Vector4<T>::operator[](usize index) const noexcept -> T
    {
        ensure(index < 4, "Index out of bounds");
        return (&x)[index];
    }

    template <Numeric T>
    constexpr auto Vector4<T>::operator[](usize index) noexcept -> T&
    {
        ensure(index < 4, "Index out of bounds");
        return (&x)[index];
    }

    template <Numeric T>
    constexpr Vector4<T>::operator std::span<const T, 4>() const noexcept
    {
        return std::span<const T, 4>(&x, 4);
    }

    template <Numeric T>
    constexpr Vector4<T>::operator std::span<T, 4>() noexcept
    {
        return std::span<T, 4>(&x, 4);
    }

    template <Numeric T>
    constexpr QURB_API auto operator+=(Vector4<T>& lhs, const Vector4<T>& rhs) noexcept -> Vector4<T>&
    {
        lhs.x += rhs.x;
        lhs.y += rhs.y;
        lhs.z += rhs.z;
        lhs.w += rhs.w;
        return lhs;
    }

    template <Numeric T>
    constexpr QURB_API auto operator+(Vector4<T> lhs, const Vector4<T>& rhs) noexcept -> Vector4<T>
    {
        return lhs += rhs;
    }

    template <Numeric T>
    constexpr QURB_API auto operator-=(Vector4<T>& lhs, const Vector4<T>& rhs) noexcept -> Vector4<T>&
    {
        lhs.x -= rhs.x;
        lhs.y -= rhs.y;
        lhs.z -= rhs.z;
        lhs.w -= rhs.w;
        return lhs;
    }

    template <Numeric T>
    constexpr QURB_API auto operator-(Vector4<T> lhs, const Vector4<T>& rhs) noexcept -> Vector4<T>
    {
        return lhs -= rhs;
    }

    template <Numeric T>
    constexpr QURB_API auto operator-(const Vector4<T>& v) noexcept -> Vector4<T>
    {
        return Vector4<T>(-v.x, -v.y, -v.z, -v.w);
    }

    template <Numeric T, Numeric U>
    constexpr QURB_API auto operator*=(Vector4<T>& lhs, U rhs) noexcept -> Vector4<T>&
    {
        lhs.x *= static_cast<T>(rhs);
        lhs.y *= static_cast<T>(rhs);
        lhs.z *= static_cast<T>(rhs);
        lhs.w *= static_cast<T>(rhs);
        return lhs;
    }

    template <Numeric T, Numeric U>
    constexpr QURB_API auto operator*(Vector4<T> lhs, U rhs) noexcept -> Vector4<T>
    {
        return lhs *= rhs;
    }

    template <Numeric T, Numeric U>
    constexpr QURB_API auto operator*(U lhs, const Vector4<T>& rhs) noexcept -> Vector4<T>
    {
        return rhs * lhs;
    }

    template <Numeric T, Numeric U>
    constexpr QURB_API auto operator/=(Vector4<T>& lhs, U rhs) noexcept -> Vector4<T>&
    {
        lhs.x /= static_cast<T>(rhs);
        lhs.y /= static_cast<T>(rhs);
        lhs.z /= static_cast<T>(rhs);
        lhs.w /= static_cast<T>(rhs);
        return lhs;
    }

    template <Numeric T, Numeric U>
    constexpr QURB_API auto operator/(Vector4<T> lhs, U rhs) noexcept -> Vector4<T>
    {
        return lhs /= rhs;
    }

    template <Numeric T>
    constexpr QURB_API auto dot(const Vector4<T>& lhs, const Vector4<T>& rhs) -> T
    {
        return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
    }
}

template <qurb::math::Numeric T>
struct QURB_API std::formatter<qurb::math::Vector4<T>>
{
    constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }

    template <typename FormatContext>
    auto format(const qurb::math::Vector4<T>& v, FormatContext& ctx) const
    {
        return std::format_to(ctx.out(), "[{}, {}, {}, {}]", v.x, v.y, v.z, v.w);
    }
};
