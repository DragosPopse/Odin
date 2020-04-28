#ifndef ODIN_WGL_CONTEXT_HPP
#define ODIN_WGL_CONTEXT_HPP

#include <odin/Config.hpp>
#include <Windows.h>
#include <odin/graphics/GraphicsInfo.hpp>

namespace odin
{
	class Window;

	class WglContext
	{
	public:
		constexpr WglContext() = default;
		~WglContext() = default;

		bool create(Window& window, const GraphicsInfo& info);
		void destroy();
		void swapBuffers();

		static bool init();

	private:
		static void* getFunction(const char* name);
		HGLRC m_context = 0;
		Window* m_window = nullptr;
	};
}

#endif