/// \file CoreDefines.hpp

#pragma once

#ifdef QURB_EXPORT
    #ifdef _MSC_VER
        #define QURB_API __declspec(dllexport)
    #else
        #define QURB_API __attribute__((visibility("default")))
    #endif
#else
    #ifdef _MSC_VER
        #define QURB_API __declspec(dllimport)
    #else
        #define QURB_API
    #endif
#endif
