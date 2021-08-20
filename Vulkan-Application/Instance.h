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
    static std::vector<const char*> getRequiredExtensions();
    static VkResult checkRequiredExtensionsSupport();
    static VkResult checkExtensionSupport(const char** extensionsToCheck, size_t extensionsToCheckCount, std::vector<VkExtensionProperties> availableExtensions);
    static bool checkValidationLayerSupport();
};