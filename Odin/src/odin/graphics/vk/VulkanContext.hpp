#ifndef ODIN_VULKAN_CONTEXT_HPP
#define ODIN_VULKAN_CONTEXT_HPP

#include <odin/Config.hpp>
#include <vulkan/vulkan.h>
#include <odin/graphics/GraphicsContext.hpp>
#include <vector>
#include <optional>

namespace odin
{
	class Window;

	namespace vulkan
	{
		struct QueueFamilyIndices
		{
			std::optional<uint32_t> graphicsFamily;
			std::optional<uint32_t> presentFamily;

			bool isComplete() const
			{
				return graphicsFamily.has_value() &&
					presentFamily.has_value();
			}
		};

		struct SwapChainSupportDetails
		{
			VkSurfaceCapabilitiesKHR capabilities;
			std::vector<VkSurfaceFormatKHR> formats;
			std::vector<VkPresentModeKHR> presentModes;
		};
	}

	class GraphicsContext::Impl
	{
	public:
		Impl();
		~Impl() = default;

		static void init();

		void create(Window& window, const GraphicsInfo& info);
		void destroy();

		void swapBuffers();


	private:
		std::vector<const char*> getInstanceExtensions();
		bool checkValidationLayerSupport();
		bool isDeviceSuitable(VkPhysicalDevice device);
		vulkan::QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
		bool checkDeviceExtensionSupport(VkPhysicalDevice device);
		vulkan::SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

		VkSurfaceFormatKHR chooseSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
		VkPresentModeKHR choosePresentMode(const std::vector<VkPresentModeKHR>& availableModes);
		VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

	private:
		Window* m_window;

		VkInstance m_instance;
		VkDebugUtilsMessengerEXT m_debugMessenger;
		VkPhysicalDevice m_physicalDevice;
		VkDevice m_device;
		VkQueue m_graphicsQueue;
		VkQueue m_presentQueue;
		VkSurfaceKHR m_surface;
		VkSwapchainKHR m_swapChain;
		VkFormat m_swapChainImageFormat;
		VkExtent2D m_swapChainExtent;

		std::vector<VkImage> m_swapChainImages;
		std::vector<VkImageView> m_swapChainImageViews;
	};
}

#endif