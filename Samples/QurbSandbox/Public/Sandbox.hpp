#pragma once

#include <Core/Application.hpp>

using namespace qurb;

class SandboxApplication : public Application
{
public:
    explicit SandboxApplication(const ApplicationDescriptor& descriptor);
    ~SandboxApplication() override = default;

public:
    auto initialize() -> void override;
    auto shutdown() -> void override;

    auto update(float32 deltaTime) -> void override;
};

inline SandboxApplication::SandboxApplication(const ApplicationDescriptor& descriptor)
    : Application(descriptor)
{}
