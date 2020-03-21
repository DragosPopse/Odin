#ifndef ODIN_VECTOR2_HPP
#define ODIN_VECTOR2_HPP

#include <odin/Config.hpp>
#include <type_traits>


namespace odin
{
	template <typename T>
	struct Vector2
	{
		T x;
		T y;

	public:
		Vector2(T paramX, T paramY) :
			x(paramX),
			y(paramY)
		{
		}
		Vector2() = default;
		~Vector2() = default;

		template <typename To, typename = std::enable_if_t<std::is_convertible_v<T, To>>>
		operator Vector2<To>()
		{
			return Vector2<To>(
				static_cast<To>(x),
				static_cast<To>(y));
		}
	};

	using Vector2f = Vector2<float>;
	using Vector2i = Vector2<int32_t>;
	using Vector2u = Vector2<uint32_t>;
	using Vector2d = Vector2<double>;
}


#endif