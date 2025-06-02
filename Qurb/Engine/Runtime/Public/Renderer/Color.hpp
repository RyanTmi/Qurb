/// \file Color.hpp

#pragma once

#include "CoreDefines.hpp"
#include "CoreTypes.hpp"
#include "Math/Vector4.hpp"

namespace qurb
{
    /// \brief The `Color` class.
    struct QURB_API Color final
    {
        float32 r;
        float32 g;
        float32 b;
        float32 a;

    public:
        static const Color black;
        static const Color white;
        static const Color red;
        static const Color green;
        static const Color blue;
        static const Color orange;
        static const Color purple;
        static const Color yellow;

    public:
        constexpr Color() noexcept = default;
        constexpr Color(float32 r, float32 g, float32 b, float32 a = 1.0f) noexcept;
        constexpr explicit Color(float32 c) noexcept;
        constexpr explicit Color(const math::Vector4f& color) noexcept;
    };

    constexpr Color::Color(float32 r, float32 g, float32 b, float32 a) noexcept
        : r(r)
        , g(g)
        , b(b)
        , a(a)
    {}

    constexpr Color::Color(float32 c) noexcept
        : Color(c, c, c, c)
    {}

    constexpr Color::Color(const math::Vector4f& color) noexcept
        : Color(color.x, color.y, color.z, color.w)
    {}
}
