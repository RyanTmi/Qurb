# Qurb Engine

add_subdirectory(Core)
add_subdirectory(Runtime)

if(APPLE)
    add_subdirectory(MetalRHI)
endif()
