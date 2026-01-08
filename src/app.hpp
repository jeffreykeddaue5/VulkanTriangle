/* Window Creation
 * Surface Creation
 * Owns all vulkan subsystems
 * Main loop
 */
#include "core/instance.hpp"
// #include <GLFW/glfw3.h>
// #include <cstdint>
const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

class VulkanTriangle {

    public:
        VulkanTriangle();
        ~VulkanTriangle();
        void run();
        void mainloop();
        void initWindow();
        void cleanup();

    private:
        GLFWwindow *window = nullptr;
        VulkanInstance instance;
};
