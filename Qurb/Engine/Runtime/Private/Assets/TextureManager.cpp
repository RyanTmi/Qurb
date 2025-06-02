#include "Assets/TextureManager.hpp"

#include "Containers/Array.hpp"
#include "Debug/Ensure.hpp"
#include "Log/Log.hpp"
#include "Renderer/Renderer.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace qurb
{
    auto TextureManager::getTexture(const std::string& name) -> rhi::Texture*
    {
        if (const auto it = _textures.find(name); it != _textures.end())
        {
            return it->second;
        }

        stbi_set_flip_vertically_on_load(true);

        int32  width    = 0;
        int32  height   = 0;
        int32  channels = 0;
        uint8* data     = stbi_load(name.c_str(), &width, &height, &channels, STBI_rgb_alpha);

        ensure(data != nullptr, "Failed to load texture: {}", name);

        Log::debug("Loading texture: {}", name);
        Log::debug("Texture size: {}x{}, channels: {}", width, height, channels);

        rhi::TextureDescriptor descriptor = {
            .width  = static_cast<uint32>(width),
            .height = static_cast<uint32>(height),
            .format = rhi::TextureFormat::RGBA8Srgb,
            .data   = data,
        };

        auto texture = _renderer.device()->createTexture(descriptor);

        stbi_image_free(data);

        _textures.emplace(name, texture);
        return texture;
    }

    auto TextureManager::createDefaultTexture() -> void
    {
        constexpr auto width       = 1024;
        constexpr auto height      = 1024;
        constexpr auto textureSize = width * height * 4;

        constexpr auto cellSize = 512;
        constexpr auto white    = Array<uint8, 4> {255, 255, 255, 255};
        constexpr auto magenta  = Array<uint8, 4> {255, 0, 255, 255};

        auto defaultTextureData = Array<uint8, textureSize>();
        for (int32 y = 0; y < height; ++y)
        {
            int32 cellY = y / cellSize;
            for (int32 x = 0; x < width; ++x)
            {
                int32 cellX = x / cellSize;
                int32 idx   = (y * width + x) * 4;

                const auto& c = ((cellX + cellY) % 2) != 0 ? white : magenta;

                defaultTextureData[idx + 0] = c[0];  // R
                defaultTextureData[idx + 1] = c[1];  // G
                defaultTextureData[idx + 2] = c[2];  // B
                defaultTextureData[idx + 3] = c[3];  // A
            }
        }

        const rhi::TextureDescriptor descriptor = {
            .width  = width,
            .height = height,
            .format = rhi::TextureFormat::RGBA8Srgb,
            .data   = defaultTextureData.data(),
        };

        _defaultTexture = _renderer.device()->createTexture(descriptor);
        _textures.emplace("default", _defaultTexture);

        Log::debug("Default texture created.");
    }
}
