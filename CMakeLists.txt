cmake_minimum_required(VERSION 3.20)
project(WaterRenderer)

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
