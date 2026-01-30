#include "device.hpp"
#include "vulkan/vulkan.hpp"
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <iterator>
#include <ostream>

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
                std::cout << "Extension Name Found : " << ext.extensionName
                          << std::endl;
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
void VulkanDevice::createLogicalDevice() {
    // find the index of the first queue family that supports supports graphics
    std::vector<vk::QueueFamilyProperties> queueFamilyProperties =
        physicalDevice.getQueueFamilyProperties();

    auto graphicsQueueFamilyProperty =
        std::ranges::find_if(queueFamilyProperties, [](auto const &qfp) {
            return (qfp.queueFlags & vk::QueueFlagBits::eGraphics) !=
                   static_cast<vk::QueueFlags>(0);
        });
    assert(graphicsQueueFamilyProperty != queueFamilyProperties.end() &&
           "No Graphics queue family found!");

    auto graphicsIndex = static_cast<uint32_t>(std::distance(
        queueFamilyProperties.begin(), graphicsQueueFamilyProperty));
    std::cout << "Graphics Index: " << graphicsIndex << std::endl;

    // 1. Default construct the chain
    vk::StructureChain<vk::PhysicalDeviceFeatures2,
                       vk::PhysicalDeviceVulkan13Features,
                       vk::PhysicalDeviceExtendedDynamicStateFeaturesEXT>
        featureChain;

    // 2. Access and set specific features using .get<T>()
    featureChain.get<vk::PhysicalDeviceVulkan13Features>().dynamicRendering =
        true;
    featureChain.get<vk::PhysicalDeviceExtendedDynamicStateFeaturesEXT>()
        .extendedDynamicState = true;

    float queuePriority = 0.f;
    vk::DeviceQueueCreateInfo deviceQueueCreateInfo;
    deviceQueueCreateInfo.queueFamilyIndex = graphicsIndex;
    deviceQueueCreateInfo.queueCount = 1;
    deviceQueueCreateInfo.pQueuePriorities = &queuePriority;

    vk::DeviceCreateInfo deviceCreateInfo{
        .pNext = &featureChain.get<vk::PhysicalDeviceFeatures2>(),
        .queueCreateInfoCount = 1,
        .pQueueCreateInfos = &deviceQueueCreateInfo,
        .enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size()),
        .ppEnabledExtensionNames = deviceExtensions.data()};

    logicalDevice = vk::raii::Device(physicalDevice, deviceCreateInfo);
    graphicsQueue = vk::raii::Queue(logicalDevice, graphicsIndex, 0);
}
