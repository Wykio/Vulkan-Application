#include "Application.h"
#include "Instance.h"

void Application::initWindow() {
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(WIDTH, HEIGHT, "Ksoss window", nullptr, nullptr);
}

void Application::initVulkan() {
    Instance::createInstance(&instance);
}

void Application::mainLoop() {
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }
}

void Application::cleanup() {
    glfwDestroyWindow(window);

    glfwTerminate();
    //After following this tutorial, you could implement automatic resource management by writing C++ classes
    //that acquire Vulkan objects in their constructorand release them in their destructor, or by providing a
    //custom deleter to either std::unique_ptr or std::shared_ptr, depending on your ownership requirements.RAII
    //is the recommended model for larger Vulkan programs, but for learning purposes it's always good to know what's 
    //going on behind the scenes.
}