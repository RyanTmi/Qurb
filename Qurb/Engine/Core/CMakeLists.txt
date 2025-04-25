# Engine Core

add_library(EngineCore SHARED)

set(PUBLIC_HEADERS
    Public/Log/Log.hpp

    Public/Platform/Console.hpp
    Public/Platform/Detection.hpp

    Public/CoreDefines.hpp
    Public/CoreMinimal.hpp
    Public/CoreTraits.hpp
    Public/CoreTypes.hpp
)

set(PRIVATE_HEADERS
)

set(PRIVATE_SOURCES
    Private/Log/Log.cpp
)

if(APPLE)
    list(APPEND PRIVATE_HEADERS
    )
    list(APPEND PRIVATE_SOURCES
        Private/Platform/MacOS/Console.cpp
    )
endif()

target_sources(EngineCore
    PUBLIC
        ${PUBLIC_HEADERS}
    PRIVATE
        ${PRIVATE_SOURCES}
        ${PRIVATE_HEADERS}
)

target_include_directories(EngineCore
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Public
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Private
)

target_compile_definitions(EngineCore
    PRIVATE
        QURB_EXPORT
)

target_compile_options(EngineCore
    PRIVATE
        -fvisibility=hidden
)

if(APPLE)
    find_library(APPKIT_LIBRARY AppKit REQUIRED)
    find_library(COCOA_LIBRARY Cocoa REQUIRED)
    find_library(FOUNDATION_LIBRARY Foundation REQUIRED)
    find_library(METAL_LIBRARY Metal REQUIRED)
    find_library(METALKIT_LIBRARY MetalKit REQUIRED)
    find_library(QUARTZ_CORE_LIBRARY QuartzCore REQUIRED)

    target_link_libraries(EngineCore
        PUBLIC
            ${APPKIT_LIBRARY}
            ${COCOA_LIBRARY}
            ${FOUNDATION_LIBRARY}
            ${METAL_LIBRARY}
            ${METALKIT_LIBRARY}
            ${QUARTZ_CORE_LIBRARY}
    )
endif()

set_target_properties(EngineCore PROPERTIES
    OUTPUT_NAME "QurbCore"
    ARCHIVE_OUTPUT_DIRECTORY "${BIN_ROOT}"
    LIBRARY_OUTPUT_DIRECTORY "${BIN_ROOT}"
    RUNTIME_OUTPUT_DIRECTORY "${BIN_ROOT}"
)