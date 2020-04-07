#ifndef ODIN_CONFIG_HPP
#define ODIN_CONFIG_HPP

#include <cstdint>
#include <type_traits>

#if defined(_WIN64)
	#define ODIN_PLATFORM_WINDOWS
	#define NOMINMAX
#else
	#error "Platform not supported"
#endif

#if defined(ODIN_PLATFORM_WINDOWS)
	#define ODIN_MAIN_SIGNATURE int WINAPI ::WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
#else
	#define ODIN_MAIN_SIGNATURE int ::main(int, char**)
#endif

#define ODIN_BIT(x) (1 << x)

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
}

#endif