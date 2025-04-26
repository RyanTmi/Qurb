/// \file EntryPoint.hpp

#pragma once

#include "Core/Engine.hpp"

namespace qurb
{
    extern auto createApplication() -> Application*;
}

auto main([[maybe_unused]] int argc, [[maybe_unused]] const char** argv) -> int
{
    using namespace qurb;

    auto application = createApplication();
    auto engine      = Engine(application);
    engine.run();
}
