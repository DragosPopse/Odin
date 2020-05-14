#include <odin/graphics/opengl/OpenglIndexBuffer.hpp>


namespace odin
{
	IndexBuffer::Impl::Impl() :
		m_EBO(0)
	{
		glGenBuffers(1, &m_EBO);
	}


	IndexBuffer::Impl::~Impl()
	{
		glDeleteBuffers(1, &m_EBO);
	}


	void IndexBuffer::Impl::bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	}


	void IndexBuffer::Impl::unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
	}
}