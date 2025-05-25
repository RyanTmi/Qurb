#pragma once

#include "CoreDefines.hpp"
#include "RHI/RenderContext.hpp"
#include "Scene/Scene.hpp"

namespace qurb
{
    class QURB_API SceneRenderer
    {
    public:
        explicit SceneRenderer(Scene& scene);

    public:
        /// \brief Renders the scene.
        /// \param renderContext The render context.
        auto render(rhi::RenderContext* renderContext) -> void;

    private:
        Scene& _scene;
    };

    inline SceneRenderer::SceneRenderer(Scene& scene)
        : _scene(scene)
    {}
}
