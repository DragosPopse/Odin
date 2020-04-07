#ifndef ODIN_CONFIG_HPP
#define ODIN_CONFIG_HPP

#include <cstdint>

#if defined(_WIN64)
	#define ODIN_PLATFORM_WINDOWS
	#define NOMINMAX
#else
	#error "Platform not supported"
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