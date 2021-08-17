#include "Application.h"
#include "Instance.h"
#include "ValidationLayer.h"

#include <GLFW/glfw3.h>
#include <stdexcept>
#include <iostream>


void Instance::createInstance(VkInstance* instance) {
    if (enableValidationLayers && !checkValidationLayerSupport()) {
        throw std::runtime_error("validation layers requested, but not available!");
    }

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

    if (checkRequiredExtensionsSupport() != VK_SUCCESS) {
        throw std::runtime_error("Some instance extensions are not supported!");
    }

    std::vector<const char*> extensions = getRequiredExtensions();
    createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    createInfo.ppEnabledExtensionNames = extensions.data();

    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
    // For validation layer
    if (enableValidationLayers) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();

        ValidationLayer::populateDebugMessengerCreateInfo(debugCreateInfo);
        createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
    }
    else {
        createInfo.enabledLayerCount = 0;
        createInfo.pNext = nullptr;
    }

    // Finally create the instance
    if (vkCreateInstance(&createInfo, nullptr, instance) != VK_SUCCESS) {
        throw std::runtime_error("failed to create instance!");
    }
}

std::vector<const char*> Instance::getRequiredExtensions() {
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    // Convert glfwExtensions to a vector
    std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

    if (enableValidationLayers) {
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }

    return extensions;
}

// Check if every required extensions are available (call checkGLFWextensionSupport)
VkResult Instance::checkRequiredExtensionsSupport() {
    // Get every extension of our instance
    // Get amount of supported extension
    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
    // Store them
    std::vector<VkExtensionProperties> extensions(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

    auto requiredExtensions = getRequiredExtensions();

    return checkExtensionSupport(requiredExtensions.data(), requiredExtensions.size(), extensions);
}

VkResult Instance::checkExtensionSupport(const char** extensionsToCheck, size_t extensionsToCheckCount, std::vector<VkExtensionProperties> availableExtensions) {
    // Check if every GLFW extension is supported
    std::cout << "Instance extensions:\n";
    for (size_t i = 0; i < extensionsToCheckCount; i++)
    {
        // Display
        std::cout << '\t' << extensionsToCheck[i];

        // Check if supported
        bool supported = false;
        for (const auto& extension : availableExtensions) {
            if (strcmp(extension.extensionName, extensionsToCheck[i]) == 0) {
                supported = true;
                std::cout << " --> Available\n";
            }
        }
        if (supported == false) {
            std::cout << " --> NOT Available\n";
            throw std::runtime_error("A GLFW extention is not supported !");
            return VK_ERROR_EXTENSION_NOT_PRESENT;
        }
    }
    return VK_SUCCESS;
}

bool Instance::checkValidationLayerSupport() {
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    for (const char* layerName : validationLayers) {
        bool layerFound = false;

        for (const auto& layerProperties : availableLayers) {
            if (strcmp(layerName, layerProperties.layerName) == 0) {
                layerFound = true;
                break;
            }
        }

        if (!layerFound) {
            return false;
        }
    }

    return true;
}