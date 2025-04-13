# Engine Core

add_library(EngineCore SHARED)

set(PUBLIC_HEADERS
    Public/Log/Log.hpp

    Public/CoreDefines.hpp
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

set_target_properties(EngineCore PROPERTIES
    OUTPUT_NAME "QurbCore"
    ARCHIVE_OUTPUT_DIRECTORY "${BIN_ROOT}"
    LIBRARY_OUTPUT_DIRECTORY "${BIN_ROOT}"
    RUNTIME_OUTPUT_DIRECTORY "${BIN_ROOT}"
)