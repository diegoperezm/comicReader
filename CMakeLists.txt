cmake_minimum_required(VERSION 3.20)

project( ComicReader VERSION 0.1.0 DESCRIPTION "Comic Reader" LANGUAGES C)

# Compiler Settings
###############################################################################

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Third-Party Libraries
###############################################################################

# raylib
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)

add_subdirectory(third_party/raylib)

# Executable
###############################################################################

add_executable(
    comic-reader
    # Application
    src/main.c
    src/third_party_impl.c
    # Third-party sources
    third_party/miniz/miniz.c
)

# Compile Definitions
###############################################################################

target_compile_definitions(
    comic-reader
    PRIVATE
        MINIZ_USE_STDIO
        _DARWIN_C_SOURCE
)

# Include Directories
###############################################################################

target_include_directories(
    comic-reader
    PRIVATE
        include
        third_party/miniz
        third_party/raygui
)

# Link Libraries
###############################################################################

target_link_libraries(
    comic-reader
    PRIVATE
        raylib
)

# Output
###############################################################################

set_target_properties(
    comic-reader
    PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Installation
###############################################################################

install(
    TARGETS comic-reader
    RUNTIME DESTINATION bin
)


# cmake -S . -B build
# cmake --build build
