#ifndef ODIN_WIN32WINDOW_HPP
#define ODIN_WIN32WINDOW_HPP

#include <odin/Config.hpp>
#include <odin/window/Window.hpp>
#include <odin/window/WindowInfo.hpp>
#include <odin/window/Event.hpp>
#include <gmath/details/vec2.hpp>


namespace odin
{
	class Window::Impl
	{
		static bool s_registerClass;
		static const wchar_t* s_className;

	public:
		Impl(Window* apiWindow);
		~Impl() = default;

		void create(const WindowInfo& info);
		void destroy();
		HWND getHandle() const;
		gm::Vec2u getSize() const;
		void processEvents();

		HDC getDC() const;
		bool isOpen() const;

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
		gm::Vec2u m_lastSize = gm::Vec2u(0u, 0u);
		HDC m_dc = 0;
		Window* m_apiWindow;
	};

}

#endif