#pragma once

#include <vulkan/vulkan.h>
#include <optional>
#include <vector>

const std::vector<const char*> deviceExtensions = {
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

struct QueueFamilyIndices {
	std::optional<uint32_t> graphicsFamily;
	std::optional<uint32_t> presentFamily;

	bool isComplete() {
		return graphicsFamily.has_value() && presentFamily.has_value();
	}
};

class Device
{
public:
	static void createLogicalDevice(VkInstance* instance, VkDevice* device, VkQueue* graphicsQueue, VkSurfaceKHR* surface, VkQueue* presentQueue);

private:
	static void pickPhysicalDevice(VkInstance* instance, VkPhysicalDevice* physicalDevice, VkSurfaceKHR* surface);
	static bool isDeviceSuitable(VkPhysicalDevice physicalDevice, VkSurfaceKHR* surface);
	static QueueFamilyIndices findQueueFamilies(VkPhysicalDevice physicalDevice, VkSurfaceKHR* surface);
	static bool checkDeviceExtensionSupport(VkPhysicalDevice physicalDevice);
};
