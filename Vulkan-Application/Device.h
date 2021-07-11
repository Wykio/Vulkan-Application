#pragma once

#include <vulkan/vulkan.h>
#include <optional>

struct QueueFamilyIndices {
	std::optional<uint32_t> graphicsFamily;

	bool isComplete() {
		return graphicsFamily.has_value();
	}
};

class Device
{
public:
	static void createLogicalDevice(VkInstance* instance, VkDevice* device, VkQueue* graphicsQueue);

private:
	static void pickPhysicalDevice(VkInstance* instance, VkPhysicalDevice* physicalDevice);
	static bool isDeviceSuitable(VkPhysicalDevice physicalDevice);
	static QueueFamilyIndices findQueueFamilies(VkPhysicalDevice physicalDevice);
};
