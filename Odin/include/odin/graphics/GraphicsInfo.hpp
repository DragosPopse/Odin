#ifndef ODIN_GRAPHICS_INFO_HPP
#define ODIN_GRAPHICS_INFO_HPP

#include <odin/Config.hpp>

namespace odin
{
	struct OpenglInfo
	{
		int32_t minorVersion = 3;
		int32_t majorVersion = 3;
	};
	
	struct VulkanInfo
	{
		mutable std::string appName;
	};

	struct GraphicsInfo
	{
		GraphicsInfo() = default;
		OpenglInfo opengl;
		VulkanInfo vulkan;
	};
}

#endif