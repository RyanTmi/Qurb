/// \file Detection.hpp

#pragma once

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
    #define QURB_PLATFORM_WINDOWS
    #ifndef _WIN64
        #error "64-bit is required on Windows!"
    #endif
#elif defined(__linux__) || defined(__gnu_linux__)
    // Linux OS
    #define QURB_PLATFORM_LINUX
#elif defined(__APPLE__)
    // Apple platforms
    #define QURB_PLATFORM_APPLE
    #include <TargetConditionals.h>
    #if TARGET_IPHONE_SIMULATOR
        #define QURB_PLATFORM_IOS
        #define QURB_PLATFORM_IOS_SIMULATOR
    #elif TARGET_OS_IPHONE
        #define QURB_PLATFORM_IOS
    #elif TARGET_OS_MAC
        #define QURB_PLATFORM_MACOS
    #else
        #error "Unknown Apple platform!"
    #endif
#else
    #error "Unsupported platform!"
#endif
