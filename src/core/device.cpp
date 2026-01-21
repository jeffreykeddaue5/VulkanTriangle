#include "device.hpp"
#include <algorithm>
#include <iostream>

VulkanDevice::VulkanDevice(const VulkanInstance &instance)
    : m_instance(instance) {}

VulkanDevice::~VulkanDevice() {}

void VulkanDevice::pickPhysicalDevice() {
    const auto &instance = m_instance.get();
    auto devices = instance.enumeratePhysicalDevices();
    if (devices.empty()) {
        throw std::runtime_error("failed to find gpus with Vulkan Support!");
    }
    for (const auto &device : devices) {
        if (isDeviceSuitable(device, deviceExtensions)) {
            physicalDevice = device;
            printGPUInfo(physicalDevice);
            return;
        }
    }
    throw std::runtime_error("VulkanDevice: failed to find suitable GPU");
}

bool VulkanDevice::supportsGraphicsQueue(
    const vk::raii::PhysicalDevice &device) {
    auto queueFamilies = device.getQueueFamilyProperties();
    return std::any_of(queueFamilies.begin(), queueFamilies.end(),
                       [](const vk::QueueFamilyProperties &qfp) {
                           return (qfp.queueFlags &
                                   vk::QueueFlagBits::eGraphics) !=
                                  vk::QueueFlags{};
                       });
}

bool VulkanDevice::supportsRequiredExtensions(
    const vk::raii::PhysicalDevice &device,
    const std::vector<const char *> &requiredExtensions) {

    auto available = device.enumerateDeviceExtensionProperties();

    for (const char *required : requiredExtensions) {
        bool found = false;

        for (const vk::ExtensionProperties &ext : available) {
            if (std::strcmp(ext.extensionName, required) == 0) {
                found = true;
                break;
            }
        }

        if (!found) {
            return false;
        }
    }

    return true;
}

bool VulkanDevice::isDeviceSuitable(
    const vk::raii::PhysicalDevice &device,
    const std::vector<const char *> &requiredExtensions) {
    auto props = device.getProperties();

    if (props.apiVersion < VK_API_VERSION_1_3)
        return false;

    if (!supportsGraphicsQueue(device))
        return false;

    if (!supportsRequiredExtensions(device, requiredExtensions))
        return false;

    return true;
}
void VulkanDevice::printGPUInfo(const vk::raii::PhysicalDevice &device) {
    vk::PhysicalDeviceProperties props = device.getProperties();

    std::cout << "GPU Name: " << props.deviceName << "\n";
    std::cout << "Vendor ID: " << props.vendorID << "\n";
    std::cout << "Device ID: " << props.deviceID << "\n";

    // Device type
    std::cout << "Device Type: ";
    switch (props.deviceType) {
    case vk::PhysicalDeviceType::eIntegratedGpu:
        std::cout << "Integrated GPU\n";
        break;
    case vk::PhysicalDeviceType::eDiscreteGpu:
        std::cout << "Discrete GPU\n";
        break;
    case vk::PhysicalDeviceType::eVirtualGpu:
        std::cout << "Virtual GPU\n";
        break;
    case vk::PhysicalDeviceType::eCpu:
        std::cout << "CPU\n";
        break;
    default:
        std::cout << "Other\n";
        break;
    }

    // API version
    uint32_t ver = props.apiVersion;
    std::cout << "Vulkan API Version: " << VK_VERSION_MAJOR(ver) << "."
              << VK_VERSION_MINOR(ver) << "." << VK_VERSION_PATCH(ver) << "\n";
}
void VulkanDevice::createLogicalDevice() {}
