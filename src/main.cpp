#include "vulkan/vulkan.hpp"
#include <algorithm>
#include <cstdint>
#include <cstring>
#include <ostream>
#include <stdexcept>
#include <vulkan/vulkan_core.h>
#if defined(__INTELLISENSE__) || !defined(USE_CPP20_MODULES)
#include <vulkan/vulkan_raii.hpp>
#else
import vulkan_hpp;
#endif
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <cstdlib>
#include <iostream>

constexpr uint32_t WIDTH = 800;
constexpr uint32_t HEIGHT = 600;

class HelloTriangleApplication {
    public:
        void run() {
            initWindow();
            initVulkan();
            mainLoop();
            cleanup();
        }

    private:
        GLFWwindow *window = nullptr;
        vk::raii::Context context;
        vk::raii::Instance instance = nullptr;

        void createInstance() {
            vk::ApplicationInfo appinfo;
            appinfo.pApplicationName = "Vulkan Triangle";
            appinfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
            appinfo.pEngineName = "No Engine";
            appinfo.apiVersion = vk::ApiVersion14;

            uint32_t glfwExtensionCount = 0;
            auto glfwExtensions =
                glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

            auto extensionProperties =
                context.enumerateInstanceExtensionProperties();

            // Available extensions
            std::cout << "available extensions:" << std::endl;
            for (const auto &extension : extensionProperties) {
                std::cout << '\t' << extension.extensionName << '\n';
            }

            // Checks whether vulkan supports the necessary extensions for glfw
            for (uint32_t i = 0; i < glfwExtensionCount; ++i) {
                if (!std::ranges::any_of(
                        extensionProperties,
                        [glfwExtension =
                             glfwExtensions[i]](auto const &extensionProperty) {
                            return strcmp(extensionProperty.extensionName,
                                          glfwExtension) == 0;
                        })) {
                    throw std::runtime_error(
                        "Required GLFW extension not supported: " +
                        std::string(glfwExtensions[i]));
                } else {
                    std::cout
                        << "Extension found: " << std::string(glfwExtensions[i])
                        << std::endl;
                }
            }

            vk::InstanceCreateInfo createinfo;
            createinfo.pApplicationInfo = &appinfo;
            createinfo.enabledExtensionCount = glfwExtensionCount;
            createinfo.ppEnabledExtensionNames = glfwExtensions;

            instance = vk::raii::Instance(context, createinfo);
        }

        void initVulkan() { createInstance(); }

        void initWindow() {
            glfwInit();
            glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
            glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
            window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan Triangle", nullptr,
                                      nullptr);
        }

        void mainLoop() {
            std::cout << "__cplusplus = " << __cplusplus << '\n';
            while (!glfwWindowShouldClose(window)) {
                glfwPollEvents();
            }
        }

        void cleanup() {
            glfwDestroyWindow(window);
            glfwTerminate();
        }
};

int main() {
    try {
        HelloTriangleApplication app;
        app.run();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
