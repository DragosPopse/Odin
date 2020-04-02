#include <odin/window/Window.hpp>


namespace odin
{
	Window::Window(const WindowInfo& info)
	{
		create(info);
	}

	void Window::create(const WindowInfo& info)
	{
		m_systemWindow.reset(new CurrentSystemWindow(this, info));
		m_systemWindow->setWindowClosedCallback(&defaultOnWindowClosed);
	}

	void Window::processEvents()
	{
		if (m_systemWindow != nullptr)
		{
			m_systemWindow->processEvents();
		}
	}

	bool Window::isOpen() const
	{
		return m_systemWindow != nullptr;
	}

	void Window::close()
	{
		m_systemWindow.reset();
	}

	void Window::defaultOnWindowClosed(const Event& ev)
	{
		ev.window->close();
	}
}