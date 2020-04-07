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
#if defined(ODIN_PLATFORM_WINDOWS)
		enum class Style
		{
			None = WS_OVERLAPPED,
			Overlapped = WS_OVERLAPPEDWINDOW,
			CloseButton = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
			Resize = WS_OVERLAPPED | WS_CAPTION | WS_THICKFRAME,
			MaximizeButton = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MAXIMIZEBOX,
			MinimizeButton = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX
		};
#endif
		

		Window(const WindowInfo& info);
		Window() = default;
		~Window() = default;

		void create(const WindowInfo& info);

		void processEvents();

		bool isOpen() const;

		void close();

		void setEventCallback(EventCallbackFn callback)
		{
			m_eventCallback = callback;
		}

	private:
		static void defaultOnWindowClosed(const Event& ev);

		std::unique_ptr<CurrentSystemWindow> m_systemWindow;
		EventCallbackFn m_eventCallback;
	};
}

#endif