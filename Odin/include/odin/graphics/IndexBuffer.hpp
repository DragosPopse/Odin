#ifndef ODIN_INDEX_BUFFER_HPP
#define ODIN_INDEX_BUFFER_HPP

#include <odin/Config.hpp>
#include <vector>

namespace odin
{
	class IndexBuffer
	{
		using IndexType = uint32_t;
		class Impl;
	public:
		IndexBuffer();
		~IndexBuffer();

	private:
		std::unique_ptr<Impl> m_impl;
		std::vector<IndexType> m_indices;
	};
}

#endif