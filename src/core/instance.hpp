/* Create/destroy vulkan instance
 * Enable Validation Layers
 * Setup Debug messenger
 * Query required extensions (GLFW/SDL/etc)
 */
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

#if defined(__INTELLISENSE__) || !defined(USE_CPP20_MODULES)
#include <vulkan/vulkan_raii.hpp>
#else
import vulkan_hpp;
#endif

#define GLFW_INCLUDE_VULKAN // REQUIRED only for GLFW CreateWindowSurface.
#include <GLFW/glfw3.h>

const std::vector<char const *> validationLayers = {
    "VK_LAYER_KHRONOS_validation"};

#ifdef NDEBUG
constexpr bool enableValidationLayers = false;
#else
constexpr bool enableValidationLayers = true;
#endif

class VulkanInstance {
    public:
        VulkanInstance();
        ~VulkanInstance();

        VkInstance get() const;
        void createInstance();
        void setupDebugMessenger();

    private:
        vk::raii::Instance instance = nullptr;
        vk::raii::Context context;
        vk::raii::DebugUtilsMessengerEXT debugMessenger = nullptr;
};
