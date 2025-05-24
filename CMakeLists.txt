cmake_minimum_required(VERSION 3.20)
project(WaterRenderer)

# Set minimum macOS version to 14.0 (Sonoma)
set(CMAKE_OSX_DEPLOYMENT_TARGET "14.0" CACHE STRING "Minimum OS X deployment version")

# Automatically detect the macOS SDK path using xcrun
execute_process(
    COMMAND xcrun --sdk macosx --show-sdk-path
    OUTPUT_VARIABLE MACOS_SDK_PATH
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Use the detected SDK path for compilation and linking
set(CMAKE_OSX_SYSROOT ${MACOS_SDK_PATH})

# Add compile and link options to use the correct SDK and deployment target
add_compile_options(
    "-isysroot" "${MACOS_SDK_PATH}"
    "-mmacosx-version-min=14.0"
)

add_link_options(
    "-isysroot" "${MACOS_SDK_PATH}"
    "-mmacosx-version-min=14.0"
)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Specify raylib location (from submodule)
add_subdirectory(lib/bgfx-cmake)
add_subdirectory(lib/glfw)

include_directories(${CMAKE_SOURCE_DIR}/lib/metal-cpp)
include_directories(${CMAKE_SOURCE_DIR}/lib/imgui)
include_directories(${CMAKE_SOURCE_DIR}/lib/imgui/backends)
include_directories(${CMAKE_SOURCE_DIR}/src/renderer)
include_directories(${CMAKE_SOURCE_DIR}/src/shaders)

# Automatically add all .cpp files in the src directory
file(GLOB SOURCES src/*.cpp src/renderer/*.cpp src/utils/*.cpp src/buffers/*.cpp src/programs/*.cpp)
file(GLOB HEADERS src/*.hpp src/renderer/*.hpp src/utils/*.hpp src/buffers/*.hpp src/buffers/*.hpp)
file(GLOB IMGUI lib/imgui/*.cpp lib/imgui/backends/imgui_impl_glfw.cpp lib/imgui/backends/imgui_impl_bgfx.cpp)

# Add source files
add_executable(WaterRenderer ${SOURCES} ${IMGUI})

# Link raylib and raygui to the project
target_link_libraries(WaterRenderer bgfx glfw bx
        "-framework Metal"
        "-framework Foundation"
        "-framework QuartzCore"
)

# Set the output directory for the executable to the "bin" folder
set_target_properties(WaterRenderer PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

