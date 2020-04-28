#include <odin/graphics/vk/VulkanContext.hpp>
#include <odin/core/App.hpp>
#include <cstring>
#include <odin/graphics/GraphicsException.hpp>
#include <odin/window/Window.hpp>
#include <odin/core/App.hpp>

namespace
{
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

#ifdef NDEBUG
	constexpr bool enableValidationLayers = false;
#else
	constexpr bool enableValidationLayers = true;	
#endif

}

namespace odin
{
	std::vector<const char*> VulkanContext::getInstanceExtensions()
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

	bool VulkanContext::init()
	{
		return true;
	}

	bool VulkanContext::create(Window& window, const GraphicsInfo& info)
	{
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
		instanceInfo.enabledExtensionCount = extensions.size();
		instanceInfo.ppEnabledExtensionNames = extensions.data();
		instanceInfo.enabledLayerCount = 0;
		instanceInfo.pNext = nullptr;
		VkDebugUtilsMessengerCreateInfoEXT instanceMessengerInfo{};
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



		return true;
	}

	bool VulkanContext::checkValidationLayerSupport()
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

	void VulkanContext::swapBuffers()
	{

	}

	void VulkanContext::destroy()
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

		vkDestroyInstance(m_instance, nullptr);
	}
}