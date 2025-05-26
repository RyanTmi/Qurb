#pragma once

#include <Core/Application.hpp>
#include <CoreMinimal.hpp>
#include <Events/WindowEvents.hpp>
#include <RHI/Device.hpp>
#include <RHI/RenderContext.hpp>
#include <Scene/Scene.hpp>
#include <Scene/SceneRenderer.hpp>

using namespace qurb;

class SandboxApplication final : public Application
{
public:
    explicit SandboxApplication(const ApplicationDescriptor& descriptor);
    ~SandboxApplication() override = default;

public:
    auto initialize() -> void override;
    auto shutdown() -> void override;

    auto update(float32 deltaTime) -> void override;
    auto render() -> void override;

private:
    auto onWindowResize(const WindowResizeEvent& event) -> bool;

    auto createQuad() -> void;
    auto createCamera() -> void;

private:
    rhi::Device*                   _device;
    rhi::RenderContext*            _renderContext;
    std::unique_ptr<Scene>         _scene;
    std::unique_ptr<SceneRenderer> _sceneRenderer;
};

inline SandboxApplication::SandboxApplication(const ApplicationDescriptor& descriptor)
    : Application(descriptor)
    , _device(nullptr)
    , _renderContext(nullptr)
    , _scene(nullptr)
    , _sceneRenderer(nullptr)
{}
