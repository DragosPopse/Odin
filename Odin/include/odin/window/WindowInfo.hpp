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
		uint32_t width = 0;
		uint32_t height = 0;
		std::wstring title = L"Odin Application";
		uint32_t style = 0;

		constexpr WindowInfo() = default;
	};
}

#endif