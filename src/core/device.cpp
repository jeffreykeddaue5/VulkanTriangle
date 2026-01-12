#include "device.hpp"
#include <stdexcept>

VulkanDevice::VulkanDevice(const VulkanInstance &instance)
    : m_instance(instance) {}

VulkanDevice::~VulkanDevice() {}

void VulkanDevice::pickPhysicalDevice() {
    const auto &instance = m_instance.get();
    auto devices = instance.enumeratePhysicalDevices();
    if (devices.empty()) {
        throw std::runtime_error("failed to find gpus with Vulkan Support!");
    }
    std::cout << "LogVulkanDevice: devices have been enumerated" << std::endl;
}

void VulkanDevice::createLogicalDevice() {}
