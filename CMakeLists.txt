cmake_minimum_required(VERSION 3.20)

project(
    ComicReader
    VERSION 0.1.0
    DESCRIPTION "Comic Reader"
    LANGUAGES C
)

###############################################################################
# C Standard
###############################################################################

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

###############################################################################
# Build Type
###############################################################################

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

###############################################################################
# Compiler Warnings
###############################################################################

if(MSVC)
    add_compile_options(
        /W4
        /permissive-
    )

else()

    add_compile_options(
        -Wall
        -Wextra
        -Wpedantic
        -Wconversion
        -Wshadow
        -Wstrict-prototypes
        -Wmissing-prototypes
        -Werror=implicit-function-declaration
    )

endif()

###############################################################################
# Raylib
###############################################################################

#set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
#set(BUILD_GAMES OFF CACHE BOOL "" FORCE)
#add_subdirectory(third_party/raylib)

###############################################################################
# Miniz
###############################################################################
add_library( miniz STATIC third_party/miniz/miniz.c)

target_include_directories( miniz PUBLIC third_party/miniz)

###############################################################################
# Executable
###############################################################################

add_executable(
    comic-reader
    src/main.c
    # src/app.c
    #src/error.c
    #src/archive.c
    #src/cache.c
    #src/decoder.c
    #src/platform/filesystem.c
    #src/platform/path.c
    #src/platform/logging.c
    #src/platform/time.c
    #src/reader.c
    #src/renderer.c
    #
    # stb_image implementation
    #
    #    src/stb_image.c
)

###############################################################################
# Include Directories
###############################################################################

target_include_directories(comic-reader PRIVATE include third_party/miniz) 
#third_party/raylib/src third_party/raygui third_party/stb)


###############################################################################
# Link Libraries
###############################################################################

target_link_libraries( comic-reader PRIVATE miniz ) # raylib 

###############################################################################
# Platform Libraries
###############################################################################

if(APPLE)
    find_library(COCOA_LIBRARY Cocoa REQUIRED)
    find_library(IOKIT_LIBRARY IOKit REQUIRED)
    find_library(COREVIDEO_LIBRARY CoreVideo REQUIRED)
    target_link_libraries( comic-reader PRIVATE ${COCOA_LIBRARY} ${IOKIT_LIBRARY} ${COREVIDEO_LIBRARY})

elseif(UNIX AND NOT APPLE)
    target_link_libraries( comic-reader PRIVATE m pthread dl)
endif()

###############################################################################
# Output
###############################################################################

set_target_properties(

    comic-reader

    PROPERTIES

        RUNTIME_OUTPUT_DIRECTORY
            ${CMAKE_BINARY_DIR}/bin
)

###############################################################################
# Install
###############################################################################

install( TARGETS comic-reader RUNTIME DESTINATION bin)

# Configure (Debug)
# mkdir -p build
# cd build
# cmake -DCMAKE_BUILD_TYPE=Debug ..
# cmake --build .

# Configure (Release)
# mkdir -p build
# cd build
# cmake -DCMAKE_BUILD_TYPE=Release ..
# cmake --build .

# Run
# ./bin/comic-reader

# Clean rebuild
# cd ..
# rm -rf build
# mkdir build
# cd build
# cmake -DCMAKE_BUILD_TYPE=Release ..
# cmake --build .

# Using Ninja (recommended)
# mkdir -p build
# cd build
# cmake -G Ninja -DCMAKE_BUILD_TYPE=Release ..
# ninja
# ./bin/comic-reader
