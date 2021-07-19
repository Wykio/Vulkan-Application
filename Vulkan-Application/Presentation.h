#pragma once

#include "Application.h"

#include <vulkan/vulkan.h>
#include <stdexcept>

class Presentation
{
public:
	static void createSurface(VkInstance* instance, GLFWwindow* window, VkSurfaceKHR* surface) {
        // GLFW deals with the platform for us
        if (glfwCreateWindowSurface(*instance, window, nullptr, surface) != VK_SUCCESS) {
            throw std::runtime_error("failed to create window surface!");
        }
    }

private:

};