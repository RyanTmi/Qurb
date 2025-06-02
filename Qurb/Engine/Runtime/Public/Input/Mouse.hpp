/// \file Mouse.hpp

#pragma once

#include "CoreDefines.hpp"
#include "Math/Vector2.hpp"

namespace qurb
{
    class QURB_API Mouse final
    {
    public:
        Mouse() = delete;

    public:
        static auto position() -> math::Vector2f;
    };
}
