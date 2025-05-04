/// \file Application.hpp

#pragma once

#include "CoreDefines.hpp"
#include "CoreTypes.hpp"

#include <memory>
#include <string>

namespace qurb
{
    /// \brief Descriptor for an application.
    struct QURB_API ApplicationDescriptor
    {
        std::string name;
    };

    /// \brief Base class for all applications.
    class QURB_API Application
    {
    public:
        explicit Application(const ApplicationDescriptor& descriptor);
        virtual ~Application() = default;

    public:
        virtual auto initialize() -> void = 0;
        virtual auto shutdown() -> void   = 0;

        virtual auto update(float32 deltaTime) -> void = 0;

    public:
        [[nodiscard]] auto descriptor() const -> const ApplicationDescriptor&;

    protected:
        ApplicationDescriptor _descriptor;
    };

    inline Application::Application(const ApplicationDescriptor& descriptor)
        : _descriptor(descriptor)
    {}

    inline auto Application::descriptor() const -> const ApplicationDescriptor&
    {
        return _descriptor;
    }
}
