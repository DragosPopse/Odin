#ifndef ODIN_CONFIG_HPP
#define ODIN_CONFIG_HPP

#include <cstdint>

#if defined(_WIN64)
	#define ODIN_PLATFORM_WINDOWS
#else
	#error "Platform not supported"
#endif

#if defined(ODIN_PLATFORM_WINDOWS)
	#if defined(_MSC_VER)
		#define ODIN_IMPORT __declspec(dllimport)
		#define ODIN_EXPORT __declspec(dllexport)
	#else
		#define ODIN_IMPORT
		#define ODIN_EXPORT
	#endif
#endif

#if defined(ODIN_BUILD_DLL)
	#define ODIN_API ODIN_EXPORT
#else
	#define ODIN_API ODIN_IMPORT
#endif

#endif