# Qurb MetalRHI

add_library(MetalRHI SHARED)

set(PUBLIC_HEADERS
    Public/MetalBuffer.hpp
    Public/MetalDevice.hpp
    Public/MetalPipelineState.hpp
    Public/MetalPlugin.hpp
    Public/MetalRenderBackend.hpp
    Public/MetalRenderContext.hpp
    Public/MetalRenderTarget.hpp
    Public/MetalShaderProgram.hpp
    Public/MetalSwapChain.hpp
    Public/MetalTexture.hpp
    Public/MetalRHI.hpp
)

set(PRIVATE_HEADERS
)

set(PRIVATE_SOURCES
    Private/MetalBuffer.mm
    Private/MetalDevice.mm
    Private/MetalPipelineState.mm
    Private/MetalPlugin.mm
    Private/MetalRenderBackend.mm
    Private/MetalRenderContext.mm
    Private/MetalRenderTarget.mm
    Private/MetalShaderProgram.mm
    Private/MetalSwapChain.mm
    Private/MetalTexture.mm
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


target_compile_options(MetalRHI
    PRIVATE
        -fvisibility=hidden
)


set_target_properties(MetalRHI PROPERTIES
    OUTPUT_NAME "QurbMetalRHI"
    ARCHIVE_OUTPUT_DIRECTORY "${BIN_ROOT}"
    LIBRARY_OUTPUT_DIRECTORY "${BIN_ROOT}"
    RUNTIME_OUTPUT_DIRECTORY "${BIN_ROOT}"
)
