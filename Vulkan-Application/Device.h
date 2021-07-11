#pragma once

#include <vulkan/vulkan.h>
#include <optional>

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
	static void createLogicalDevice(VkInstance* instance, VkDevice* device, VkQueue* graphicsQueue, VkSurfaceKHR* surface);

private:
	static void pickPhysicalDevice(VkInstance* instance, VkPhysicalDevice* physicalDevice, VkSurfaceKHR* surface);
	static bool isDeviceSuitable(VkPhysicalDevice physicalDevice, VkSurfaceKHR* surface);
	static QueueFamilyIndices findQueueFamilies(VkPhysicalDevice physicalDevice, VkSurfaceKHR* surface);
};
