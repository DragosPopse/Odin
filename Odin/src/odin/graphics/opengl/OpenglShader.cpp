#include <odin/graphics/opengl/OpenglShader.hpp>
#include <fstream>
#include <odin/core/App.hpp>
#include <glad/glad.h>

namespace
{
	constexpr uint32_t MAX_OPENGL_LOG_BUFFER_LENGTH = 512;
}

namespace odin
{
	Shader::Impl::Impl()
	{
		m_program = glCreateProgram();
	}

	bool Shader::Impl::loadFromFile(const std::string& filename, Shader::Type type)
	{
		std::ifstream file(filename, std::ios::ate);
		if (!file.is_open())
		{
			App::get().getSystemLogger()(odin::Logger::Level::Error,
				"Failed to open shader file.");
			return false;
		}
		size_t size = (size_t)file.tellg();
		std::vector<char> shaderSource(size);
		file.seekg(0);
		file.read(shaderSource.data(), size);
		
		uint32_t shader = 0;
		switch (type)
		{
		case Shader::Type::Vertex:
			shader = glCreateShader(GL_VERTEX_SHADER);
			break;

		case Shader::Type::Fragment:
			shader = glCreateShader(GL_FRAGMENT_SHADER);
			break;

		case Shader::Type::Geometry:
			shader = glCreateShader(GL_GEOMETRY_SHADER);
			break;
		}

		auto rawData = shaderSource.data();
		glShaderSource(shader, 1, &rawData, nullptr);
		glCompileShader(shader);
		
		int success;
		char log[MAX_OPENGL_LOG_BUFFER_LENGTH];
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, MAX_OPENGL_LOG_BUFFER_LENGTH, nullptr, log);
			App::get().getSystemLogger()(odin::Logger::Level::Error,
				concat(filename, ": ",log));
			return false;
		}
		

		m_shaders.push_back(shader);
		return true;
	}

	bool Shader::Impl::link()
	{
		for (auto shader : m_shaders)
		{
			glAttachShader(m_program, shader);
		}
		glLinkProgram(m_program);

		int success;
		char log[MAX_OPENGL_LOG_BUFFER_LENGTH];
		glGetProgramiv(m_program, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(m_program, MAX_OPENGL_LOG_BUFFER_LENGTH, nullptr, log);
			App::get().getSystemLogger()(Logger::Level::Error,
				log);
			return false;
		} 

		for (auto shader : m_shaders)
		{
			glDeleteShader(shader);
		}
		m_shaders.clear();
	}

	Shader::Impl::~Impl()
	{
		glDeleteProgram(m_program);
		for (auto shader : m_shaders)
		{
			glDeleteShader(shader);
		}
	}


	void Shader::Impl::bind() const
	{
		glUseProgram(m_program);
	}


	void Shader::Impl::setMat4(const std::string& name, const Mat4f& mat)
	{
		uint32_t location = glGetUniformLocation(m_program, name.c_str());
		glUniformMatrix4fv(location, 1, GL_TRUE, mat.data());
	}
}