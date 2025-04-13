# Samples QurbSandbox

add_executable(QurbSandbox)

set(PUBLIC_HEADERS
    Public/Sandbox.hpp
)

set(PRIVATE_SOURCES
    Private/Sandbox.cpp
)

target_sources(QurbSandbox
    PUBLIC
        ${PUBLIC_HEADERS}
    PRIVATE
        ${PRIVATE_SOURCES}
)

target_link_libraries(QurbSandbox
    PRIVATE
        EngineCore
)

set_target_properties(QurbSandbox PROPERTIES
    OUTPUT_NAME "QurbSandbox"
    ARCHIVE_OUTPUT_DIRECTORY "${BIN_ROOT}"
    LIBRARY_OUTPUT_DIRECTORY "${BIN_ROOT}"
    RUNTIME_OUTPUT_DIRECTORY "${BIN_ROOT}"
)
