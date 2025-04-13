#include "Log/Log.hpp"

#include <print>

auto log(const char* message) -> void
{
    std::println("{}", message);
}
