#include <odin/graphics/Texture.hpp>
#include <odin/graphics/Image.hpp>

#if defined(ODIN_RENDERAPI_OPENGL)
#include <odin/graphics/opengl/OpenglTexture.hpp>
#endif


namespace odin
{
	Texture::Texture() :
		m_impl(new Impl(*this)),
		m_height(0),
		m_width(0)
	{
	}


	Texture::~Texture()
	{
	}


	void Texture::bind() const
	{
		m_impl->bind();
	}


	bool Texture::loadFromFile(const std::string& filename)
	{
		Image image;
		bool success = image.load(filename);
		m_width = image.width();
		m_height = image.height();
		if (success)
		{
			if (m_impl->load(image.data(), image.channels()))
			{
				return true;
			}
		}
		return false;
	}
}