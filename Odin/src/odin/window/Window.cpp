#include <odin/window/Window.hpp>

//#if defined(ODIN_PLATFORM_WINDOWS)
#include <odin/window/win32/Win32Window.hpp>
//#endif

namespace odin
{
	Window::Window() :
		m_impl(new Window::Impl(this))
	{
	}

	void Window::create(const WindowInfo& info)
	{
		m_impl->create(info);
	}

	void Window::processEvents()
	{
		if (m_impl->isOpen())
		{
			m_impl->processEvents();
		}
	}

	bool Window::isOpen() const
	{
		return m_impl->isOpen();
	}

	void Window::close()
	{
		m_impl->destroy();
	}

	void Window::setEventCallback(EventCallbackFn callback)
	{
		m_onEventCallback = callback;
	}

	Window::Impl* Window::getSystemWindow()
	{
		return m_impl.get();
	}

	void Window::defaultOnWindowClosed(const Event& ev)
	{
		ev.window->close();
	}

	gm::Vec2u Window::getSize() const
	{
		return m_impl->getSize();
	}

	Window::~Window()
	{
	}
}