#include "Sandbox.hpp"

#include <Core/Engine.hpp>
#include <EntryPoint.hpp>

using namespace qurb;

auto SandboxApplication::initialize() -> void
{
    _renderContext = _engine->activeWindow().renderContext();
    _renderContext->retain();

    Log::info("{} initialized", _name);
}

auto SandboxApplication::shutdown() -> void
{
    _renderContext->release();
    _renderContext = nullptr;

    Log::info("{} shutdown", _name);
}

auto SandboxApplication::update(float32 deltaTime) -> void {}

auto SandboxApplication::render() -> void
{
    _renderContext->beginFrame();

    _sceneRenderer.render(_renderContext);

    _renderContext->present();
    _renderContext->endFrame();
}

auto qurb::createApplication() -> Application*
{
    ApplicationDescriptor descriptor = {
        .name = "Qurb Sandbox",
    };

    return new SandboxApplication(descriptor);
}
