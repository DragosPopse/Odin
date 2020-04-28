#include <odin/graphics/opengl/OpenglContext.hpp>

#include <odin/window/Window.hpp>

#if defined(ODIN_PLATFORM_WINDOWS)
#include <odin/graphics/opengl/wgl/WglContext.hpp>
#endif


namespace odin
{
	GraphicsContext::Impl::Impl() :
		m_impl(new Impl2())
	{
	}

	GraphicsContext::Impl::~Impl()
	{
	}

	void GraphicsContext::Impl::init()
	{
		Impl2::init();
	}

	void GraphicsContext::Impl::create(Window& window, const GraphicsInfo& info)
	{
		m_impl->create(window, info);
	}

	void GraphicsContext::Impl::destroy()
	{
		m_impl->destroy();
	}

	void GraphicsContext::Impl::swapBuffers()
	{
		m_impl->swapBuffers();
	}
}