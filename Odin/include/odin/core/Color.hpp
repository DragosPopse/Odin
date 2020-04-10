#ifndef ODIN_COLOR_HPP
#define ODIN_COLOR_HPP

#include <odin/Config.hpp>

struct Color
{
	uint8_t r = 0;
	uint8_t g = 0;
	uint8_t b = 0;
	uint8_t a = 255;

	constexpr Color() = default;

	Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255) :
		r(red),
		g(green),
		b(blue),
		a(alpha)
	{
	}

	~Color() = default;
};

#endif