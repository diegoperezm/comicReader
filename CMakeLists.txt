cmake_minimum_required(VERSION 3.20)

project(
    ComicReader
    VERSION 0.1.0
    DESCRIPTION "Comic Reader"
    LANGUAGES C
)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Executable: Compile main.c and miniz.c directly together
###############################################################################
add_executable(
    comic-reader
    src/main.c
    third_party/miniz/miniz.c
)

# --- FORCE COMPILE ALL MINIZ FILE APIS ---
# This ensures miniz doesn't drop the stdio and archive functions on AppleClang
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
) 

# Platform Libraries
###############################################################################
if(APPLE)
    find_library(COCOA_LIBRARY Cocoa REQUIRED)
    find_library(IOKIT_LIBRARY IOKit REQUIRED)
    find_library(COREVIDEO_LIBRARY CoreVideo REQUIRED)
    target_link_libraries(comic-reader PRIVATE ${COCOA_LIBRARY} ${IOKIT_LIBRARY} ${COREVIDEO_LIBRARY})
elseif(UNIX AND NOT APPLE)
    target_link_libraries(comic-reader PRIVATE m pthread dl)
endif()

set_target_properties(comic-reader PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
install(TARGETS comic-reader RUNTIME DESTINATION bin)
