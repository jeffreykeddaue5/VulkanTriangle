/* Pick VkPhysicalDevice
 * Create VkDevice
 * Retrieves queues
 */
#pragma once
#include "instance.hpp"
#include <vulkan/vulkan_raii.hpp>

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
};
