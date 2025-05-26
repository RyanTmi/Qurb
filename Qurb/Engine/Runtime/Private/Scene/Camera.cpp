#include "Scene/Camera.hpp"

namespace qurb
{
    auto makeOrthographic(float32 left, float32 right, float32 bottom, float32 top, float32 near, float32 far) -> math::Matrix4x4f
    {
        math::Matrix4x4f result = math::Matrix4x4f::identity;

        result[0, 0] = 2.0f / (right - left);
        result[0, 3] = (left + right) / (left - right);
        result[1, 1] = 2.0f / (top - bottom);
        result[1, 3] = (bottom + top) / (bottom - top);
        result[2, 2] = 1.0f / (far - near);
        result[2, 3] = near / (near - far);
        result[3, 3] = 1.0f;

        return result;
    }

    auto makePerspective(float32 fov, float32 aspect, float32 near, float32 far) -> math::Matrix4x4f
    {
        const auto y = 1.0f / std::tan(fov * 0.5);
        const auto x = y / aspect;
        const auto z = far / (far - near);

        math::Matrix4x4f result;
        result[0, 0] = x;
        result[1, 1] = y;
        result[2, 2] = z;
        result[2, 3] = -near * z;
        result[3, 2] = 1.0f;
        return result;
    }
}
