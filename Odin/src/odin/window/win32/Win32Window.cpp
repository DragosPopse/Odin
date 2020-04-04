#include <odin/window/win32/Win32Window.hpp>
#include <odin/window/Event.hpp>
#include <iostream>

namespace
{
	///credits https://stackoverflow.com/questions/15966642/how-do-you-tell-lshift-apart-from-rshift-in-wm-keydown-events
	WPARAM MapLeftRightKeys(WPARAM vk, LPARAM lParam)
	{
		WPARAM new_vk = vk;
		UINT scancode = (lParam & 0x00ff0000) >> 16;
		int extended = (lParam & 0x01000000) != 0;

		switch (vk) {
		case VK_SHIFT:
			new_vk = MapVirtualKeyW(scancode, MAPVK_VSC_TO_VK_EX);
			break;
		case VK_CONTROL:
			new_vk = extended ? VK_RCONTROL : VK_LCONTROL;
			break;
		case VK_MENU:
			new_vk = extended ? VK_RMENU : VK_LMENU;
			break;
		default:
			// not a key we map from generic to left/right specialized
			//  just return it.
			new_vk = vk;
			break;
		}

		return new_vk;
	}

}

namespace odin
{

	LRESULT CALLBACK Win32Window::WindowProc(
		_In_ HWND handle,
		_In_ UINT message,
		_In_ WPARAM wparam,
		_In_ LPARAM lparam
	)
	{
		if (message == WM_CREATE)
		{
			Win32Window* window = static_cast<Win32Window*>(reinterpret_cast<CREATESTRUCTW*>(lparam)->lpCreateParams);
			SetLastError(0);
			if (!SetWindowLongPtrW(handle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window)))
			{
				if (GetLastError() != 0)
				{
					return 0;
				}
			}
			return 0;
		}

		Win32Window* window = handle ? reinterpret_cast<Win32Window*>(GetWindowLongPtrW(handle, GWLP_USERDATA)) : nullptr;

		if (window)
		{
			Event ev;
			ev.window = window->m_apiWindow;
			switch (message)
			{
			case WM_CLOSE:
				ev.type = Event::Type::WindowClosed;
				window->m_onEventCallback(ev);
				return 0;

			case WM_SYSKEYDOWN:
			case WM_KEYDOWN:
				wparam = MapLeftRightKeys(wparam, lparam);
				ev.type = Event::Type::KeyPressed;
				ev.key.code = static_cast<Keyboard::Key>(wparam);
				window->m_onEventCallback(ev);
				return 0;

			case WM_SYSKEYUP:
			case WM_KEYUP:
				wparam = MapLeftRightKeys(wparam, lparam);
				ev.type = Event::Type::KeyReleased;
				ev.key.code = static_cast<Keyboard::Key>(wparam);
				window->m_onEventCallback(ev);
				return 0;
			}
		}

		
		return DefWindowProcW(handle, message, wparam, lparam);
	}
	

	bool Win32Window::s_registerClass = true;
	const wchar_t* Win32Window::s_className = L"Odin_DefaultWindow";

	Win32Window::Win32Window(Window* apiWindow, const WindowInfo& info) :
		SystemWindow(apiWindow),
		m_window(NULL)
	{	
		//First Window
		//Register the window class
		if (s_registerClass)
		{
			WNDCLASSEXW windowClass{};
			windowClass.cbSize = sizeof(WNDCLASSEXW);
			windowClass.hInstance = GetModuleHandleW(0);
			windowClass.lpfnWndProc = &WindowProc;
			windowClass.style = CS_OWNDC;
			windowClass.lpszClassName = s_className;
			RegisterClassExW(&windowClass);
			s_registerClass = false;
		}

		m_window = CreateWindowExW(
			0,
			s_className,
			info.title.c_str(),
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT,
			info.width, info.height,
			NULL, NULL, GetModuleHandleW(0), this);

		ShowWindow(m_window, SW_SHOW);
	}

	Win32Window::~Win32Window()
	{
		DestroyWindow(m_window);
	}

	WindowHandle Win32Window::getHandle() const
	{
		return m_window;
	}

	void Win32Window::processEvents()
	{
		MSG message;
		while (PeekMessageW(&message, m_window, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&message);
			DispatchMessageW(&message);
		}
	}
}