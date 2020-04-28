#ifndef ODIN_GRAPHICS_CONTEXT_HPP
#define ODIN_GRAPHICS_CONTEXT_HPP

#include <odin/Config.hpp>

#if defined(ODIN_RENDERAPI_VULKAN)
	#include <odin/graphics/vk/VulkanContext.hpp>
namespace odin
{
	using GraphicsContext = VulkanContext;
}
#elif defined(ODIN_RENDERAPI_OPENGL)
	#include <odin/graphics/opengl/OpenglContext.hpp>
namespace odin
{
	using GraphicsContext = OpenglContext;
}
#endif



#endif