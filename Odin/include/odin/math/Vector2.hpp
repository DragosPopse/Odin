#ifndef ODIN_VECTOR2_HPP
#define ODIN_VECTOR2_HPP

#include <odin/Config.hpp>
#include <type_traits>


namespace odin
{
	template <typename T, 
		typename = std::is_fundamental<T>, 
		typename = std::is_arithmetic<T>>
	struct Vector2
	{
		T x = static_cast<T>(0);
		T y = static_cast<T>(0);

	public:
		constexpr Vector2(T paramX, T paramY) :
			x(paramX),
			y(paramY)
		{
		}
		constexpr Vector2() = default;
		Vector2(const Vector2& other) = default;
		Vector2(Vector2&& other) = default;
		~Vector2() = default;
		
		Vector2& operator=(const Vector2 other)
		{
			x = other.x;
			y = other.y;
			return *this;
		}

		template <typename To, typename = std::enable_if_t<std::is_convertible_v<T, To>>>
		operator Vector2<To>()
		{
			return Vector2<To>(
				static_cast<To>(x),
				static_cast<To>(y));
		}

		bool operator==(Vector2<T> other)
		{
			return x == other.x && y == other.y;
		}

		bool operator!=(Vector2<T> other)
		{
			return !(x == other.x && y == other.y);
		}
	};

	using Vector2f = Vector2<float>;
	using Vector2i = Vector2<int32_t>;
	using Vector2u = Vector2<uint32_t>;
	using Vector2d = Vector2<double>;
}


#endif