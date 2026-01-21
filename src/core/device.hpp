/* Pick VkPhysicalDevice
 * Create VkDevice
 * Retrieves queues
 */
#pragma once
#include "instance.hpp"
#include <vector>

class VulkanDevice {
    public:
        VulkanDevice(const VulkanInstance &instance);
        ~VulkanDevice();
        void pickPhysicalDevice();
        void createLogicalDevice();

    private:
        const VulkanInstance &m_instance;
        vk::raii::PhysicalDevice physicalDevice = nullptr;
        vk::raii::Device logicalDevice = nullptr;

        bool supportsGraphicsQueue(const vk::raii::PhysicalDevice &device);
        bool supportsRequiredExtensions(
            const vk::raii::PhysicalDevice &device,
            const std::vector<const char *> &requiredExtensions);
        bool
        isDeviceSuitable(const vk::raii::PhysicalDevice &device,
                         const std::vector<const char *> &requiredExtensions);

        void printGPUInfo(const vk::raii::PhysicalDevice &device);
        std::vector<const char *> deviceExtensions = {
            vk::KHRSwapchainExtensionName, vk::KHRSpirv14ExtensionName,
            vk::KHRSynchronization2ExtensionName,
            vk::KHRCreateRenderpass2ExtensionName};
};
