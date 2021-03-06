#ifndef ODIN_SHADER_HPP
#define ODIN_SHADER_HPP

#include <odin/Config.hpp>

#include <gmath/mat.hpp>
#include <gmath/vec.hpp>


namespace odin
{

	class Shader
	{
		class Impl;
	public:
		enum class DataType
		{
			None = 0,
			Float,
			Float2,
			Float3,
			Float4,
			Mat3,
			Mat4,
			UnsignedInt,
			Int,
			Int2,
			Int3,
			Int4,
			Bool,
			Byte,
			UnsignedByte
		};

		static constexpr uint32_t getDataTypeSize(DataType type);
		static constexpr uint32_t getDataTypeCount(DataType type);

		enum class Type
		{
			Vertex,
			Fragment,
			Geometry
		};

		Shader();
		~Shader();

		/*
			Load a shader from a file.
		*/
		bool loadFromFile(const std::string& filename, Shader::Type type);
		/*
			Link all the loaded shaders and create the final program.
		*/
		bool link();

		void bind() const;

		void setMat4(const std::string& name, const gm::Mat4f& value);
		void setVec4(const std::string& name, const gm::Vec4f& value);
		void setFloat(const std::string& name, float value);
		
	private:
		std::unique_ptr<Impl> m_impl;
	};
}

#endif