#ifndef ODIN_WIN32_WINDOW_H
#define ODIN_WIN32_WINDOW_H

#include <odin/Config.hpp>
#include <odin/window/Event.hpp>
#include <odin/window/SystemWindow.hpp>
#include <odin/window/WindowInfo.hpp>
#include <odin/math/Vector2.hpp>

#include <Windows.h>

#include <queue>

namespace odin
{
	class Window;

	class Win32Window : 
		public SystemWindow<Win32Window>
	{
		static bool s_registerClass;
		static const wchar_t* s_className;

	public:
		Win32Window(Window* apiWindow, EventCallbackFn eventFn, const WindowInfo& info);
		~Win32Window();

		WindowHandle getHandle() const;
		Vector2u getSize() const;

		void processEvents();
		
	private:
		static LRESULT CALLBACK WindowProc(
			_In_ HWND handle,
			_In_ UINT message,
			_In_ WPARAM wparam,
			_In_ LPARAM lparam
		);

	private:
		HWND m_window = 0;
		bool m_resizing = false;
		Vector2u m_lastSize = Vector2u(0u, 0u);
	};

}

#endif