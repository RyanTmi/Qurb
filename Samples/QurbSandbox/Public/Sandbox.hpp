#pragma once

#include <Core/Application.hpp>
#include <CoreMinimal.hpp>
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
    rhi::RenderContext* _renderContext;
    Scene               _scene;
    SceneRenderer       _sceneRenderer;
};

inline SandboxApplication::SandboxApplication(const ApplicationDescriptor& descriptor)
    : Application(descriptor)
    , _renderContext(nullptr)
    , _sceneRenderer(_scene)
{}
