#include <odin/graphics/vk/VulkanContext.hpp>
#include <odin/core/App.hpp>
#include <cstring>
#include <set>
#include <odin/graphics/GraphicsException.hpp>
#include <odin/core/App.hpp>
#include <odin/window/Window.hpp>

#if defined(ODIN_PLATFORM_WINDOWS)
#include <odin/window/win32/Win32Window.hpp>
#include <vulkan/vulkan_win32.h>
#endif

#include <algorithm>
#include <odin/math/Vec2.hpp>


#ifdef NDEBUG
	constexpr bool enableValidationLayers = false;
#else
	constexpr bool enableValidationLayers = false;
#endif

	VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
		VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT messageType,
		const VkDebugUtilsMessengerCallbackDataEXT* callbackData,
		void* userData)
	{
		odin::App::get().getSystemLogger()(odin::Logger::Level::Error,
			callbackData->pMessage);
		
		return VK_FALSE;
	}

	void initDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& info)
	{
		info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
		info.messageSeverity =
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
		info.messageType =
			VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT;
		info.pfnUserCallback = debugCallback;
		info.pUserData = nullptr;
	}

	const std::vector<const char*> validationLayers = {
			"VK_LAYER_KHRONOS_validation"
	};

	const std::vector<const char*> deviceExtensions = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};


namespace odin
{
	std::vector<const char*> GraphicsContext::Impl::getInstanceExtensions()
	{
		std::vector<const char*> extensions;
		extensions.push_back(VK_KHR_SURFACE_EXTENSION_NAME);
#if defined(ODIN_PLATFORM_WINDOWS)
		extensions.push_back("VK_KHR_win32_surface");
#endif
		if constexpr (enableValidationLayers)
		{
			extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
		}

		return extensions;
	}

	GraphicsContext::Impl::Impl() :
		m_window(nullptr),
		m_instance(VK_NULL_HANDLE),
		m_debugMessenger(VK_NULL_HANDLE),
		m_physicalDevice(VK_NULL_HANDLE),
		m_device(VK_NULL_HANDLE)
	{
	}

	void GraphicsContext::Impl::init()
	{
	}

	void GraphicsContext::Impl::create(Window& window, const GraphicsInfo& info)
	{
		m_window = &window;
		if (enableValidationLayers && !checkValidationLayerSupport())
		{
			throw GraphicsException("Vulkan validation layers unavailable.");
		}

		VkApplicationInfo appInfo{};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "Odin Application";
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = "Odin";
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_0;

		auto extensions = getInstanceExtensions();
		VkInstanceCreateInfo instanceInfo{};
		instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		instanceInfo.pApplicationInfo = &appInfo;
		instanceInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
		instanceInfo.ppEnabledExtensionNames = extensions.data();
		instanceInfo.enabledLayerCount = 0;
		instanceInfo.pNext = nullptr;
		VkDebugUtilsMessengerCreateInfoEXT instanceMessengerInfo{};
		/*
			Create debug messenger for instance
		*/
		if constexpr (enableValidationLayers)
		{
			instanceInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
			instanceInfo.ppEnabledLayerNames = validationLayers.data();
			initDebugMessengerCreateInfo(instanceMessengerInfo);
			instanceInfo.pNext = &instanceMessengerInfo;
		}

		if (auto result = vkCreateInstance(&instanceInfo, nullptr, &m_instance); result != VK_SUCCESS)
		{
			throw GraphicsException("Failed to create Vulkan Instance", result);
		}

		/*
			Create debug messenger
		*/
		if constexpr (enableValidationLayers)
		{
			VkDebugUtilsMessengerCreateInfoEXT messengerInfo{};
			initDebugMessengerCreateInfo(messengerInfo);
			auto createMessenger = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(m_instance, "vkCreateDebugUtilsMessengerEXT");
			if (!createMessenger)
			{
				throw GraphicsException("Debug extension not found. ", VK_ERROR_EXTENSION_NOT_PRESENT);
			}
			if (auto result = createMessenger(m_instance, &messengerInfo, nullptr, &m_debugMessenger); result != VK_SUCCESS)
			{
				throw GraphicsException("Failed to create messenger.", result);
			}
		}

		/*
			Create surface depending on the platform
		*/
#if defined(ODIN_PLATFORM_WINDOWS)
		VkWin32SurfaceCreateInfoKHR surfaceInfo{};
		surfaceInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
		surfaceInfo.hwnd = m_window->getSystemWindow()->getHandle();
		surfaceInfo.hinstance = GetModuleHandle(0);
		if (auto result = vkCreateWin32SurfaceKHR(m_instance, &surfaceInfo, nullptr, &m_surface); result != VK_SUCCESS)
		{
			throw GraphicsException("Failed to create surface.");
		}
#endif
		
		/*
			Pick physical device
		*/
		uint32_t deviceCount = 0;
		vkEnumeratePhysicalDevices(m_instance, &deviceCount, nullptr);
		if (deviceCount == 0)
		{
			throw GraphicsException("Failed to find GPUs with Vulkan support.");
		}
		std::vector<VkPhysicalDevice> physicalDevices(deviceCount);
		vkEnumeratePhysicalDevices(m_instance, &deviceCount, physicalDevices.data());

		for (const auto& device : physicalDevices)
		{
			if (isDeviceSuitable(device))
			{
				m_physicalDevice = device;
				break;
			}
		}

		if (m_physicalDevice == VK_NULL_HANDLE)
		{
			throw GraphicsException("No GPU suitable for running Odin.");
		}

		/*
			Create logical device
		*/
		vulkan::QueueFamilyIndices indices = findQueueFamilies(m_physicalDevice);
		float queuePriority = 1.f;
		std::vector<VkDeviceQueueCreateInfo> queueInfos;
		std::set<uint32_t> uniqueQueueFamilies = { indices.graphicsFamily.value(), indices.presentFamily.value() };
		for (uint32_t queueFamily : uniqueQueueFamilies)
		{
			VkDeviceQueueCreateInfo queueInfo{};
			queueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueInfo.queueFamilyIndex = queueFamily;
			queueInfo.pQueuePriorities = &queuePriority;
			queueInfo.queueCount = 1;
			queueInfos.push_back(queueInfo);
		}


		VkPhysicalDeviceFeatures deviceFeatures{};
		VkDeviceCreateInfo deviceInfo{};
		deviceInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		deviceInfo.pQueueCreateInfos = queueInfos.data();
		deviceInfo.queueCreateInfoCount = static_cast<uint32_t>(queueInfos.size());
		deviceInfo.pEnabledFeatures = &deviceFeatures;
		deviceInfo.ppEnabledExtensionNames = deviceExtensions.data();
		deviceInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
		deviceInfo.enabledLayerCount = 0;
		if constexpr (enableValidationLayers)
		{
			/*
				Prior versions of vulkan required validation layers enabled on device as well
			*/
			deviceInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
			deviceInfo.ppEnabledLayerNames = validationLayers.data();
		}

		if (auto result = vkCreateDevice(m_physicalDevice, &deviceInfo, nullptr, &m_device); result != VK_SUCCESS)
		{
			throw GraphicsException("Failed to create logical device.", result);
		}

		vkGetDeviceQueue(m_device, indices.graphicsFamily.value(), 0, &m_graphicsQueue);
		vkGetDeviceQueue(m_device, indices.presentFamily.value(), 0, &m_presentQueue);

		vulkan::SwapChainSupportDetails swapChainSupport = querySwapChainSupport(m_physicalDevice);
		auto surfaceFormat = chooseSurfaceFormat(swapChainSupport.formats);
		auto presentMode = choosePresentMode(swapChainSupport.presentModes);
		auto extent = chooseSwapExtent(swapChainSupport.capabilities);
	
		uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
		if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount)
		{
			imageCount = swapChainSupport.capabilities.maxImageCount;
		}

		VkSwapchainCreateInfoKHR swapChainInfo{};
		swapChainInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		swapChainInfo.surface = m_surface;
		swapChainInfo.minImageCount = imageCount;
		swapChainInfo.imageFormat = surfaceFormat.format;
		swapChainInfo.imageColorSpace = surfaceFormat.colorSpace;
		swapChainInfo.presentMode = presentMode;
		swapChainInfo.imageExtent = extent;
		swapChainInfo.imageArrayLayers = 1;
		swapChainInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
		
		uint32_t queueFamilyIndices[]{ indices.graphicsFamily.value(), indices.presentFamily.value() };
		if (indices.graphicsFamily.value() != indices.presentFamily.value())
		{
			swapChainInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
			swapChainInfo.queueFamilyIndexCount = 2;
			swapChainInfo.pQueueFamilyIndices = queueFamilyIndices;
		}
		else
		{
			swapChainInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
			swapChainInfo.queueFamilyIndexCount = 0;
			swapChainInfo.pQueueFamilyIndices = nullptr;
		}

		swapChainInfo.preTransform = swapChainSupport.capabilities.currentTransform;
		swapChainInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		swapChainInfo.clipped = VK_TRUE;
		swapChainInfo.oldSwapchain = VK_NULL_HANDLE;
		swapChainInfo.pNext = nullptr;
		
		if (auto result = vkCreateSwapchainKHR(m_device, &swapChainInfo, nullptr, &m_swapChain); result != VK_SUCCESS)
		{
			throw GraphicsException("Failed to create swap chain.", result);
		}

		vkGetSwapchainImagesKHR(m_device, m_swapChain, &imageCount, nullptr);
		m_swapChainImages.resize(imageCount);
		vkGetSwapchainImagesKHR(m_device, m_swapChain, &imageCount, m_swapChainImages.data());
		m_swapChainExtent = extent;
		m_swapChainImageFormat = surfaceFormat.format;

		/*
			Create swap chain image views
		*/
		m_swapChainImageViews.resize(m_swapChainImages.size());
		for (size_t i = 0; i < m_swapChainImages.size(); i++)
		{
			VkImageViewCreateInfo imageViewInfo{};
			imageViewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
			imageViewInfo.image = m_swapChainImages[i];
			imageViewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
			imageViewInfo.format = m_swapChainImageFormat;

			imageViewInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
			imageViewInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
			imageViewInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
			imageViewInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

			imageViewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			imageViewInfo.subresourceRange.baseMipLevel = 0;
			imageViewInfo.subresourceRange.levelCount = 1;
			imageViewInfo.subresourceRange.baseArrayLayer = 0;
			imageViewInfo.subresourceRange.layerCount = 1;

			if (auto result = vkCreateImageView(m_device, &imageViewInfo, nullptr, &m_swapChainImageViews[i]); result != VK_SUCCESS)
			{
				throw GraphicsException("Failed to create image view.", result);
			}
		}
	}


	vulkan::SwapChainSupportDetails GraphicsContext::Impl::querySwapChainSupport(VkPhysicalDevice device)
	{
		vulkan::SwapChainSupportDetails details;
		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, m_surface, &details.capabilities);
		uint32_t formatCount;
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, m_surface, &formatCount, nullptr);
		if (formatCount != 0)
		{
			details.formats.resize(formatCount);
			vkGetPhysicalDeviceSurfaceFormatsKHR(device, m_surface, &formatCount, details.formats.data());
		}
		uint32_t presentModeCount;
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, m_surface, &presentModeCount, nullptr);
		if (presentModeCount != 0)
		{
			details.presentModes.resize(presentModeCount);
			vkGetPhysicalDeviceSurfacePresentModesKHR(device, m_surface, &presentModeCount, details.presentModes.data());
		}
		return details;
	}


	VkSurfaceFormatKHR GraphicsContext::Impl::chooseSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
	{
		for (const auto& format : availableFormats)
		{
			if (format.format == VK_FORMAT_B8G8R8A8_SRGB && format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
			{
				return format;
			}
			return availableFormats[0];
		}
	}

	VkPresentModeKHR GraphicsContext::Impl::choosePresentMode(const std::vector<VkPresentModeKHR>& availableModes)
	{
		for (const auto& mode : availableModes)
		{
			if (mode == VK_PRESENT_MODE_MAILBOX_KHR)
			{
				return mode;
			}
		}

		return VK_PRESENT_MODE_FIFO_KHR;
	}

	VkExtent2D GraphicsContext::Impl::chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities)
	{
		if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max())
		{
			return capabilities.currentExtent;
		}

		auto size = m_window->getSize();
		VkExtent2D extent{ size.x, size.y };

		extent.width = std::max(capabilities.minImageExtent.width, std::min(capabilities.maxImageExtent.width, extent.width));
		extent.height = std::max(capabilities.minImageExtent.height, std::min(capabilities.maxImageExtent.height, extent.height));

		return extent;
	}


	vulkan::QueueFamilyIndices GraphicsContext::Impl::findQueueFamilies(VkPhysicalDevice device)
	{
		vulkan::QueueFamilyIndices indices;
		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
		std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());
		int i = 0;
		for (const auto& queueFamily : queueFamilies)
		{
			if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
			{
				indices.graphicsFamily = i;
			}
			VkBool32 presentSupport = false;
			vkGetPhysicalDeviceSurfaceSupportKHR(device, i, m_surface, &presentSupport);
			if (presentSupport)
			{
				indices.presentFamily = i;
			}
			if (indices.isComplete())
			{
				break;
			}
			i++;
		}
		return indices;
	}


	bool GraphicsContext::Impl::isDeviceSuitable(VkPhysicalDevice device)
	{
		VkPhysicalDeviceProperties properties;
		vkGetPhysicalDeviceProperties(device, &properties);
		VkPhysicalDeviceFeatures features;
		vkGetPhysicalDeviceFeatures(device, &features);
		odin::vulkan::QueueFamilyIndices indices = findQueueFamilies(device);
		bool swapChainAdequate = false;
		bool extensionsSupported = checkDeviceExtensionSupport(device);
		if (extensionsSupported)
		{
			vulkan::SwapChainSupportDetails swapChainSupport = querySwapChainSupport(device);
			swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
		}
		bool suitable = indices.isComplete() && extensionsSupported && swapChainAdequate;
		return suitable;
	}


	bool GraphicsContext::Impl::checkDeviceExtensionSupport(VkPhysicalDevice device)
	{
		uint32_t extensionCount;
		vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);
		std::vector<VkExtensionProperties> extensions(extensionCount);
		vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, extensions.data());
		std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());
		for (const auto& extension : extensions)
		{
			requiredExtensions.erase(extension.extensionName);
		}
		return requiredExtensions.empty();
	}

	bool GraphicsContext::Impl::checkValidationLayerSupport()
	{
		uint32_t layerCount;

		vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
		std::vector<VkLayerProperties> availableLayers(layerCount);
		vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

		for (const char* layerName : validationLayers)
		{
			bool layerFound = false;

			for (const auto& layerProperties : availableLayers)
			{
				if (strcmp(layerName, layerProperties.layerName) == 0)
				{
					layerFound = true;
					break;
				}
			}

			if (!layerFound)
			{
				return false;
			}
		}

		return true;
	}

	void GraphicsContext::Impl::swapBuffers()
	{

	}

	void GraphicsContext::Impl::destroy()
	{
		if constexpr (enableValidationLayers)
		{
			auto destroyMessenger = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(m_instance,
				"vkDestroyDebugUtilsMessengerEXT");
			if (!destroyMessenger)
			{
				throw GraphicsException("Extension not found.", MCIERR_EXTENSION_NOT_FOUND);
			}
			destroyMessenger(m_instance, m_debugMessenger, nullptr);
		}
		for (auto imageView : m_swapChainImageViews)
		{
			vkDestroyImageView(m_device, imageView, nullptr);
		}
		vkDestroySwapchainKHR(m_device, m_swapChain, nullptr);
		vkDestroyDevice(m_device, nullptr);
		vkDestroySurfaceKHR(m_instance, m_surface, nullptr);
		vkDestroyInstance(m_instance, nullptr);
	}
}