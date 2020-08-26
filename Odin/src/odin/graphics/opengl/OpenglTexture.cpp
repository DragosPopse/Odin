#include <odin/graphics/opengl/OpenglTexture.hpp>
#include <odin/core/App.hpp>

namespace odin
{
	Texture::Impl::Impl(Texture& base) :
		m_base(base),
		m_texture(0)
	{
		glGenTextures(1, &m_texture);
	}


	Texture::Impl::~Impl()
	{
		glDeleteTextures(1, &m_texture);
	}


	void Texture::Impl::bind() const
	{
		glBindTexture(GL_TEXTURE_2D, m_texture);
	}


	bool Texture::Impl::load(unsigned char* data, int channels)
	{
		bind();
		GLint internalFormat;
		GLint format;
		switch (channels)
		{
		case 3:
			internalFormat = format = GL_RGB;
			break;

		case 4:
			internalFormat = format = GL_RGBA;
			break;

		default:
			return false;
		}
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_base.m_width, m_base.m_height, 0, format, GL_UNSIGNED_BYTE, data);
		//glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		return true;
	}
}