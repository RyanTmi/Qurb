#pragma once

#include "CoreTypes.hpp"
#include "Math/TypeTraits.hpp"
#include "Math/Vector3.hpp"

#include <cmath>
#include <numbers>

namespace qurb::math
{
    /// \brief A quaternion class.
    /// \tparam T The type of the quaternion elements. Must be a real type.
    template <Real T>
    class Quaternion
    {
    public:
        static inline const Quaternion identity = Quaternion();

    public:
        constexpr Quaternion() noexcept;
        constexpr Quaternion(T x, T y, T z, T w) noexcept;
        constexpr explicit Quaternion(const Vector3<T>& euler) noexcept;
        constexpr Quaternion(T degrees, const Vector3<T>& axis) noexcept;

    public:
        constexpr auto operator[](uint32 index) const noexcept -> T;

        [[nodiscard]] constexpr auto x() const noexcept -> T;
        [[nodiscard]] constexpr auto y() const noexcept -> T;
        [[nodiscard]] constexpr auto z() const noexcept -> T;
        [[nodiscard]] constexpr auto w() const noexcept -> T;

        constexpr auto normalized() const noexcept -> Quaternion;
        constexpr auto eulerAngles() const noexcept -> Vector3<T>;

    private:
        T _x;
        T _y;
        T _z;
        T _w;
    };

    using QuaternionF = Quaternion<float32>;
    using QuaternionD = Quaternion<float64>;

    template <Real T>
    constexpr Quaternion<T>::Quaternion() noexcept
        : _x(0.0)
        , _y(0.0)
        , _z(0.0)
        , _w(1.0)
    {}

    template <Real T>
    constexpr Quaternion<T>::Quaternion(T x, T y, T z, T w) noexcept
        : _x(x)
        , _y(y)
        , _z(z)
        , _w(w)
    {}

    template <Real T>
    constexpr Quaternion<T>::Quaternion(const Vector3<T>& euler) noexcept
    {
        const auto rx = toRadians(euler.x) * T(0.5);
        const auto ry = toRadians(euler.y) * T(0.5);
        const auto rz = toRadians(euler.z) * T(0.5);

        const auto cx = std::cos(rx);
        const auto sx = std::sin(rx);
        const auto cy = std::cos(ry);
        const auto sy = std::sin(ry);
        const auto cz = std::cos(rz);
        const auto sz = std::sin(rz);

        _x = sx * cy * cz - cx * sy * sz;
        _y = cx * sy * cz + sx * cy * sz;
        _z = cx * cy * sz - sx * sy * cz;
        _w = cx * cy * cz + sx * sy * sz;
    }

    template <Real T>
    constexpr Quaternion<T>::Quaternion(T degrees, const Vector3<T>& axis) noexcept
    {
        const auto halfAngle = toRadians(degrees) / T(2);
        const auto s         = std::sin(halfAngle);

        _x = axis.x * s;
        _y = axis.y * s;
        _z = axis.z * s;
        _w = std::cos(halfAngle);
    }

    template <Real T>
    constexpr auto Quaternion<T>::operator[](uint32 index) const noexcept -> T
    {
        ensure(index < 4, "Index out of bounds");
        return (&_x)[index];
    }

    template <Real T>
    constexpr auto Quaternion<T>::x() const noexcept -> T
    {
        return _x;
    }

    template <Real T>
    constexpr auto Quaternion<T>::y() const noexcept -> T
    {
        return _y;
    }

    template <Real T>
    constexpr auto Quaternion<T>::z() const noexcept -> T
    {
        return _z;
    }

    template <Real T>
    constexpr auto Quaternion<T>::w() const noexcept -> T
    {
        return _w;
    }

    template <Real T>
    constexpr auto Quaternion<T>::normalized() const noexcept -> Quaternion<T>
    {
        const auto norm = std::sqrt(_x * _x + _y * _y + _z * _z + _w * _w);
        ensure(norm > 0, "Cannot normalize a zero quaternion");

        return Quaternion(_x / norm, _y / norm, _z / norm, _w / norm);
    }

    template <Real T>
    constexpr auto Quaternion<T>::eulerAngles() const noexcept -> Vector3<T>
    {
        // roll (x-axis rotation)
        const auto sinRoll = 2.0 * (_w * _x + _y * _z);
        const auto cosRoll = 1.0 - 2.0 * (_x * _x + _y * _y);

        // pitch (y-axis rotation)
        const auto sinPitch = std::sqrt(1.0 + 2.0 * (_w * _y - _x * _z));
        const auto cosPitch = std::sqrt(1.0 - 2.0 * (_w * _y - _x * _z));

        // yaw (z-axis rotation)
        const auto sinYaw = 2.0 * (_w * _z + _x * _y);
        const auto cosYaw = 1.0 - 2.0 * (_y * _y + _z * _z);

        const auto x = std::atan2(sinRoll, cosRoll);
        const auto y = 2.0 * std::atan2(sinPitch, cosPitch) - 0.5 * std::numbers::pi_v<T>;
        const auto z = std::atan2(sinYaw, cosYaw);
        return Vector3<T>(x, y, z);
    }

    template <Real T>
    constexpr auto operator*(const Quaternion<T>& lhs, const Quaternion<T>& rhs) noexcept -> Quaternion<T>
    {
        const auto x = lhs.w() * rhs.x() + lhs.x() * rhs.w() + lhs.y() * rhs.z() - lhs.z() * rhs.y();
        const auto y = lhs.w() * rhs.y() - lhs.x() * rhs.z() + lhs.y() * rhs.w() + lhs.z() * rhs.x();
        const auto z = lhs.w() * rhs.z() + lhs.x() * rhs.y() - lhs.y() * rhs.x() + lhs.z() * rhs.w();
        const auto w = lhs.w() * rhs.w() - lhs.x() * rhs.x() - lhs.y() * rhs.y() - lhs.z() * rhs.z();
        return Quaternion<T>(x, y, z, w);
    }
}
