#ifndef ODIN_OPENGL_TEXTURE_HPP
#define ODIN_OPENGL_TEXTURE_HPP

#include <odin/Config.hpp>
#include <odin/graphics/Texture.hpp>
#include <glad/glad.h>

namespace odin
{
	class Texture::Impl
	{
	public:
		Impl(Texture& base);
		~Impl();

		bool load(unsigned char* data, int channels);

		void bind() const;

	private:
		Texture& m_base;

		uint32_t m_texture;
		
	};
}

#endif