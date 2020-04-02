#ifndef ODIN_WINDOW_INFO_HPP
#define ODIN_WINDOW_INFO_HPP

#include <odin/Config.hpp>
#include <string>

namespace odin
{
	struct WindowInfo
	{
		uint32_t width;
		uint32_t height;
		std::string name;
	};
}

#endif