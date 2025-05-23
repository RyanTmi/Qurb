/// \file MetalPlugin.hpp

#pragma once

#include "MetalRenderBackend.hpp"
#include "MetalRHI.hpp"

#include <RHI/Plugin.hpp>

namespace qurb::rhi::metal
{
    /// \brief The `Plugin` class.
    class QURB_METAL_RHI_API Plugin final : public rhi::Plugin
    {
    public:
        using base = rhi::Plugin;

    public:
        explicit Plugin(DynamicLibrary&& library);
        ~Plugin() override = default;

    public:
        auto name() const -> std::string_view override;
        auto description() const -> std::string_view override;
        auto version() const -> std::string_view override;

        auto createRenderBackend() const -> rhi::RenderBackend* override;
    };

    inline Plugin::Plugin(DynamicLibrary&& library)
        : base(std::move(library))
    {}

    inline auto Plugin::name() const -> std::string_view
    {
        return "Qurb Render Hardware Interface - Metal";
    }

    inline auto Plugin::description() const -> std::string_view
    {
        // TODO: Need a description
        return "";
    }

    inline auto Plugin::version() const -> std::string_view
    {
        return "0.1";
    }

    inline auto Plugin::createRenderBackend() const -> rhi::RenderBackend*
    {
        return new RenderBackend();
    }
}
