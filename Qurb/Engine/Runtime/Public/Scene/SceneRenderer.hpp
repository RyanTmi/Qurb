/// \file SceneRenderer.hpp

#pragma once

#include "CoreDefines.hpp"
#include "Math/Matrix4x4.hpp"
#include "RHI/Buffer.hpp"
#include "RHI/Device.hpp"
#include "RHI/RenderContext.hpp"
#include "Scene/Scene.hpp"

namespace qurb
{
    /// \brief The `SceneRenderer` class.
    class QURB_API SceneRenderer
    {
    public:
        SceneRenderer(Scene& scene, rhi::Device* device);
        ~SceneRenderer();

    public:
        /// \brief Renders the scene.
        /// \param renderContext The render context.
        auto render(rhi::RenderContext* renderContext) const -> void;

    private:
        Scene&       _scene;
        rhi::Device* _device;
        rhi::Buffer* _sceneConstantsBuffer;
    };

    inline SceneRenderer::SceneRenderer(Scene& scene, rhi::Device* device)
        : _scene(scene)
        , _device(device)
        , _sceneConstantsBuffer(nullptr)
    {
        _device->retain();
        _sceneConstantsBuffer = _device->createBuffer(
            rhi::BufferDescriptor {
                .initialData = nullptr,
                .bufferSize  = 2 * sizeof(math::Matrix4x4f),
                .bufferType  = rhi::BufferType::Vertex,
                .bufferUsage = rhi::BufferUsage::Dynamic,
            });
    }

    inline SceneRenderer::~SceneRenderer()
    {
        _device->release();
        _sceneConstantsBuffer->release();
    }
}
