/// \file Matrix4x4.hpp

#pragma once

#include "CoreTypes.hpp"
#include "Debug/Ensure.hpp"
#include "Math/Quaternion.hpp"
#include "Math/TypeTraits.hpp"
#include "Math/Vector4.hpp"

#include <format>
#include <span>

namespace qurb::math
{
    /// \brief A 4x4 matrix class.
    /// \tparam T The type of the matrix elements. Must be a numeric type.
    template <Numeric T>
    class Matrix4x4
    {
    public:
        static inline const Matrix4x4 zero     = Matrix4x4();
        static inline const Matrix4x4 identity = Matrix4x4(1);

    public:
        constexpr Matrix4x4() noexcept;
        constexpr explicit Matrix4x4(T scalar) noexcept;

    public:
        [[nodiscard]] constexpr auto data() noexcept -> T*;
        [[nodiscard]] constexpr auto data() const noexcept -> const T*;

        constexpr auto operator[](uint32 i, uint32 j) const noexcept -> const T&;
        constexpr auto operator[](uint32 i, uint32 j) noexcept -> T&;

    private:
        T _data[16];
    };

    using Matrix4x4f = Matrix4x4<float32>;
    using Matrix4x4d = Matrix4x4<float64>;

    template <Numeric T>
    constexpr Matrix4x4<T>::Matrix4x4() noexcept
        : _data()
    {}

    template <Numeric T>
    constexpr Matrix4x4<T>::Matrix4x4(T scalar) noexcept
    {
        for (int32 i = 0; i < 4; ++i)
        {
            operator[](i, i) = scalar;
        }
    }

    template <Numeric T>
    constexpr auto Matrix4x4<T>::data() noexcept -> T*
    {
        return _data;
    }

    template <Numeric T>
    constexpr auto Matrix4x4<T>::data() const noexcept -> const T*
    {
        return _data;
    }

    template <Numeric T>
    constexpr auto Matrix4x4<T>::operator[](uint32 i, uint32 j) const noexcept -> const T&
    {
        ensure(i < 4 and j < 4, "Indices out of bounds");
        return _data[i * 4 + j];
    }

    template <Numeric T>
    constexpr auto Matrix4x4<T>::operator[](uint32 i, uint32 j) noexcept -> T&
    {
        ensure(i < 4 and j < 4, "Indices out of bounds");
        return _data[i * 4 + j];
    }

    template <Numeric T>
    constexpr auto operator+=(Matrix4x4<T>& lhs, const Matrix4x4<T>& rhs) -> Matrix4x4<T>&
    {
        for (uint32 i = 0; i < 4; ++i)
        {
            for (uint32 j = 0; j < 4; ++j)
            {
                lhs[i, j] += rhs[i, j];
            }
        }
        return lhs;
    }

    template <Numeric T>
    constexpr auto operator+(Matrix4x4<T> lhs, const Matrix4x4<T>& rhs) -> Matrix4x4<T>
    {
        return lhs += rhs;
    }

    template <Numeric T>
    constexpr auto operator-=(Matrix4x4<T>& lhs, const Matrix4x4<T>& rhs) -> Matrix4x4<T>&
    {
        for (uint32 i = 0; i < 4; ++i)
        {
            for (uint32 j = 0; j < 4; ++j)
            {
                lhs[i, j] -= rhs[i, j];
            }
        }
        return lhs;
    }

    template <Numeric T>
    constexpr auto operator-(Matrix4x4<T> lhs, const Matrix4x4<T>& rhs) -> Matrix4x4<T>
    {
        return lhs -= rhs;
    }

    template <Numeric T>
    constexpr auto operator-(const Matrix4x4<T>& mat) -> Matrix4x4<T>
    {
        auto res = Matrix4x4<T>();

        T* mat_data = mat.data();
        T* res_data = res.data();
        for (uint32 i = 0; i < 16; ++i)
        {
            res_data[i] = -mat_data[i];
        }

        return res;
    }

    template <Numeric T>
    constexpr auto operator*(const Matrix4x4<T>& lhs, const Matrix4x4<T>& rhs) -> Matrix4x4<T>
    {
        auto res = Matrix4x4<T>();

        for (uint32 i = 0; i < 4; ++i)
        {
            for (uint32 k = 0; k < 4; ++k)
            {
                for (uint32 j = 0; j < 4; ++j)
                {
                    res[i, j] += lhs[i, k] * rhs[k, j];
                }
            }
        }

        return res;
    }

    template <Numeric T>
    constexpr auto operator*=(Matrix4x4<T>& lhs, const Matrix4x4<T>& rhs) -> Matrix4x4<T>
    {
        lhs = lhs * rhs;
        return lhs;
    }

    template <Numeric T>
    constexpr auto operator*(const Matrix4x4<T>& lhs, const Vector4<T>& rhs) -> Vector4<T>
    {
        auto res = Vector4<T>();

        for (int32 i = 0; i < 4; ++i)
        {
            for (int32 j = 0; j < 4; ++j)
            {
                res[i] += lhs[i, j] * rhs[j];
            }
        }

        return res;
    }

    template <Real T>
    constexpr auto translationMatrix(const Vector3<T>& translation) noexcept -> Matrix4x4<T>
    {
        auto res  = Matrix4x4<T>::identity;
        res[0, 3] = translation.x;
        res[1, 3] = translation.y;
        res[2, 3] = translation.z;
        return res;
    }

    template <Real T>
    constexpr auto scaleMatrix(const Vector3<T>& scale) noexcept -> Matrix4x4<T>
    {
        auto res  = Matrix4x4<T>::identity;
        res[0, 0] = scale.x;
        res[1, 1] = scale.y;
        res[2, 2] = scale.z;
        return res;
    }

    template <Real T>
    constexpr auto rotationMatrix(const Quaternion<T>& quat) noexcept -> Matrix4x4<T>
    {
        auto q   = quat.normalized();
        auto res = Matrix4x4<T>::identity;

        auto xx = q.x() * q.x();
        auto yy = q.y() * q.y();
        auto zz = q.z() * q.z();
        auto xy = q.x() * q.y();
        auto xz = q.x() * q.z();
        auto yz = q.y() * q.z();
        auto wx = q.w() * q.x();
        auto wy = q.w() * q.y();
        auto wz = q.w() * q.z();

        res[0, 0] = 1 - 2 * (yy + zz);
        res[0, 1] = 2 * (xy - wz);
        res[0, 2] = 2 * (xz + wy);

        res[1, 0] = 2 * (xy + wz);
        res[1, 1] = 1 - 2 * (xx + zz);
        res[1, 2] = 2 * (yz - wx);

        res[2, 0] = 2 * (xz - wy);
        res[2, 1] = 2 * (yz + wx);
        res[2, 2] = 1 - 2 * (xx + yy);

        return res;
    }

    template <Real T>
    constexpr auto rotationMatrix(const Vector3<T>& euler) noexcept -> Matrix4x4<T>
    {
        return rotationMatrix(Quaternion<T>(euler));
    }
}

template <qurb::math::Numeric T>
struct std::formatter<qurb::math::Matrix4x4<T>>
{
    constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }

    template <typename FormatContext>
    auto format(const qurb::math::Matrix4x4<T>& m, FormatContext& ctx) const
    {
        auto sp0 = std::span(&m[0, 0], 4);
        auto sp1 = std::span(&m[1, 0], 4);
        auto sp2 = std::span(&m[2, 0], 4);
        auto sp3 = std::span(&m[3, 0], 4);
        return std::format_to(ctx.out(), "[{::4.8f}\n {::4.8f}\n {::4.8f}\n {::4.8f}]", sp0, sp1, sp2, sp3);
    }
};
