#ifndef ODIN_VERTEX_BUFFER_HPP
#define ODIN_VERTEX_BUFFER_HPP

#include <odin/Config.hpp>
#include <odin/graphics/Vertex.hpp>
#include <vector>
#include <odin/graphics/BufferLayout.hpp>

namespace odin
{
	class VertexBuffer
	{
		class Impl;
	public:
		VertexBuffer();
		~VertexBuffer();

		void bind() const;
		void unbind() const;

		void add(const Vertex& vertex);
		
		const Vertex* data() const noexcept;

		size_t size() const;

		void upload() const;

		inline void setLayout(const BufferLayout& layout)
		{
			m_layout = layout;
		}

		inline const BufferLayout& layout() const
		{
			return m_layout;
		}

	private:
		std::unique_ptr<Impl> m_impl;
		std::vector<Vertex> m_vertices;
		BufferLayout m_layout;
	};
}

#endif