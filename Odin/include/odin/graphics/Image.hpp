#ifndef ODIN_IMAGE_HPP
#define ODIN_IMAGE_HPP

#include <odin/Config.hpp>
#include <string>

namespace odin
{
	class Image
	{
		unsigned char* m_data = nullptr;
		int32_t m_width = 0;
		int32_t m_height = 0;
		int32_t m_numberOfChannels = 0;

	public:
		constexpr Image() = default;
		~Image();

		bool load(const std::string& filename);

		int32_t width() const { return m_width; }
		int32_t height() const { return m_height; }
		int32_t channels() const { return m_numberOfChannels; }
		unsigned char* data() const { return m_data; }

	private:
		void cleanup();
	};
}

#endif