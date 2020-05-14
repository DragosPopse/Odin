#ifndef ODIN_VEC3_HPP
#define ODIN_VEC3_HPP

#include <odin/Config.hpp>
#include <odin/math/Vec.hpp>
#include <algorithm>

namespace odin
{
	template <typename T>
	struct Vec<3, T>
	{
		static_assert(std::is_arithmetic_v<T>, "Vec3<T>: T is not arithmetic");

		static const size_t size = 3;

		T x = static_cast<T>(0);
		T y = static_cast<T>(0);
		T z = static_cast<T>(0);

	private:
		using ElementType = T Vec<3, T>::* const;
		static const ElementType m_elements[size];
		
	public:
		constexpr Vec(T paramX, T paramY, T paramZ) :
			x(paramX),
			y(paramY),
			z(paramZ)
		{
		}
		constexpr Vec() = default;
		constexpr Vec(const Vec& other) = default;
		constexpr Vec(Vec&& other) = default;
		~Vec() = default;

		template <typename VecType, typename... Args, typename = std::enable_if_t<std::is_class_v<VecType>>>
		constexpr Vec(const VecType& other, Args... values) :
			Vec()
		{
			constexpr size_t minSize = std::min(Vec::size, VecType::size);
			for (size_t i = 0; i < minSize; i++)
			{
				(*this)[i] = other[i];
			}

			constexpr int diff = Vec::size - VecType::size;
			if constexpr (diff > 0)
			{
				initHelper(VecType::size, values...);
			}
			
		}

		Vec& operator=(const Vec& other)
		{
			x = other.x;
			y = other.y;
			z = other.z;
			return *this;
		}


		T operator*(const Vec& other)
		{
			T sum = static_cast<T>(0);
			sum += x * other.x;
			sum += y * other.y;
			sum += z * other.z;
		}


		Vec operator*(T scalar)
		{
			return Vec(x * scalar, y * scalar, z * scalar);
		}


		Vec operator-()
		{
			return Vec(-x, -y, -z);
		}


		T& operator[](size_t i)
		{
			return this->*m_elements[i];
		}


		T operator[](size_t i) const
		{
			return this->*m_elements[i];
		}



		template <typename To, typename = std::enable_if_t<std::is_convertible_v<T, To>>>
		operator Vec<3, To>()
		{
			return Vec<3, To>(
				static_cast<To>(x),
				static_cast<To>(y),
				static_cast<To>(z));
		}


		bool operator==(const Vec<3, T>& other)
		{
			return x == other.x && y == other.y && z == other.z;
		}


		bool operator!=(const Vec<3, T>& other)
		{
			return !(x == other.x && y == other.y && z == other.z);
		}

	
	private:
		template <typename First, typename... Args>
		void initHelper(size_t i, First first, Args... args)
		{
			if (i < size)
			{
				(*this)[i] = first;
				initHelper(i + 1, args...);
			}
		}

		template <typename First>
		void initHelper(size_t i, First first)
		{
			if (i < size)
			{
				(*this)[i] = static_cast<T>(first);
			}
		}

		void initHelper(size_t i)
		{
		}

	};

	template <typename T>
	const typename Vec<3, T>::ElementType Vec<3, T>::m_elements[Vec<3, T>::size] = {
		&Vec<3, T>::x,
		&Vec<3, T>::y,
		&Vec<3, T>::z
	};

	template <typename T>
	using Vec3 = Vec<3, T>;
	using Vec3f = Vec3<float>;
	using Vec3i = Vec3<int32_t>;
	using Vec3u = Vec3<uint32_t>;
	using Vec3d = Vec3<double>;
}

#endif