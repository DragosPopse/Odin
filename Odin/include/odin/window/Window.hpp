#ifndef ODIN_WINDOW_HPP
#define ODIN_WINDOW_HPP

#include <odin/Config.hpp>
#include <odin/window/Event.hpp>
#include <memory>
#include <odin/window/WindowInfo.hpp>

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
		Window(const WindowInfo& info);
		Window() = default;
		~Window() = default;

		void create(const WindowInfo& info);

		void processEvents();

		bool isOpen() const;

		void close();

	private:
		static void defaultOnWindowClosed(const Event& ev);

		std::unique_ptr<CurrentSystemWindow> m_systemWindow;
	};
}

#endif