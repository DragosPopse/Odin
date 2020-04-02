#ifndef ODIN_CONFIG_HPP
#define ODIN_CONFIG_HPP

#include <cstdint>

#if defined(_WIN64)
	#define ODIN_PLATFORM_WINDOWS
#else
	#error "Platform not supported"
#endif


#endif