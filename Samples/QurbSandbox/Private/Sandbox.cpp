#include "Sandbox.hpp"

#include <Core/Engine.hpp>
#include <EntryPoint.hpp>
#include <Math/Vector2.hpp>
#include <Math/Vector3.hpp>
#include <Scene/Components.hpp>
#include <Scene/Entity.hpp>

using namespace qurb;

struct Vertex3d
{
    math::Vector3f position;
    math::Vector2f uv;

    static auto vertexFormat() -> rhi::BufferLayout
    {
        return rhi::BufferLayout {
            {rhi::ShaderDataType::Float3, "position"},
            {rhi::ShaderDataType::Float2, "uv"      },
        };
    }
};

auto quadVertices() -> Vector<Vertex3d>
{
    return Vector<Vertex3d> {
        {{-1.0f, -1.0f, 0.0f}, {0.0f, 0.0f}},
        {{1.0f, -1.0f, 0.0f},  {1.0f, 0.0f}},
        {{1.0f, 1.0f, 0.0f},   {1.0f, 1.0f}},
        {{-1.0f, -1.0f, 0.0f}, {0.0f, 0.0f}},
        {{1.0f, 1.0f, 0.0f},   {1.0f, 1.0f}},
        {{-1.0f, 1.0f, 0.0f},  {0.0f, 1.0f}},
    };
}

auto SandboxApplication::initialize() -> void
{
    _device = _engine->renderer().device();
    _device->retain();

    _renderContext = _engine->activeWindow().renderContext();
    _renderContext->retain();

    auto vertices = quadVertices();

    const auto entityCount = 1;
    for (int i = 0; i < entityCount; ++i)
    {
        _scene.createEntity();
    }

    for (auto& entity : _scene.entities())
    {
        auto& transformComponent = entity.addComponent<TransformComponent>();
        auto& meshComponent      = entity.addComponent<MeshComponent>();
        auto& materialComponent  = entity.addComponent<MaterialComponent>();

        Log::debug("{}", entity.hasComponents<TransformComponent, MeshComponent, MaterialComponent>());

        meshComponent.vertexBuffer = _device->createBuffer(
            rhi::BufferDescriptor {
                .bufferSize  = sizeof(Vertex3d) * vertices.size(),
                .bufferType  = rhi::BufferType::Vertex,
                .bufferUsage = rhi::BufferUsage::Immutable,
                .initialData = vertices.data(),
            });
        meshComponent.indexCount = static_cast<uint32>(vertices.size());

        rhi::ShaderProgramDescriptor shaderProgramDescriptor;
        shaderProgramDescriptor.shaderName           = "Object.Builtin";
        shaderProgramDescriptor.vertexFunctionName   = "vertex_main";
        shaderProgramDescriptor.fragmentFunctionName = "fragment_main";
        shaderProgramDescriptor.bufferLayout         = Vertex3d::vertexFormat();

        materialComponent.shaderProgram = _device->createShaderProgram(shaderProgramDescriptor);

        rhi::PipelineStateDescriptor pipelineStateDescriptor;
        pipelineStateDescriptor.shaderProgram = materialComponent.shaderProgram;

        materialComponent.pipelineState = _device->createPipelineState(pipelineStateDescriptor);
    }

    Log::info("{} initialized", _name);
}

auto SandboxApplication::shutdown() -> void
{
    for (auto& entity : _scene.entities())
    {
        if (entity.hasComponent<MaterialComponent>())
        {
            auto& materialComponent = entity.getComponent<MaterialComponent>();
            materialComponent.pipelineState->release();
            materialComponent.shaderProgram->release();
        }

        if (entity.hasComponent<MeshComponent>())
        {
            auto& meshComponent = entity.getComponent<MeshComponent>();
            meshComponent.vertexBuffer->release();
        }
    }

    _renderContext->release();
    _renderContext = nullptr;

    _device->release();
    _device = nullptr;

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
