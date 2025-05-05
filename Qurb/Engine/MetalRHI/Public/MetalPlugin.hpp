/// \file MetalPlugin.hpp

#pragma once

#include "MetalRenderBackend.hpp"
#include "MetalRHI.hpp"

#include <RHI/RHIPlugin.hpp>

namespace qurb
{
    /// \brief The `MetalRHIPlugin` class.
    class QURB_METAL_RHI_API MetalRHIPlugin final : public RHIPlugin
    {
    public:
        explicit MetalRHIPlugin(DynamicLibrary&& library);
        ~MetalRHIPlugin() override = default;

    public:
        auto name() const -> std::string_view override;
        auto description() const -> std::string_view override;
        auto version() const -> std::string_view override;

        auto createRenderBackend() const -> RenderBackend* override;
    };

    inline MetalRHIPlugin::MetalRHIPlugin(DynamicLibrary&& library)
        : RHIPlugin(std::move(library))
    {}

    inline auto MetalRHIPlugin::name() const -> std::string_view
    {
        return "Qurb Render Hardware Interface - Metal";
    }

    inline auto MetalRHIPlugin::description() const -> std::string_view
    {
        // TODO: Need a description
        return "";
    }

    inline auto MetalRHIPlugin::version() const -> std::string_view
    {
        return "0.1";
    }

    inline auto MetalRHIPlugin::createRenderBackend() const -> RenderBackend*
    {
        return new MetalRenderBackend;
    }
}
