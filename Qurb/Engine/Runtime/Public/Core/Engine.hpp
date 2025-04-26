/// \file Engine.hpp

#pragma once

#include "Core/Application.hpp"
#include "CoreDefines.hpp"

#include <memory>

auto main(int argc, const char** argv) -> int;

namespace qurb
{
    class QURB_API Engine
    {
    public:
        explicit Engine(Application* application);
        ~Engine();

    private:
        friend auto ::main(int argc, const char** argv) -> int;

    private:
        auto run() -> void;

    private:
        std::unique_ptr<Application> _application;
    };
}
