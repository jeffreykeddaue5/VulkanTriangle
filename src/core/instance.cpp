#include "instance.hpp"
#include <vulkan/vulkan_structs.hpp>

VulkanInstance::VulkanInstance(bool enableValidation) {}

VulkanInstance::~VulkanInstance() {}

void VulkanInstance::createInstance() {
    constexpr vk::ApplicationInfo appInfo{
        "Vulkan Triangle",        VK_MAKE_VERSION(1, 0, 0), "No Engine",
        VK_MAKE_VERSION(1, 0, 0), vk::ApiVersion13,
    };

    // Get the required instance extensions from GLFW.
    uint32_t glfwExtensionCount = 0;
    auto glfwExtensions =
        glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    // Check if the required GLFW extensions are supported by the Vulkan
    // implementation.
    auto extensionProperties = context.enumerateInstanceExtensionProperties();
    for (uint32_t i = 0; i < glfwExtensionCount; ++i) {
        if (std::ranges::none_of(
                extensionProperties, [glfwExtension = glfwExtensions[i]](
                                         auto const &extensionProperty) {
                    return strcmp(extensionProperty.extensionName,
                                  glfwExtension) == 0;
                })) {
            throw std::runtime_error("Required GLFW extension not supported: " +
                                     std::string(glfwExtensions[i]));
        }
    }
    vk::InstanceCreateInfo createInfo{};
    createInfo.setPApplicationInfo(&appInfo);
    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;
    instance = vk::raii::Instance(context, createInfo);
}

void VulkanInstance::setupDebugMessenger() {}
