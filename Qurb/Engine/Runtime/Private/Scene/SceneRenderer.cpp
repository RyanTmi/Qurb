#include "Scene/SceneRenderer.hpp"

#include "Log/Log.hpp"

namespace qurb
{
    auto SceneRenderer::render(rhi::RenderContext* renderContext) -> void
    {
        static auto renderPassDescriptor = rhi::RenderPassDescriptor {
            .clearColor = Color::purple,
        };

        // Get the swap chain.
        auto swapChain    = renderContext->swapChain();
        auto renderTarget = swapChain->nextRenderTarget();

        // Geometry render pass.
        renderContext->beginRenderPass(renderTarget, renderPassDescriptor);

        // Render all renderable objects in the scene here.

        renderContext->endRenderPass();
    }
}
