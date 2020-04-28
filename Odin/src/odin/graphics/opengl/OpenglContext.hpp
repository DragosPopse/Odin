#ifndef ODIN_OPENGL_CONTEXT_HPP
#define ODIN_OPENGL_CONTEXT_HPP

#include <odin/Config.hpp>
#include <odin/graphics/GraphicsContext.hpp>

namespace odin
{
	class GraphicsContext::Impl
	{
		class Impl2; // WGL/GLX/EGL

	public:
		Impl();
		~Impl();

		void create(Window& window, const GraphicsInfo& info);
		void destroy();
		void swapBuffers();

		static void init();
		
	private:
		std::unique_ptr<Impl2> m_impl;
	};
}

#endif