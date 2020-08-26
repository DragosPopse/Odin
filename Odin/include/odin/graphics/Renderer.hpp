#ifndef ODIN_RENDERER_HPP
#define ODIN_RENDERER_HPP

#include <odin/Config.hpp>
#include <odin/graphics/VertexBuffer.hpp>
#include <odin/graphics/IndexBuffer.hpp>
#include <odin/graphics/Color.hpp>
#include <gmath/mat.hpp>
#include <odin/graphics/Shader.hpp>

namespace odin
{
	class Renderer
	{
		class Impl;
	public:
		Renderer() = delete;

		static void init();

		static void draw();

		static void destroy();

		static void clear();

		static void setClearColor(const Color& color);
	};
}

#endif