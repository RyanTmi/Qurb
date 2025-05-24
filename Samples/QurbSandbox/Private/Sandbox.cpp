#include "Sandbox.hpp"

#include <Core/Engine.hpp>
#include <EntryPoint.hpp>
#include <Scene/Components.hpp>
#include <Scene/Entity.hpp>

using namespace qurb;

auto SandboxApplication::initialize() -> void
{
    _renderContext = _engine->activeWindow().renderContext();
    _renderContext->retain();

    Vector<Entity> entities;
    entities.reserve(20);
    for (int i = 0; i < 20; ++i)
    {
        entities.pushBack(_scene.registery().createEntity());

        auto& tagComponent = entities[i].addComponent<TagComponent>();
        tagComponent.name  = std::format("Entity {}", i);
    }

    for (auto& entity : entities)
    {
        auto& tagComponent = entity.getComponent<TagComponent>();
        Log::debug("{}", tagComponent.name);
        tagComponent.name = std::format("Updated {}", tagComponent.name);
    }

    for (auto& entity : entities)
    {
        auto& tagComponent = entity.getComponent<TagComponent>();
        Log::debug("{}", tagComponent.name);
    }

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
