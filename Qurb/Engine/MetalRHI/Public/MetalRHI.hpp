/// \file MetalRHI.hpp

#pragma once

#ifdef QURB_METAL_RHI_EXPORT
    #define QURB_METAL_RHI_API __attribute__((visibility("default")))
#else
    #define QURB_METAL_RHI_API
#endif
