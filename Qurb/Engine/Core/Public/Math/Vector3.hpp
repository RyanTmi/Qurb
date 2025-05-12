/// \file Vector3.hpp

#pragma once

#include "CoreDefines.hpp"
#include "CoreTypes.hpp"
#include "Debug/Ensure.hpp"
#include "Math/TypeTraits.hpp"

#include <format>
#include <span>

namespace qurb::math
{
    /// \brief A 3D vector class template.
    /// \tparam T The numeric type of the vector components.
    template <Numeric T>
    struct QURB_API Vector3
    {
        T x;
        T y;
        T z;

    public:
        static inline const Vector3 zero  = {0, 0, 0};
        static inline const Vector3 one   = {1, 1, 1};
        static inline const Vector3 left  = {-1, 0, 0};
        static inline const Vector3 right = {1, 0, 0};
        static inline const Vector3 up    = {0, 1, 0};
        static inline const Vector3 down  = {0, -1, 0};
        static inline const Vector3 front = {0, 0, 1};
        static inline const Vector3 back  = {0, 0, -1};

    public:
        constexpr explicit Vector3(T scalar = 0) noexcept;
        constexpr Vector3(T x, T y, T z) noexcept;

    public:
        [[nodiscard]] constexpr auto size() const noexcept -> usize;

        constexpr auto operator[](usize index) const noexcept -> T;
        constexpr auto operator[](usize index) noexcept -> T&;

        constexpr operator std::span<const T, 3>() const noexcept;
        constexpr operator std::span<T, 3>() noexcept;
    };

    using Vector3f = Vector3<float32>;
    using Vector3d = Vector3<float64>;
    using Vector3i = Vector3<int32>;

    template <Numeric T>
    constexpr Vector3<T>::Vector3(T scalar) noexcept
        : Vector3(scalar, scalar, scalar)
    {}

    template <Numeric T>
    constexpr Vector3<T>::Vector3(T x, T y, T z) noexcept
        : x(x)
        , y(y)
        , z(z)
    {}

    template <Numeric T>
    constexpr auto Vector3<T>::size() const noexcept -> usize
    {
        return 3;
    }

    template <Numeric T>
    constexpr auto Vector3<T>::operator[](usize index) const noexcept -> T
    {
        ensure(index < 3, "Index out of bounds");
        return (&x)[index];
    }

    template <Numeric T>
    constexpr auto Vector3<T>::operator[](usize index) noexcept -> T&
    {
        ensure(index < 3, "Index out of bounds");
        return (&x)[index];
    }

    template <Numeric T>
    constexpr Vector3<T>::operator std::span<const T, 3>() const noexcept
    {
        return std::span<const T, 3>(&x, 3);
    }

    template <Numeric T>
    constexpr Vector3<T>::operator std::span<T, 3>() noexcept
    {
        return std::span<T, 3>(&x, 3);
    }

    template <Numeric T>
    constexpr QURB_API auto operator+=(Vector3<T>& lhs, const Vector3<T>& rhs) noexcept -> Vector3<T>&
    {
        lhs.x += rhs.x;
        lhs.y += rhs.y;
        lhs.z += rhs.z;
        return lhs;
    }

    template <Numeric T>
    constexpr QURB_API auto operator+(Vector3<T> lhs, const Vector3<T>& rhs) noexcept -> Vector3<T>
    {
        return lhs += rhs;
    }

    template <Numeric T>
    constexpr QURB_API auto operator-=(Vector3<T>& lhs, const Vector3<T>& rhs) noexcept -> Vector3<T>&
    {
        lhs.x -= rhs.x;
        lhs.y -= rhs.y;
        lhs.z -= rhs.z;
        return lhs;
    }

    template <Numeric T>
    constexpr QURB_API auto operator-(Vector3<T> lhs, const Vector3<T>& rhs) noexcept -> Vector3<T>
    {
        return lhs -= rhs;
    }

    template <Numeric T>
    constexpr QURB_API auto operator-(const Vector3<T>& v) noexcept -> Vector3<T>
    {
        return Vector3<T>(-v.x, -v.y, -v.z);
    }

    template <Numeric T, Numeric U>
    constexpr QURB_API auto operator*=(Vector3<T>& lhs, U rhs) noexcept -> Vector3<T>&
    {
        lhs.x *= static_cast<T>(rhs);
        lhs.y *= static_cast<T>(rhs);
        lhs.z *= static_cast<T>(rhs);
        return lhs;
    }

    template <Numeric T, Numeric U>
    constexpr QURB_API auto operator*(Vector3<T> lhs, U rhs) noexcept -> Vector3<T>
    {
        return lhs *= rhs;
    }

    template <Numeric T, Numeric U>
    constexpr QURB_API auto operator*(U lhs, const Vector3<T>& rhs) noexcept -> Vector3<T>
    {
        return rhs * lhs;
    }

    template <Numeric T, Numeric U>
    constexpr QURB_API auto operator/=(Vector3<T>& lhs, U rhs) noexcept -> Vector3<T>&
    {
        lhs.x /= static_cast<T>(rhs);
        lhs.y /= static_cast<T>(rhs);
        lhs.z /= static_cast<T>(rhs);
        return lhs;
    }

    template <Numeric T, Numeric U>
    constexpr QURB_API auto operator/(Vector3<T> lhs, U rhs) noexcept -> Vector3<T>
    {
        return lhs /= rhs;
    }

    template <Numeric T>
    constexpr QURB_API auto dot(const Vector3<T>& lhs, const Vector3<T>& rhs) -> T
    {
        return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
    }

    template <Numeric T>
    constexpr QURB_API auto cross(const Vector3<T>& lhs, const Vector3<T>& rhs) -> Vector3<T>
    {
        const auto x = (lhs.y * rhs.z) - (lhs.z * rhs.y);
        const auto y = (lhs.z * rhs.x) - (lhs.x * rhs.z);
        const auto z = (lhs.x * rhs.y) - (lhs.y * rhs.x);
        return Vector3<T>(x, y, z);
    }
}

template <qurb::math::Numeric T>
struct QURB_API std::formatter<qurb::math::Vector3<T>>
{
    constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }

    template <typename FormatContext>
    auto format(const qurb::math::Vector3<T>& v, FormatContext& ctx) const
    {
        return std::format_to(ctx.out(), "[{}, {}, {}]", v.x, v.y, v.z);
    }
};
