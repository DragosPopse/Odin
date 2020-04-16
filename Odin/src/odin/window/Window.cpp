#include <odin/window/Window.hpp>


namespace odin
{
	Window::Window() :
		m_systemWindow(this)
	{
	}

	void Window::create(const WindowInfo& info)
	{
		m_systemWindow.create(info);
	}

	void Window::processEvents()
	{
		if (m_systemWindow.isOpen())
		{
			m_systemWindow.processEvents();
		}
	}

	bool Window::isOpen() const
	{
		return m_systemWindow.isOpen();
	}

	void Window::close()
	{
		m_systemWindow.destroy();
	}

	void Window::defaultOnWindowClosed(const Event& ev)
	{
		ev.window->close();
	}
}