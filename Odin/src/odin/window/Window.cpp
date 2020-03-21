#include <odin/window/Window.hpp>


namespace odin
{
	Window::Window(uint32_t width, uint32_t height)
	{
		m_systemWindow.reset(new CurrentSystemWindow(width, height));
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