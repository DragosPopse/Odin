#include <odin/graphics/VertexBuffer.hpp>

#if defined(ODIN_RENDERAPI_OPENGL)
#include <odin/graphics/opengl/OpenglVertexBuffer.hpp>
#elif defined(ODIN_RENDERAPI_VULKAN)

#endif

namespace odin
{
	VertexBuffer::VertexBuffer() :
		m_impl(new Impl())
	{
	}


	VertexBuffer::~VertexBuffer()
	{
	}


	const Vertex* VertexBuffer::data() const noexcept
	{
		return m_vertices.data();
	}


	size_t VertexBuffer::size() const
	{
		return m_vertices.size();
	}


	void VertexBuffer::upload() const
	{
		m_impl->upload(m_vertices);
	}

	
	void VertexBuffer::bind() const
	{
		m_impl->bind();
	}


	void VertexBuffer::unbind() const
	{
		m_impl->unbind();
	}


	void VertexBuffer::add(const Vertex& vertex)
	{
		m_vertices.push_back(vertex);
	}
}