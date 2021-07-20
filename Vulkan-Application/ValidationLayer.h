#pragma once

#include "Application.h"
#include "Instance.h"

#include <iostream>

class ValidationLayer
{
public:
    static void setupDebugMessenger(VkInstance* instance, VkDebugUtilsMessengerEXT* debugMessenger);
    static void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo); // Called when we create the instance
    static void DestroyDebugMessenger(VkInstance* instance, VkDebugUtilsMessengerEXT* debugMessenger);
private:
    static VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
    static void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);
};

