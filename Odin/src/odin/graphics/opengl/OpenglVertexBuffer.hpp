#ifndef ODIN_OPENGL_VERTEX_BUFFER_HPP
#define ODIN_OPENGL_VERTEX_BUFFER_HPP

#include <odin/Config.hpp>
#include <odin/graphics/VertexBuffer.hpp>
#include <glad/glad.h>

namespace odin
{
	class VertexBuffer::Impl
	{
	public:
		Impl();
		~Impl();

		void bind() const;
		void unbind() const;

		void upload(const std::vector<Vertex>& vertices);

	private:
		uint32_t m_VBO;
	};
}

#endif