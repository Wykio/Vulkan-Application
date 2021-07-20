#include "Application.h"
#include "Instance.h"
#include "Device.h"
#include "Presentation.h"
#include "ValidationLayer.h"

#include <iostream>

void Application::initWindow() {
    // Using GLFW for
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(WIDTH, HEIGHT, "Ksoss window", nullptr, nullptr);
}

void Application::initVulkan() {
    Instance::createInstance(&instance);
    ValidationLayer::setupDebugMessenger(&instance, &debugMessenger); // need to put this in a class
    Presentation::createSurface(&instance, window, &surface);
    //Device::pickPhysicalDevice(&instance);
    Device::createLogicalDevice(&instance, &device, &graphicsQueue, &surface, &presentQueue);
}

void Application::mainLoop() {
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }
}

void Application::cleanup() {
    vkDestroyDevice(device, nullptr);
    vkDestroySurfaceKHR(instance, surface, nullptr);
    ValidationLayer::DestroyDebugMessenger(&instance, &debugMessenger);
    vkDestroyInstance(instance, nullptr);
    glfwDestroyWindow(window);
    glfwTerminate();
    //After following this tutorial, you could implement automatic resource management by writing C++ classes
    //that acquire Vulkan objects in their constructorand release them in their destructor, or by providing a
    //custom deleter to either std::unique_ptr or std::shared_ptr, depending on your ownership requirements.RAII
    //is the recommended model for larger Vulkan programs, but for learning purposes it's always good to know what's 
    //going on behind the scenes.
}