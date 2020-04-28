#include <odin/graphics/GraphicsContext.hpp>

#if defined(ODIN_RENDERAPI_VULKAN)
#include <odin/graphics/vk/VulkanContext.hpp>
#elif defined(ODIN_RENDERAPI_OPENGL)
#include <odin/graphics/opengl/OpenglContext.hpp>
#elif defined ODIN_RENDERAPI_DIRECTX)

#endif

namespace odin
{
	GraphicsContext::GraphicsContext() :
		m_impl(new Impl())
	{
	}

	GraphicsContext::~GraphicsContext()
	{
	}

	void GraphicsContext::init()
	{
		Impl::init();
	}

	void GraphicsContext::create(Window& window, const GraphicsInfo& info)
	{
		m_impl->create(window, info);
	}

	void GraphicsContext::destroy()
	{
		m_impl->destroy();
	}

	void GraphicsContext::swapBuffers()
	{
		m_impl->swapBuffers();
	}
}