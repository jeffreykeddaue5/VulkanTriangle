
cmake_minimum_required(VERSION 3.20)
project(vulkan_example LANGUAGES CXX)

# ✅ Force C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) # disable GNU extensions

# ✅ Export compile_commands.json for clangd / Neovim
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ✅ Find Vulkan and GLFW
find_package(Vulkan REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

# ✅ Add your executable
add_executable(vulkan_example
    src/app.cpp 
    src/device.cpp 
    src/instance.cpp 
    src/main.cpp 
    include/app.hpp 
    include/device.hpp 
    include/instance.hpp 
)

# ✅ Link libraries
target_link_libraries(vulkan_example
    Vulkan::Vulkan
    glfw
)
