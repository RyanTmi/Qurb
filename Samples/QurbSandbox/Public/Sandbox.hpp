#pragma once

#include <Core/Application.hpp>

using namespace qurb;

class SandboxApplication : public Application
{
public:
    SandboxApplication()           = default;
    ~SandboxApplication() override = default;

public:
    auto initialize() -> void override;
    auto shutdown() -> void override;
};
