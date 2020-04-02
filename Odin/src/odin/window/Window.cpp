#include <odin/window/Window.hpp>


namespace odin
{
	Window::Window(const WindowInfo& info)
	{
		m_systemWindow.reset(new CurrentSystemWindow(info));
	}

	void Window::create(const WindowInfo& info)
	{
		m_systemWindow.reset(new CurrentSystemWindow(info));
	}

	bool Window::pollEvent(Event& ev)
	{
		if (m_systemWindow != nullptr)
		{
			return m_systemWindow->pollEvent(ev);
		}
		return false;
	}

	bool Window::isOpen() const
	{
		return m_systemWindow != nullptr;
	}

	void Window::close()
	{
		m_systemWindow.reset();
	}
}