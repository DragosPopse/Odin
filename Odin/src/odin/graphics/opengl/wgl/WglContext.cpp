#include <odin/graphics/opengl/wgl/WglContext.hpp>
#include <Windows.h>
#include <glad/glad.h>
#include <glad/glad_wgl.h>
#include <odin/window/Window.hpp>
#include <iostream>

namespace odin
{
	void* WglContext::getFunction(const char* name)
	{
		void* p = (void*)wglGetProcAddress(name);
		if (p == 0 ||
			(p == (void*)0x1) || (p == (void*)0x2) || (p == (void*)0x3) ||
			(p == (void*)-1))
		{
			HMODULE module = LoadLibraryA("opengl32.dll"); //possibly optimize?
			p = (void*)GetProcAddress(module, name);
		}

		return p;
	}

	bool WglContext::init()
	{
		WNDCLASSW dummyWinClass{};
		dummyWinClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		dummyWinClass.lpfnWndProc = DefWindowProcW;
		dummyWinClass.hInstance = GetModuleHandleW(0);
		dummyWinClass.lpszClassName = L"odin_Dummy";

		if (!RegisterClassW(&dummyWinClass))
		{
			std::cout << "Failed to register dummy class.\n";
			return false;
		}

		HWND dummyWindow = CreateWindowExW(
			0,
			dummyWinClass.lpszClassName,
			L"Dummy Window",
			0,
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
			0, 0,
			dummyWinClass.hInstance,
			0
		);

		HDC dummyDc = GetDC(dummyWindow);
		PIXELFORMATDESCRIPTOR pfd{};
		pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pfd.nVersion = 1;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		pfd.cColorBits = 32;
		pfd.cAlphaBits = 8;
		pfd.iLayerType = PFD_MAIN_PLANE;
		pfd.cDepthBits = 24;
		pfd.cStencilBits = 8;

		int pixelFormat = ChoosePixelFormat(dummyDc, &pfd);
		if (!pixelFormat)
		{
			std::cout << "Failed to find a suitable pixel format.\n";
			return false;
		}

		if (!SetPixelFormat(dummyDc, pixelFormat, &pfd))
		{
			std::cout << "Failed to set pixel format\n";
			return false;
		}


		HGLRC dummyContext = wglCreateContext(dummyDc);
		if (!dummyContext)
		{
			std::cout << "Failed to create dummy context.\n";
			return false;
		}

		if (!wglMakeCurrent(dummyDc, dummyContext))
		{
			std::cout << "Failed to activate dummy context\n";
			return false;
		}

		if (!gladLoadWGLLoader((GLADloadproc)getFunction, dummyDc))
		{
			std::cout << "Failed to initialize GLAD WGL.\n";
			return false;
		}

		if (!gladLoadGLLoader((GLADloadproc)getFunction))
		{
			std::cout << "Failder to initialize GLAD GL.\n";
			return false;
		}

		wglMakeCurrent(dummyDc, 0);
		wglDeleteContext(dummyContext);
		ReleaseDC(dummyWindow, dummyDc);
		DestroyWindow(dummyWindow);
		return true;
	}

	bool WglContext::create(Window& window)
	{
		auto& win32Window = window.getSystemWindow();
		auto dc = win32Window.getDC();
		int pixelFormatAttribs[]{
			WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
			WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
			WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
			WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
			WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
			WGL_COLOR_BITS_ARB, 32,
			WGL_DEPTH_BITS_ARB, 24,
			WGL_STENCIL_BITS_ARB, 8,
			0
		};

		int pixelFormat;
		uint32_t formatsAvailable;
		wglChoosePixelFormatARB(dc, pixelFormatAttribs, 0, 1, &pixelFormat, &formatsAvailable);
		if (formatsAvailable == 0)
		{
			std::cout << "Failed to set OpenGL pixel format.\n";
			return false;
		}

		int contextAttribs[]{
			WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
			WGL_CONTEXT_MINOR_VERSION_ARB, 3,
			WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
			0
		};

		PIXELFORMATDESCRIPTOR pfd;
		DescribePixelFormat(dc, pixelFormat, sizeof(pfd), &pfd);

		if (!SetPixelFormat(dc, pixelFormat, &pfd))
		{
			std::cout << "Failed to set Opengl pixel format.\n";
			return 0;
		}
		
		m_context = wglCreateContextAttribsARB(dc, 0, contextAttribs);
		if (!m_context)
		{
			std::cout << "Failed to create OpenGL context.\n";
			return false;
		}

		return true;
	}

	bool WglContext::makeCurrent(Window& window)
	{
		if (!wglMakeCurrent(window.getSystemWindow().getDC(), m_context))
		{
			std::cout << "Failed to activate context.\n";
			return false;
		}
		return true;
	}

	void WglContext::destroy()
	{
		if (m_context)
		{
			wglDeleteContext(m_context);
		}
	}

	void WglContext::swapBuffers(Window& window)
	{
		SwapBuffers(window.getSystemWindow().getDC());
	}
}