#ifndef ODIN_VEC2_HPP
#define ODIN_VEC2_HPP

#include <odin/Config.hpp>
#include <type_traits>


namespace odin
{
	template <typename T, 
		typename = std::is_fundamental<T>, 
		typename = std::is_arithmetic<T>>
	struct Vec2
	{
		T x = static_cast<T>(0);
		T y = static_cast<T>(0);

	public:
		constexpr Vec2(T paramX, T paramY) :
			x(paramX),
			y(paramY)
		{
		}
		constexpr Vec2() = default;
		Vec2(const Vec2& other) = default;
		Vec2(Vec2&& other) = default;
		~Vec2() = default;
		
		Vec2& operator=(const Vec2 other)
		{
			x = other.x;
			y = other.y;
			return *this;
		}

		template <typename To, typename = std::enable_if_t<std::is_convertible_v<T, To>>>
		operator Vec2<To>()
		{
			return Vec2<To>(
				static_cast<To>(x),
				static_cast<To>(y));
		}

		bool operator==(Vec2<T> other)
		{
			return x == other.x && y == other.y;
		}

		bool operator!=(Vec2<T> other)
		{
			return !(x == other.x && y == other.y);
		}
	};

	using Vec2f = Vec2<float>;
	using Vec2i = Vec2<int32_t>;
	using Vec2u = Vec2<uint32_t>;
	using Vec2d = Vec2<double>;
}


#endif