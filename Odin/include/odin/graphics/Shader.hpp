#ifndef ODIN_SHADER_HPP
#define ODIN_SHADER_HPP

#include <odin/Config.hpp>

#include <odin/math/Mat.hpp>
#include <odin/math/Vec2.hpp>
#include <odin/math/Vec3.hpp>
#include <odin/math/Vec4.hpp>


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

		void setMat4(const std::string& name, const Mat4f& mat);
		
	private:
		std::unique_ptr<Impl> m_impl;
	};
}

#endif