#include "Sandbox.hpp"

#include <CoreMinimal.hpp>
#include <EntryPoint.hpp>

using namespace qurb;

auto SandboxApplication::initialize() -> void
{
    Log::info("{} initialized", _descriptor.name);
}

auto SandboxApplication::shutdown() -> void {}

auto qurb::createApplication() -> Application*
{
    ApplicationDescriptor descriptor = {
        .name = "Qurb Sandbox",
    };

    return new SandboxApplication(descriptor);
}
