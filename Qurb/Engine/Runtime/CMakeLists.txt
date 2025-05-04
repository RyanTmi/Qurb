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

    Public/Renderer/Renderer.hpp

    Public/EntryPoint.hpp
)

set(PRIVATE_HEADERS
)

set(PRIVATE_SOURCES
    Private/Core/Application.cpp
    Private/Core/Engine.cpp
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