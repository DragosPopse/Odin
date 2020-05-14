#ifndef ODIN_BUFFER_LAYOUT_HPP
#define ODIN_BUFFER_LAYOUT_HPP

#include <odin/Config.hpp>
#include <odin/graphics/Shader.hpp>
#include <vector>

namespace odin
{
	struct BufferElement
	{
		std::string name;
		Shader::DataType type;
		bool normalize;
		uint32_t size;
		uint32_t offset;

		BufferElement(Shader::DataType type, const std::string& name, bool tnormalize = false);
	};


	class BufferLayout
	{
	public:
		BufferLayout(const std::initializer_list<BufferElement>& elements);
		BufferLayout() = default;

		~BufferLayout() = default;

		std::vector<BufferElement>::iterator begin();
		std::vector<BufferElement>::iterator end();
		std::vector<BufferElement>::const_iterator begin() const;
		std::vector<BufferElement>::const_iterator end() const;

	private:
		std::vector<BufferElement> m_elements;
		uint32_t m_stride = 0;
	};
}


#endif