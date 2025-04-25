/// \file TypeTraits.hpp

#pragma once

namespace qurb
{
    template <typename T, T v>
    struct IntegralConstant
    {
        static constexpr T value = v;
    };

    using TrueType  = IntegralConstant<bool, true>;
    using FalseType = IntegralConstant<bool, false>;
}
