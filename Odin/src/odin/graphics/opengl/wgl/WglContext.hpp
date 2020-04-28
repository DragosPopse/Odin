#ifndef ODIN_WGL_CONTEXT_HPP
#define ODIN_WGL_CONTEXT_HPP

#include <odin/Config.hpp>
#include <Windows.h>
#include <odin/graphics/GraphicsInfo.hpp>
#include <odin/graphics/opengl/OpenglContext.hpp>

namespace odin
{
	class Window;

	class GraphicsContext::Impl::Impl2
	{
	public:
		constexpr Impl2() = default;
		~Impl2() = default;

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