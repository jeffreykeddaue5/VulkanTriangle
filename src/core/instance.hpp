/* Create/destroy vulkan instance
 * Enable Validation Layers
 * Setup Debug messenger
 * Query required extensions (GLFW/SDL/etc)
 */
#pragma once
#if defined(__INTELLISENSE__) || !defined(USE_CPP20_MODULES)
#include <vulkan/vulkan_raii.hpp>
#else
import vulkan_hpp;
#endif
#define GLFW_INCLUDE_VULKAN // REQUIRED only for GLFW CreateWindowSurface.
#include <GLFW/glfw3.h>

class VulkanInstance {
    public:
        VulkanInstance(bool enableValidation);
        ~VulkanInstance();

        VkInstance get() const;

    private:
        void createInstance();
        void setupDebugMessenger();

        vk::raii::Instance instance = nullptr;
        vk::raii::Context context;
};
