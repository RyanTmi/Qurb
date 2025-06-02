/// \file TextureManager.hpp

#pragma once

#include "CoreDefines.hpp"
#include "RHI/Texture.hpp"

#include <ranges>
#include <string>
#include <unordered_map>

namespace qurb
{
    class Renderer;

    /// \brief The `TextureManager` class.
    class QURB_API TextureManager final
    {
    public:
        explicit TextureManager(Renderer& renderer);
        ~TextureManager();

        TextureManager(const TextureManager&)            = delete;
        TextureManager& operator=(const TextureManager&) = delete;

    public:
        auto defaultTexture() -> rhi::Texture*;

        auto getTexture(const std::string& name) -> rhi::Texture*;

    private:
        using TextureMap = std::unordered_map<std::string, rhi::Texture*>;

        auto createDefaultTexture() -> void;

    private:
        Renderer&     _renderer;
        TextureMap    _textures;
        rhi::Texture* _defaultTexture;
    };

    inline TextureManager::TextureManager(Renderer& renderer)
        : _renderer(renderer)
        , _defaultTexture(nullptr)
    {}

    inline TextureManager::~TextureManager()
    {
        for (const auto& texture : _textures | std::views::values)
        {
            texture->release();
        }
    }

    inline auto TextureManager::defaultTexture() -> rhi::Texture*
    {
        if (_defaultTexture == nullptr)
        {
            createDefaultTexture();
        }
        return _defaultTexture;
    }
}
