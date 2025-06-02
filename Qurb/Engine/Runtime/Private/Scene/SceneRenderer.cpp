#include "Scene/SceneRenderer.hpp"

#include "Log/Log.hpp"
#include "Scene/Components.hpp"

namespace qurb
{
    auto SceneRenderer::render(rhi::RenderContext* renderContext) const -> void
    {
        static auto renderPassDescriptor = rhi::RenderPassDescriptor {
            .clearColor = Color::black,
        };

        // Get the swap chain.
        const auto swapChain    = renderContext->swapChain();
        const auto renderTarget = swapChain->nextRenderTarget();

        // Geometry render pass.
        renderContext->beginRenderPass(renderTarget, renderPassDescriptor);

        // Render all renderable objects in the scene here.
        for (auto& entity : _scene._entities)
        {
            auto& transformComponent = entity.getComponent<TransformComponent>();

            const auto& transformMatrix = transformComponent.transformMatrix();

            if (entity.hasComponent<CameraComponent>())
            {
                auto& cameraComponent = entity.getComponent<CameraComponent>();

                auto* data = _sceneConstantsBuffer->map<math::Matrix4x4f>();
                data[0]    = transformMatrix.inverse();
                data[1]    = cameraComponent.projection();
                _sceneConstantsBuffer->unmap();

                renderContext->bindVertexBuffer(_sceneConstantsBuffer, 2, 0);
            }

            if (entity.hasComponents<MeshComponent, MaterialComponent>())
            {
                auto [meshComponent, materialComponent] = entity.getComponents<MeshComponent, MaterialComponent>();

                renderContext->bindPipelineState(materialComponent.pipelineState);
                renderContext->pushConstants(&transformMatrix, sizeof(math::Matrix4x4f));
                renderContext->bindVertexBuffer(meshComponent.vertexBuffer, 0, 0);
                renderContext->bindFragmentTexture(materialComponent.texture, 0);
                renderContext->draw(meshComponent.vertexCount, 0);
            }
        }

        renderContext->endRenderPass();
    }
}
