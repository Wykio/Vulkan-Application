#pragma once

#include <vulkan/vulkan.h>
#include <vector>

const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

class Instance
{
    public:
        static void createInstance(VkInstance* instance);

    private:
        static void checkGLFWextensionSupport(const char** glfwExtensions, uint32_t glfwExtensionCount, std::vector<VkExtensionProperties> extensions);
        static bool checkValidationLayerSupport();
};