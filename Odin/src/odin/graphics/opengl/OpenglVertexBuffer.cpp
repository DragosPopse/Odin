#include <odin/graphics/opengl/OpenglVertexBuffer.hpp>

namespace odin
{
	VertexBuffer::Impl::Impl() :
		m_VBO(0)
	{
		glGenBuffers(1, &m_VBO);
	}

	
	VertexBuffer::Impl::~Impl()
	{
		glDeleteBuffers(1, &m_VBO);
	}


	void VertexBuffer::Impl::bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	}


	void VertexBuffer::Impl::unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, NULL);
	}


	void VertexBuffer::Impl::upload(const std::vector<Vertex>& vertices)
	{
		bind();
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_DYNAMIC_DRAW);
	}
}