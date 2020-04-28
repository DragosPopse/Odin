#ifndef ODIN_WINDOW_HPP
#define ODIN_WINDOW_HPP

#include <odin/Config.hpp>
#include <odin/window/Event.hpp>
#include <memory>
#include <odin/window/WindowInfo.hpp>


namespace odin
{
	class Window
	{
		class Impl;

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
		

		Window();
		~Window();

		void create(const WindowInfo& info);
		void processEvents();
		bool isOpen() const;
		void close();
		void setEventCallback(EventCallbackFn callback);
		Impl* getSystemWindow();

	private:
		static void defaultOnWindowClosed(const Event& ev);

		EventCallbackFn m_onEventCallback;
		std::unique_ptr<Impl> m_impl;
	};
}

#endif