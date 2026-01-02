#include "app.hpp"
#include <GLFW/glfw3.h>

void VulkanTriangle::run() {
    initWindow();
    mainloop();
    cleanup();
}

void VulkanTriangle::mainloop() {
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }
}

void VulkanTriangle::initWindow() {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    window =
        glfwCreateWindow(WIDTH, HEIGHT, "Vulkan Triangle", nullptr, nullptr);
}

void VulkanTriangle::cleanup() {
    glfwDestroyWindow(window);
    glfwTerminate();
}
