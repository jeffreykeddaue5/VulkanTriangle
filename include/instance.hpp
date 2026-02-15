/* Create/destroy vulkan instance
 * Enable Validation Layers
 * Setup Debug messenger
 * Query required extensions (GLFW/SDL/etc)
 */
#pragma once

#include <cstdlib>
#include <cstring>
#include <vector>

#if defined(__INTELLISENSE__) || !defined(USE_CPP20_MODULES)
#define VULKAN_HPP_NO_STRUCT_CONSTRUCTORS
#include <vulkan/vulkan_raii.hpp>
#else
import vulkan_hpp;
#endif

#define GLFW_INCLUDE_VULKAN // REQUIRED only for GLFW CreateWindowSurface.
#include <GLFW/glfw3.h>

#ifdef NDEBUG
constexpr bool enableValidationLayers = false;
#else
constexpr bool enableValidationLayers = true;
#endif

const std::vector<char const *> validationLayers = {
    "VK_LAYER_KHRONOS_validation"};

namespace vkcore::instance {

void init();
void createInstance();
void setupDebugMessenger();
vk::raii::Instance &get();

std::vector<const char *> getRequiredExtensions();

static VKAPI_ATTR vk::Bool32 VKAPI_CALL debugCallback(
    vk::DebugUtilsMessageSeverityFlagBitsEXT severity,
    vk::DebugUtilsMessageTypeFlagsEXT type,
    const vk::DebugUtilsMessengerCallbackDataEXT *pCallbackData, void *);

} // namespace vkcore::instance
