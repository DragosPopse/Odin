#include <odin/graphics/Image.hpp>
#include <stb/stb_image.h>
#include <odin/core/App.hpp>

namespace odin
{
	Image::~Image()
	{
		cleanup();
	}


	void Image::cleanup()
	{
		if (m_data)
		{
			stbi_image_free(m_data);
		}
	}


	bool Image::load(const std::string& file)
	{
		cleanup();
		m_data = stbi_load(file.c_str(), &m_width, &m_height, &m_numberOfChannels, 0);
		if (!m_data)
		{
			return false;
		}
		return true;
	}
}