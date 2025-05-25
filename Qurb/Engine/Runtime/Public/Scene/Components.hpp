/// \file Components.hpp

#pragma once

#include "CoreDefines.hpp"
#include "Math/Matrix4x4.hpp"
#include "Math/Vector3.hpp"
#include "RHI/Buffer.hpp"
#include "RHI/PipelineState.hpp"
#include "RHI/ShaderProgram.hpp"

namespace qurb
{
    struct QURB_API TagComponent
    {
        std::string name;

    public:
        TagComponent()                    = default;
        TagComponent(const TagComponent&) = default;
        TagComponent(TagComponent&&)      = default;
    };

    struct QURB_API TransformComponent
    {
        math::Vector3f position    = math::Vector3f::zero;
        math::Vector3f eulerAngles = math::Vector3f::zero;
        math::Vector3f scale       = math::Vector3f::one;

    public:
        TransformComponent() = default;

    public:
        [[nodiscard]] auto transformMatrix() -> const math::Matrix4x4f&;

    private:
        math::Matrix4x4f _transform;
    };

    inline auto TransformComponent::transformMatrix() -> const math::Matrix4x4f&
    {
        _transform = translationMatrix(position);
        _transform *= scaleMatrix(scale);
        _transform *= rotationMatrix(eulerAngles);
        return _transform;
    }

    struct QURB_API MeshComponent
    {
        rhi::Buffer* vertexBuffer;
        rhi::Buffer* indexBuffer;
        uint32       vertexCount;

    public:
        MeshComponent() = default;
    };

    struct QURB_API MaterialComponent
    {
        rhi::ShaderProgram* shaderProgram;
        rhi::PipelineState* pipelineState;

    public:
        MaterialComponent() = default;
    };

    struct QURB_API NativeScriptComponent

    {
        NativeScriptComponent()          = default;
        virtual ~NativeScriptComponent() = default;

    protected:
        virtual auto start() -> void                   = 0;
        virtual auto update(float32 deltaTime) -> void = 0;
        virtual auto destroy() -> void                 = 0;
    };
}
