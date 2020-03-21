#ifndef ODIN_WINDOW_HPP
#define ODIN_WINDOW_HPP

#include <odin/Config.hpp>
#include <odin/window/Event.hpp>
#include <memory>

#if defined(ODIN_PLATFORM_WINDOWS)
#include <odin/window/win32/Win32Window.hpp>
namespace odin
{
	using CurrentSystemWindow = Win32Window;
}
#endif

namespace odin
{
	class Window
	{

	public:
		ODIN_API Window(uint32_t width, uint32_t height);
		ODIN_API Window() = default;
		ODIN_API ~Window() = default;

		bool ODIN_API pollEvent(Event& ev);

		bool ODIN_API isOpen() const;

		void ODIN_API close();

	private:
		std::unique_ptr<CurrentSystemWindow> m_systemWindow;
	};
}

#endif