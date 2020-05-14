#ifndef ODIN_CONFIG_HPP
#define ODIN_CONFIG_HPP

#include <cstdint>
#include <type_traits>

//to be added in other header
#include <string>
#include <sstream>

#if defined(_WIN64)
	#define ODIN_PLATFORM_WINDOWS
#else
	#error "Platform not supported"
#endif

#if defined(ODIN_PLATFORM_WINDOWS)
	#define NOMINMAX
	#define ODIN_MAIN_SIGNATURE int WINAPI ::WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
#else
	#define ODIN_MAIN_SIGNATURE int ::main(int, char**)
#endif

#define ODIN_BIT(x) (1 << x)

#define ODIN_STANDARD_LOG_FORMAT "[{mday}/{nmon}/{year} {hour}:{min}:{sec}] [{lvl}] {0}"

namespace odin
{
	template <typename E>
	constexpr auto etoi(E e)
	{
		return static_cast<std::underlying_type_t<E>>(e);
	}

	template <typename... Args>
	constexpr auto mask(Args... args)
	{
		return (etoi(args) | ...);
	}

	//to be added in other header
	template <typename... Args>
	std::string concat(Args&&... args)
	{
		std::stringstream ss;
		(ss << ... << args);
		return ss.str();
	}
}

#endif