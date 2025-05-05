# Qurb MetalRHI

add_library(MetalRHI SHARED)

set(PUBLIC_HEADERS
    Public/MetalPlugin.hpp
    Public/MetalRenderBackend.hpp
    Public/MetalRHI.hpp
)

set(PRIVATE_HEADERS
)

set(PRIVATE_SOURCES
    Private/MetalPlugin.mm
)

target_sources(MetalRHI
    PUBLIC
        ${PUBLIC_HEADERS}
    PRIVATE
        ${PRIVATE_SOURCES}
        ${PRIVATE_HEADERS}
)

target_include_directories(MetalRHI
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Public
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Private
)

target_link_libraries(MetalRHI
    PRIVATE
        EngineRuntime
)

target_compile_definitions(MetalRHI
    PRIVATE
        QURB_METAL_RHI_EXPORT
)

set_target_properties(MetalRHI PROPERTIES
    OUTPUT_NAME "QurbMetalRHI"
    ARCHIVE_OUTPUT_DIRECTORY "${BIN_ROOT}"
    LIBRARY_OUTPUT_DIRECTORY "${BIN_ROOT}"
    RUNTIME_OUTPUT_DIRECTORY "${BIN_ROOT}"
)
