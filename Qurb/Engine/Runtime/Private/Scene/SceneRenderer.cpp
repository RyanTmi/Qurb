#include "Scene/SceneRenderer.hpp"

#include "Log/Log.hpp"
#include "Scene/Components.hpp"

namespace qurb
{
    auto SceneRenderer::render(rhi::RenderContext* renderContext) -> void
    {
        static auto renderPassDescriptor = rhi::RenderPassDescriptor {
            .clearColor = Color::black,
        };

        // Get the swap chain.
        auto swapChain    = renderContext->swapChain();
        auto renderTarget = swapChain->nextRenderTarget();

        // Geometry render pass.
        renderContext->beginRenderPass(renderTarget, renderPassDescriptor);

        // Render all renderable objects in the scene here.
        for (auto& entity : _scene.entities())
        {
            if (not entity.hasComponents<TransformComponent, MeshComponent, MaterialComponent>())
            {
                continue;
            }

            auto components = entity.getComponents<TransformComponent, MeshComponent, MaterialComponent>();

            auto [transformComponent, meshComponent, materialComponent] = components;

            renderContext->bindPipelineState(materialComponent.pipelineState);
            renderContext->pushConstants(&transformComponent.transformMatrix(), sizeof(math::Matrix4x4f));
            renderContext->bindVertexBuffer(meshComponent.vertexBuffer, 0, 0);
            renderContext->draw(meshComponent.vertexCount, 0);
        }

        renderContext->endRenderPass();
    }
}
