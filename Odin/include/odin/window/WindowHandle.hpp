#ifndef ODIN_WINDOW_HANDLE_HPP
#define ODIN_WINDOW_HANDLE_HPP

#include <odin/Config.hpp>

#if defined(ODIN_PLATFORM_WINDOWS)

#include <Windows.h>

namespace odin
{
	using WindowHandle = HWND;
}

#endif


#endif