#include <Log/Log.hpp>

using namespace qurb;

auto main(int argc, const char** argv) -> int
{
    Log::fatal("Test fatal message");
    Log::error("Test error message");
    Log::warn("Test warn message");
    Log::info("Test info message");
    Log::debug("Test debug message");
    Log::trace("Test trace message");
}
