#ifndef ODIN_TEXTURE_HPP
#define ODIN_TEXTURE_HPP

#include <odin/Config.hpp>
#include <string>


namespace odin
{
	class Texture
	{
		class Impl;

	public:
		Texture();
		~Texture();

		bool loadFromFile(const std::string& filename);

		void bind() const;

		int32_t width() const { return m_width; }
		int32_t height() const { return m_height; }

	private:
		std::unique_ptr<Impl> m_impl;
		int32_t m_width;
		int32_t m_height;
	};
}


#endif