#ifndef ODIN_OPENGL_INDEX_BUFFER_HPP
#define ODIN_OPENGL_INDEX_BUFFER_HPP

#include <odin/Config.hpp>
#include <odin/graphics/IndexBuffer.hpp>
#include <glad/glad.h>

namespace odin
{
	class IndexBuffer::Impl
	{
	public:
		Impl();
		~Impl();
		void bind();
		void unbind();

	private:
		uint32_t m_EBO;
	};
}

#endif