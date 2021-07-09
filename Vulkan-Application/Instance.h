#pragma once

#include <vulkan/vulkan.h>
#include <stdexcept>

class Instance
{
    public:
        static void createInstance(VkInstance* instance) {
            // Information about the app
            VkApplicationInfo appInfo{};
            appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
            appInfo.pApplicationName = "Hello Triangle";
            appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
            appInfo.pEngineName = "No Engine";
            appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
            appInfo.apiVersion = VK_API_VERSION_1_0;

            // Information about the instance of Vulkan
            VkInstanceCreateInfo createInfo{};
            createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
            createInfo.pApplicationInfo = &appInfo;

            // Determine the required instance extensions for GLFW
            uint32_t glfwExtensionCount = 0;
            const char** glfwExtensions;

            glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

            createInfo.enabledExtensionCount = glfwExtensionCount;
            createInfo.ppEnabledExtensionNames = glfwExtensions;

            // For validation layer
            createInfo.enabledLayerCount = 0;

            // Finally create the instance
            if (vkCreateInstance(&createInfo, nullptr, instance) != VK_SUCCESS) {
                throw std::runtime_error("failed to create instance!");
            }
        }
};