#ifndef ODIN_VULKAN_CONTEXT_HPP
#define ODIN_VULKAN_CONTEXT_HPP

#include <odin/Config.hpp>
#include <vulkan/vulkan.h>
#include <odin/graphics/GraphicsInfo.hpp>
#include <vector>

namespace odin
{
	class Window;

	class VulkanContext
	{
	public:
		VulkanContext() = default;
		~VulkanContext() = default;

		static bool init();

		bool create(Window& window, const GraphicsInfo& info);
		void destroy();

		void swapBuffers();


	private:
		std::vector<const char*> getInstanceExtensions();
		
		bool checkValidationLayerSupport();

	private:
		Window* m_window;

		VkInstance m_instance;
		VkDebugUtilsMessengerEXT m_debugMessenger;
	};
}

#endif