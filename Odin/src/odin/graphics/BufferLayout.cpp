#include <odin/graphics/BufferLayout.hpp>


namespace odin
{
	BufferElement::BufferElement(Shader::DataType ttype, const std::string& tname, bool tnormalize) :
		type(ttype),
		name(tname),
		normalize(tnormalize),
		size(Shader::getDataTypeSize(ttype)),
		offset(0)
	{
	}


	BufferLayout::BufferLayout(const std::initializer_list<BufferElement>& elements) :
		m_elements(elements),
		m_stride(0)
	{
		uint32_t offset = 0;
		for (auto& element : m_elements)
		{
			element.offset = offset;
			offset += element.size; 
			m_stride += element.size;
		}
	}


	std::vector<BufferElement>::iterator BufferLayout::begin()
	{
		return m_elements.begin();
	}


	std::vector<BufferElement>::iterator BufferLayout::end()
	{
		return m_elements.end();
	}


	std::vector<BufferElement>::const_iterator BufferLayout::begin() const
	{
		return m_elements.begin();
	}


	std::vector<BufferElement>::const_iterator BufferLayout::end() const
	{
		return m_elements.end();
	}
}