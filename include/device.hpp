/* Pick VkPhysicalDevice
 * Create VkDevice
 * Retrieves queues
 */
#pragma once

#include <vector>
#include <vulkan/vulkan_raii.hpp>

namespace vkcore::device {

void pickPhysicalDevice();
void createLogicalDevice();

bool supportsGraphicsQueue(const vk::raii::PhysicalDevice &device);
bool supportsRequiredExtensions(
    const vk::raii::PhysicalDevice &device,
    const std::vector<const char *> &requiredExtensions);
bool isDeviceSuitable(const vk::raii::PhysicalDevice &device,
                      const std::vector<const char *> &requiredExtensions);
void printGPUInfo(const vk::raii::PhysicalDevice &device);

} // namespace vkcore::device
