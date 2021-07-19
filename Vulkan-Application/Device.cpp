#include "Device.h"
#include "Instance.h"

#include <stdexcept>
#include <set>


void Device::createLogicalDevice(VkInstance* instance, VkDevice* device, VkQueue* graphicsQueue, VkSurfaceKHR* surface, VkQueue* presentQueue) {
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

	pickPhysicalDevice(instance, &physicalDevice, surface);

	QueueFamilyIndices indices = findQueueFamilies(physicalDevice, surface);
	
	// Simplify the Queue creation
	std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
	// SET -> If the queue families are the same, then we only need to pass its index once.
	std::set<uint32_t> uniqueQueueFamilies = { indices.graphicsFamily.value(), indices.presentFamily.value() };

	// Create Queues for each family type
	float queuePriority = 1.0f;
	for (uint32_t queueFamily : uniqueQueueFamilies) {
		VkDeviceQueueCreateInfo queueCreateInfo{};
		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo.queueFamilyIndex = queueFamily;
		queueCreateInfo.queueCount = 1;
		queueCreateInfo.pQueuePriorities = &queuePriority;
		queueCreateInfos.push_back(queueCreateInfo);
	}

	//VkDeviceQueueCreateInfo queueCreateInfo{};
	//queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	//queueCreateInfo.queueFamilyIndex = indices.graphicsFamily.value();
	//queueCreateInfo.queueCount = 1;

	//queueCreateInfo.pQueuePriorities = &queuePriority;	

	VkPhysicalDeviceFeatures deviceFeatures{}; // if we need features by default -> VK_FALSE

	VkDeviceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());;
	createInfo.pQueueCreateInfos = queueCreateInfos.data();

	createInfo.pEnabledFeatures = &deviceFeatures;
	createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
	createInfo.ppEnabledExtensionNames = deviceExtensions.data();

	// Previous implementations of Vulkan made a distinction between instance and device specific validation layers, but this is no longer the case. That means that the enabledLayerCount and ppEnabledLayerNames fields of VkDeviceCreateInfo are ignored by up-to-date implementations. However, it is still a good idea to set them anyway to be compatible with older implementations:

	if (enableValidationLayers) {
		createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
		createInfo.ppEnabledLayerNames = validationLayers.data();
	}
	else {
		createInfo.enabledLayerCount = 0;
	}

	if (vkCreateDevice(physicalDevice, &createInfo, nullptr, device) != VK_SUCCESS) {
		throw std::runtime_error("failed to create logical device!");
	}

	// If the logical device is created we can retrieve queue handles
	vkGetDeviceQueue(*device, indices.graphicsFamily.value(), 0, graphicsQueue);
	vkGetDeviceQueue(*device, indices.presentFamily.value(), 0, presentQueue);
}

void Device::pickPhysicalDevice(VkInstance* instance, VkPhysicalDevice* physicalDevice, VkSurfaceKHR* surface) {
	// Count available devices
	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(*instance, &deviceCount, nullptr);

	if (deviceCount == 0) {
		throw std::runtime_error("failed to find GPUs with Vulkan support!");
	}
	// List all of them
	std::vector<VkPhysicalDevice> devices(deviceCount);
	vkEnumeratePhysicalDevices(*instance, &deviceCount, devices.data());

	for (const auto& device : devices) {
		if (isDeviceSuitable(device, surface)) {
			*physicalDevice = device;
			break;
		}
	}

	if (physicalDevice == VK_NULL_HANDLE) {
		throw std::runtime_error("failed to find a suitable GPU!");
	}
}

bool Device::isDeviceSuitable(VkPhysicalDevice physicalDevice, VkSurfaceKHR* surface) {
	QueueFamilyIndices indices = findQueueFamilies(physicalDevice, surface);

	bool extensionsSupported = checkDeviceExtensionSupport(physicalDevice);

	return indices.isComplete() && extensionsSupported;
}

QueueFamilyIndices Device::findQueueFamilies(VkPhysicalDevice physicalDevice, VkSurfaceKHR* surface) {
	QueueFamilyIndices indices;
	// Logic to find queue family indices to populate struct with

	uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);

	std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilies.data());

	// Check if there is a VK_QUEUE_GRAPHICS_BIT queue is the device
	int i = 0;
	for (const auto& queueFamily : queueFamilies) {
		// 
		if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
			indices.graphicsFamily = i;
		}
		VkBool32 presentSupport = false;
		vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, i, *surface, &presentSupport);
		if (presentSupport) {
			indices.presentFamily = i;
		}
		if (indices.isComplete()) {
			break;
		}
		i++;
	}

	return indices;
}

bool Device::checkDeviceExtensionSupport(VkPhysicalDevice physicalDevice) {
	uint32_t extensionCount;
	vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, nullptr);

	std::vector<VkExtensionProperties> availableExtensions(extensionCount);
	vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, availableExtensions.data());

	std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

	for (const auto& extension : availableExtensions) {
		requiredExtensions.erase(extension.extensionName);
	}

	return requiredExtensions.empty();
}