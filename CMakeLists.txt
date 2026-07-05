
cmake_minimum_required(VERSION 3.20)
project(vulkan_triangle LANGUAGES CXX)

# -------------------------
# C++ Standard
# -------------------------
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#  Export compile_commands.json for clangd / Neovim
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#  Find Vulkan and GLFW
find_package(Vulkan REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

# -------------------------
# Executable
# -------------------------
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    src/*.cpp
)

add_executable(vulkan_triangle
    ${SOURCES}
)
# -------------------------
# Include Paths
# -------------------------
target_include_directories(vulkan_triangle
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# -------------------------
# Link Libraries
# -------------------------
target_link_libraries(vulkan_triangle
    PRIVATE
        Vulkan::Vulkan
        glfw
)

