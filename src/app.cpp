#include "app.hpp"
#include <GLFW/glfw3.h>

VulkanTriangle::VulkanTriangle()
    : m_instance{},
      m_device(m_instance) {
    initVulkan();
};

VulkanTriangle::~VulkanTriangle() {};

void VulkanTriangle::run() {
    initWindow();
    mainloop();
    cleanup();
}

void VulkanTriangle::initVulkan() {
    m_instance.init();
    m_device.pickPhysicalDevice();
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
