# Engine Runtime

add_library(EngineRuntime SHARED)

set(PUBLIC_HEADERS
    Public/Core/Application.hpp
    Public/Core/Engine.hpp

    Public/Events/Event.hpp
    Public/Events/EventDispatcher.hpp
    Public/Events/WindowEvents.hpp

    Public/Platform/Platform.hpp
    Public/Platform/Window.hpp
    Public/Platform/MacOS/NativeWindow.hpp

    Public/Plugins/Plugin.hpp
    Public/Plugins/PluginManager.hpp

    Public/Renderer/Renderer.hpp

    Public/RHI/Buffer.hpp
    Public/RHI/Device.hpp
    Public/RHI/PipelineState.hpp
    Public/RHI/Plugin.hpp
    Public/RHI/RenderBackend.hpp
    Public/RHI/RenderContext.hpp
    Public/RHI/RenderPass.hpp
    Public/RHI/RenderTarget.hpp
    Public/RHI/ShaderProgram.hpp
    Public/RHI/SwapChain.hpp
    Public/RHI/Texture.hpp

    Public/Scene/Scene.hpp
    Public/Scene/SceneRenderer.hpp

    Public/EntryPoint.hpp
)

set(PRIVATE_HEADERS
)

set(PRIVATE_SOURCES
    Private/Core/Engine.cpp

    Private/Plugins/PluginManager.cpp

    Private/Renderer/Renderer.cpp
    Private/Renderer/Color.cpp

    Private/Scene/Scene.cpp
    Private/Scene/SceneRenderer.cpp
)

if(APPLE)
    list(APPEND PRIVATE_HEADERS
        Private/Platform/MacOS/ApplicationDelegate.hpp
        Private/Platform/MacOS/View.hpp
        Private/Platform/MacOS/WindowDelegate.hpp
    )
    list(APPEND PRIVATE_SOURCES
        Private/Platform/MacOS/ApplicationDelegate.mm
        Private/Platform/MacOS/Platform.mm
        Private/Platform/MacOS/View.mm
        Private/Platform/MacOS/Window.mm
        Private/Platform/MacOS/WindowDelegate.mm
    )
endif()

target_sources(EngineRuntime
    PUBLIC
        ${PUBLIC_HEADERS}
    PRIVATE
        ${PRIVATE_SOURCES}
        ${PRIVATE_HEADERS}
)

target_include_directories(EngineRuntime
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Public
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Private
)

target_link_libraries(EngineRuntime
    PUBLIC
        EngineCore
)

target_compile_definitions(EngineRuntime
    PRIVATE
        QURB_EXPORT
)

target_compile_options(EngineRuntime
    PRIVATE
        -fvisibility=hidden
)

set_target_properties(EngineRuntime PROPERTIES
    OUTPUT_NAME "QurbRuntime"
    ARCHIVE_OUTPUT_DIRECTORY "${BIN_ROOT}"
    LIBRARY_OUTPUT_DIRECTORY "${BIN_ROOT}"
    RUNTIME_OUTPUT_DIRECTORY "${BIN_ROOT}"
)