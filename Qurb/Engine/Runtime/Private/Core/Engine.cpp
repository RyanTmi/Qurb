#include "Core/Engine.hpp"

namespace qurb
{
    Engine::Engine(Application* application)
        : _application(application)
    {
        _application->initialize();
    }

    Engine::~Engine()
    {
        _application->shutdown();
    }

    auto Engine::run() -> void
    {}
}
