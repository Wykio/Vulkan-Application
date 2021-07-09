#pragma once

#include <vulkan/vulkan.h>
#include <stdexcept>
#include <vector>
#include <iostream>

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

            // Get every extension of our instance
            // Get amount of supported extension
            uint32_t extensionCount = 0;
            vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
            // Store them
            std::vector<VkExtensionProperties> extensions(extensionCount);
            vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
            std::cout << "available instance extensions:\n";

            for (const auto& extension : extensions) {
                std::cout << '\t' << extension.extensionName << '\n';
            }

            // Determine the required instance extensions for GLFW
            uint32_t glfwExtensionCount = 0;
            const char** glfwExtensions;

            glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

            // Check if every GLFW extension is supported
            std::cout << "glfw extensions:\n";
            for (size_t i = 0; i < glfwExtensionCount; i++)
            {
                // Display
                std::cout << '\t' << glfwExtensions[i] << '\n';

                // Check if supported
                bool supported = false;
                for (const auto& extension : extensions) {
                    if (extension.extensionName == glfwExtensions[i])
                        supported = true;
                }
                if (supported = false)
                    throw std::runtime_error("A GLFW extention is not supported !");
            }

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