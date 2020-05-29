#ifndef ODIN_OPENGL_SHADER_HPP
#define ODIN_OPENGL_SHADER_HPP

#include <odin/Config.hpp>
#include <odin/graphics/Shader.hpp>
#include <vector>

namespace odin
{
	class Shader::Impl
	{
	public:
		Impl();
		~Impl();

		bool loadFromFile(const std::string& filename, Shader::Type type);
		bool link();

		void bind() const;

		void setMat4(const std::string& name, const Mat4f& value);
		void setVec4(const std::string& name, const Vec4f& value);
		void setFloat(const std::string& name, float value);

	private:
		uint32_t m_program;
		std::vector<uint32_t> m_shaders;
	};
}

#endif