cmake_minimum_required(VERSION 3.16)
project(vulkan_example LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Vulkan REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

add_executable(vulkan_example
    src/main.cpp
    src/app.cpp
    src/app.hpp
    src/core/instance.cpp
)

target_link_libraries(vulkan_example
    Vulkan::Vulkan
    glfw
)

