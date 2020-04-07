#ifndef ODIN_WINDOW_INFO_HPP
#define ODIN_WINDOW_INFO_HPP

#include <odin/Config.hpp>
#include <string>

#if defined(ODIN_PLATFORM_WINDOWS)
#include <Windows.h>
#endif

namespace odin
{
	struct WindowInfo
	{
		uint32_t width;
		uint32_t height;
		std::wstring title;
		uint32_t style;
	};
}

#endif