#include "Sandbox.hpp"

#include <CoreMinimal.hpp>
#include <EntryPoint.hpp>

using namespace qurb;

auto qurb::createApplication() -> Application*
{
    return new SandboxApplication();
}

auto SandboxApplication::initialize() -> void
{
    Log::info("SandboxApplication initialize");
}

auto SandboxApplication::shutdown() -> void
{
    Log::info("SandboxApplication shutdown");
}
