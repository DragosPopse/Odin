#ifndef ODIN_WGL_CONTEXT_HPP
#define ODIN_WGL_CONTEXT_HPP

#include <odin/Config.hpp>
#include <Windows.h>

namespace odin
{
	class Window;

	class WglContext
	{
	public:
		constexpr WglContext() = default;
		~WglContext() = default;

		bool create(Window& window);
		void destroy();
		bool makeCurrent(Window& window);
		static void swapBuffers(Window& window);

		static bool init();

	private:
		static void* getFunction(const char* name);
		HGLRC m_context = 0;
	};
}

#endif