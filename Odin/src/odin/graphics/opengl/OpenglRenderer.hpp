#ifndef ODIN_OPENGL_RENDERER_HPP
#define ODIN_OPENGL_RENDERER_HPP

#include <odin/Config.hpp>
#include <odin/graphics/Renderer.hpp>
#include <glad/glad.h>

namespace odin
{
	class Renderer::Impl
	{
	public:
		Impl() = delete;

		static void init();

		static void draw();
		
		static void destroy();

		static void clear();
		static void setClearColor(const Color& color);

	private:
		static uint32_t s_quadVAO;
		static uint32_t s_quadEBO;
		static uint32_t s_quadVBO;
	};
}

#endif