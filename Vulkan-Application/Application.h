#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

class Application {
public:
    void run() {
        initWindow();
        initVulkan();
        mainLoop();
        cleanup();
    }

    // Debug tools
    static void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

private:
    GLFWwindow* window;
    VkInstance instance;
    VkDebugUtilsMessengerEXT debugMessenger;
    VkDevice device;
    VkQueue graphicsQueue;

    void initWindow();
    void initVulkan();
    void mainLoop();
    void cleanup();
        
    // Debug tools
    void setupDebugMessenger();
    void DestroyDebugMessenger();
}; 