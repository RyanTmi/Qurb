#include "Sandbox.hpp"

#include <Containers/Array.hpp>
#include <Core/Engine.hpp>
#include <EntryPoint.hpp>
#include <Math/Vector2.hpp>
#include <Math/Vector3.hpp>
#include <Scene/Components.hpp>
#include <Scene/Entity.hpp>

#include <ranges>

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
    _renderContext->window().registerEvent<WindowResizeEvent>(bind<&SandboxApplication::onWindowResize>(this));

    _scene         = std::make_unique<Scene>();
    _sceneRenderer = std::make_unique<SceneRenderer>(*_scene, _device);

    createCamera();
    createQuad();

    onWindowResize(WindowResizeEvent(_renderContext->window()));

    Log::info("{} initialized", _name);
}

auto SandboxApplication::shutdown() -> void
{
    for (auto& entity : _scene->entities())
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

    _sceneRenderer.reset();
    _scene.reset();

    _renderContext->window().unregisterEvent<WindowResizeEvent>(bind<&SandboxApplication::onWindowResize>(this));
    _renderContext->release();
    _renderContext = nullptr;

    _device->release();
    _device = nullptr;

    Log::info("{} shutdown", _name);
}

auto SandboxApplication::update(float32 deltaTime) -> void
{
    static auto time = 0.0f;
    time += deltaTime;

    for (auto& entity : _scene->entities())
    {
        if (entity.hasComponent<CameraComponent>())
        {
            continue;
        }
        auto& transformComponent = entity.getComponent<TransformComponent>();
        transformComponent.eulerAngles.z += deltaTime * 50.0f;
    }
}

auto SandboxApplication::render() -> void
{
    _renderContext->beginFrame();

    _sceneRenderer->render(_renderContext);

    _renderContext->present();
    _renderContext->endFrame();
}

auto SandboxApplication::onWindowResize(const WindowResizeEvent& event) -> bool
{
    for (auto& entity : _scene->entities())
    {
        if (entity.hasComponent<CameraComponent>())
        {
            auto&   cameraComponent = entity.getComponent<CameraComponent>();
            float32 aspectRatio     = static_cast<float32>(event.window.size().x) / static_cast<float32>(event.window.size().y);
            // auto  projection       = makeOrthographic(0.0f, event.window.size().x, 0.0f, event.window.size().y, 0.1, 1000);
            auto projection        = makePerspective(45.0f, aspectRatio, 0.1f, 1000.0f);
            cameraComponent.camera = Camera(CameraType::Perspective, projection);
            break;
        }
    }

    return false;
}

auto SandboxApplication::createQuad() -> void
{
    constexpr auto quadCount = 4;

    auto vertices  = quadVertices();
    auto positions = Array<math::Vector3f, quadCount> {
        {-1.0f, -1.0f, 1.0f},
        {1.0f,  -1.0f, 1.0f},
        {1.0f,  1.0f,  1.0f},
        {-1.0f, 1.0f,  1.0f},
    };

    for (int i = 0; i < quadCount; ++i)
    {
        _scene->createEntity();
    }

    // Because `_scene->entities()[0]` is the camera entity.
    for (int i = 0; i < quadCount; ++i)
    {
        auto& entity = _scene->entities()[i + 1];

        entity.addComponent<TagComponent>().name = std::format("Quad {}", i + 1);

        auto& transformComponent = entity.addComponent<TransformComponent>();
        auto& meshComponent      = entity.addComponent<MeshComponent>();
        auto& materialComponent  = entity.addComponent<MaterialComponent>();

        transformComponent.position = positions[i] / 2.0f;
        transformComponent.scale    = {.25f, .25f, 1.0f};

        meshComponent.vertexBuffer = _device->createBuffer(
            rhi::BufferDescriptor {
                .bufferSize  = sizeof(Vertex3d) * vertices.size(),
                .bufferType  = rhi::BufferType::Vertex,
                .bufferUsage = rhi::BufferUsage::Immutable,
                .initialData = vertices.data(),
            });
        meshComponent.vertexCount = static_cast<uint32>(vertices.size());

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
}

auto SandboxApplication::createCamera() -> void
{
    auto cameraEntity = _scene->createEntity();

    cameraEntity.addComponent<TagComponent>().name = "Camera";

    auto& transformComponent = cameraEntity.addComponent<TransformComponent>();
    auto& cameraComponent    = cameraEntity.addComponent<CameraComponent>();

    transformComponent.position = {0.0f, 0.0f, -1.5f};
}

auto qurb::createApplication() -> Application*
{
    ApplicationDescriptor descriptor = {
        .name = "Qurb Sandbox",
    };

    return new SandboxApplication(descriptor);
}
