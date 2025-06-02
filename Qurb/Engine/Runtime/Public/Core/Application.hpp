/// \file Application.hpp

#pragma once

#include "CoreDefines.hpp"
#include "CoreTypes.hpp"

#include <string>

namespace qurb
{
    class Engine;

    /// \brief Descriptor for an application.
    struct QURB_API ApplicationDescriptor
    {
        std::string name;
    };

    /// \brief Base class for all applications.
    class QURB_API Application
    {
        friend class Engine;

    public:
        explicit Application(const ApplicationDescriptor& descriptor);
        virtual ~Application() = default;

    public:
        virtual auto initialize() -> void = 0;
        virtual auto shutdown() -> void   = 0;

        virtual auto update(float32 deltaTime) -> void = 0;
        virtual auto render() -> void                  = 0;

    public:
        [[nodiscard]] auto name() const -> const std::string&;

    protected:
        std::string _name;
        Engine*     _engine;
    };

    inline Application::Application(const ApplicationDescriptor& descriptor)
        : _name(descriptor.name)
    {}

    inline auto Application::name() const -> const std::string&
    {
        return _name;
    }
}
