/// \file Application.hpp

#pragma once

#include "CoreDefines.hpp"

#include <memory>

namespace qurb
{
    class QURB_API Application
    {
    public:
        Application()          = default;
        virtual ~Application() = default;

    public:
        virtual auto initialize() -> void = 0;
        virtual auto shutdown() -> void   = 0;
    };
}
