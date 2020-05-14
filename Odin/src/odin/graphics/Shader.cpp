#include <odin/graphics/Shader.hpp>

#if defined(ODIN_RENDERAPI_OPENGL)
#include <odin/graphics/opengl/OpenglShader.hpp>
#elif defined(ODIN_RENDERAPI_VULKAN)
#include <odin/graphics/vk/VulkanShader.hpp>
#endif

namespace odin
{
	constexpr uint32_t Shader::getDataTypeSize(Shader::DataType type)
	{
		switch (type)
		{
		case Shader::DataType::Float: return 4;
		case Shader::DataType::Float2: return 4 * 2;
		case Shader::DataType::Float3: return 4 * 3;
		case Shader::DataType::Float4: return 4 * 4;
		case Shader::DataType::Mat3: return 4 * 3 * 3;
		case Shader::DataType::Mat4: return 4 * 4 * 4;
		case Shader::DataType::UnsignedInt: return 4;
		case Shader::DataType::Int: return 4;
		case Shader::DataType::Int2: return 4 * 2;
		case Shader::DataType::Int3: return 4 * 3;
		case Shader::DataType::Int4: return 4 * 4;
		case Shader::DataType::Bool: return 1;
		case Shader::DataType::Byte: return 1;
		case Shader::DataType::UnsignedByte: return 1;
		}

		return 0;
	}


	constexpr uint32_t Shader::getDataTypeCount(Shader::DataType type)
	{
		switch (type)
		{
		case Shader::DataType::Float: return 1;
		case Shader::DataType::Float2: return 2;
		case Shader::DataType::Float3: return 3;
		case Shader::DataType::Float4: return 4;
		case Shader::DataType::Mat3: return 3 * 3;
		case Shader::DataType::Mat4: return 4 * 4;
		case Shader::DataType::UnsignedInt: return 1;
		case Shader::DataType::Int: return 1;
		case Shader::DataType::Int2: return 2;
		case Shader::DataType::Int3: return 3;
		case Shader::DataType::Int4: return 4;
		case Shader::DataType::Bool: return 1;
		case Shader::DataType::Byte: return 1;
		case Shader::DataType::UnsignedByte: return 1;
		}

		return 0;
	}


	Shader::Shader() :
		m_impl(new Impl())
	{
	}


	Shader::~Shader()
	{
	}


	bool Shader::loadFromFile(const std::string& filename, Shader::Type type)
	{
		return m_impl->loadFromFile(filename, type);
	}


	bool Shader::link()
	{
		return m_impl->link();
	}


	void Shader::bind() const
	{
		m_impl->bind();
	}


	void Shader::setMat4(const std::string& name, const Mat4f& mat)
	{
		m_impl->setMat4(name, mat); 
	}
}