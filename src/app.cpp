#include "app.hpp"
#include "device.hpp"
#include "instance.hpp"
#include <GLFW/glfw3.h>

VulkanTriangle::VulkanTriangle() {};
VulkanTriangle::~VulkanTriangle() {};

void VulkanTriangle::run() {
    initWindow();
    initVulkan();
    mainloop();
    cleanup();
}

void VulkanTriangle::initVulkan() {
    vkcore::instance::init();
    vkcore::device::pickPhysicalDevice();
    vkcore::device::createLogicalDevice();
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
