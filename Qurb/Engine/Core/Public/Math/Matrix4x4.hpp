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

        auto inverse() const noexcept -> Matrix4x4<T>;

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
    auto Matrix4x4<T>::inverse() const noexcept -> Matrix4x4<T>
    {
        auto data = reinterpret_cast<const T(*)[4]>(_data);

        T i0  = data[1][1] * data[3][3];
        T i1  = data[3][2] * data[2][3];
        T i2  = data[1][2] * data[3][3];
        T i3  = data[3][2] * data[1][3];
        T i4  = data[1][2] * data[2][3];
        T i5  = data[1][1] * data[1][3];
        T i6  = data[0][2] * data[3][3];
        T i7  = data[3][2] * data[0][3];
        T i8  = data[0][2] * data[2][3];
        T i9  = data[1][1] * data[0][3];
        T i10 = data[0][2] * data[1][3];
        T i11 = data[1][2] * data[0][3];
        T i12 = data[2][0] * data[3][1];
        T i13 = data[3][0] * data[2][1];
        T i14 = data[1][0] * data[3][1];
        T i15 = data[3][0] * data[1][1];
        T i16 = data[1][0] * data[2][1];
        T i17 = data[2][0] * data[1][1];
        T i18 = data[0][0] * data[3][1];
        T i19 = data[3][0] * data[0][1];
        T i20 = data[0][0] * data[2][1];
        T i21 = data[2][0] * data[0][1];
        T i22 = data[0][0] * data[1][1];
        T i23 = data[1][0] * data[0][1];

        Matrix4x4<T> inverse;
        inverse[0, 0] = (i0 * data[1][1] + i3 * data[2][1] + i4 * data[3][1]) - (i1 * data[1][1] + i2 * data[2][1] + i5 * data[3][1]);
        inverse[0, 1] = (i1 * data[0][1] + i6 * data[2][1] + i9 * data[3][1]) - (i0 * data[0][1] + i7 * data[2][1] + i8 * data[3][1]);
        inverse[0, 2] = (i2 * data[0][1] + i7 * data[1][1] + i10 * data[3][1]) - (i3 * data[0][1] + i6 * data[1][1] + i11 * data[3][1]);
        inverse[0, 3] = (i5 * data[0][1] + i8 * data[1][1] + i11 * data[2][1]) - (i4 * data[0][1] + i9 * data[1][1] + i10 * data[2][1]);

        T d = T(1) / (data[0][0] * inverse[0, 0] + data[1][0] * inverse[0, 1] + data[2][0] * inverse[0, 2] + data[3][0] * inverse[3, 0]);

        inverse[0, 0] = d * inverse[0, 0];
        inverse[0, 1] = d * inverse[0, 1];
        inverse[0, 2] = d * inverse[0, 2];
        inverse[0, 3] = d * inverse[0, 3];

        inverse[1, 0] = d * ((i1 * data[1][0] + i2 * data[2][0] + i5 * data[3][0]) - (i0 * data[1][0] + i3 * data[2][0] + i4 * data[3][0]));
        inverse[1, 1] = d * ((i0 * data[0][0] + i7 * data[2][0] + i8 * data[3][0]) - (i1 * data[0][0] + i6 * data[2][0] + i9 * data[3][0]));
        inverse[1, 2] = d * ((i3 * data[0][0] + i6 * data[1][0] + i11 * data[3][0]) - (i2 * data[0][0] + i7 * data[1][0] + i10 * data[3][0]));
        inverse[1, 3] = d * ((i4 * data[0][0] + i9 * data[1][0] + i10 * data[2][0]) - (i5 * data[0][0] + i8 * data[1][0] + i11 * data[2][0]));

        inverse[2, 0] = d * ((i12 * data[1][3] + i15 * data[2][3] + i16 * data[3][3]) - (i13 * data[1][3] + i14 * data[2][3] + i17 * data[3][3]));
        inverse[2, 1] = d * ((i13 * data[3][0] + i18 * data[2][3] + i21 * data[3][3]) - (i12 * data[3][0] + i19 * data[2][3] + i20 * data[3][3]));
        inverse[2, 2] = d * ((i14 * data[3][0] + i19 * data[1][3] + i22 * data[3][3]) - (i15 * data[3][0] + i18 * data[1][3] + i23 * data[3][3]));
        inverse[2, 3] = d * ((i17 * data[3][0] + i20 * data[1][3] + i23 * data[2][3]) - (i16 * data[3][0] + i21 * data[1][3] + i22 * data[2][3]));

        inverse[3, 0] = d * ((i14 * data[2][2] + i17 * data[3][2] + i13 * data[1][2]) - (i16 * data[3][2] + i12 * data[1][2] + i15 * data[2][2]));
        inverse[3, 1] = d * ((i20 * data[3][2] + i12 * data[2][0] + i19 * data[2][2]) - (i18 * data[2][2] + i21 * data[3][2] + i13 * data[2][0]));
        inverse[3, 2] = d * ((i18 * data[1][2] + i23 * data[3][2] + i15 * data[2][0]) - (i22 * data[3][2] + i14 * data[2][0] + i19 * data[1][2]));
        inverse[3, 3] = d * ((i22 * data[2][2] + i16 * data[2][0] + i21 * data[1][2]) - (i20 * data[1][2] + i23 * data[2][2] + i17 * data[2][0]));
        return inverse;
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
