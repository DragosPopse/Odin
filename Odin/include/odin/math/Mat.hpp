#ifndef ODIN_MAT_HPP
#define ODIN_MAT_HPP

#include <odin/Config.hpp>
#include <array>
#include <odin/math/Vec.hpp>

namespace odin
{
	template <size_t ROWS, size_t COLS, typename T>
	class Mat
	{		
	public:
		using ElementsType = std::array<std::array<T, COLS>, ROWS>;
		static const size_t rows = ROWS;
		static const size_t columns = COLS;

		constexpr Mat() = default;
		~Mat() = default;


		constexpr Mat(const ElementsType& elements) :
			m_elements(elements)
		{
		}


		template <typename = std::enable_if_t<ROWS == COLS>>
		constexpr Mat(T scalar) :
			Mat()
		{
			for (size_t i = 0; i < ROWS; i++)
			{
				m_elements[i][i] = scalar;
			}
		}


		const T* data() const
		{
			return &m_elements[0][0];
		}


		std::array<T, COLS>& operator[](size_t index)
		{
			return m_elements[index];
		}


		const std::array<T, COLS>& operator[](size_t index) const
		{
			return m_elements[index];
		}


		template <size_t N>
		Mat<ROWS, N, T> operator*(const Mat<COLS, N, T>& other)
		{
			Mat<ROWS, N, T> result;
			for (int i = 0; i < ROWS; i++)
			{
				for (int j = 0; j < N; j++)
				{
					for (int k = 0; k < ROWS; k++)
					{
						result[i][j] += m_elements[i][k] * m_elements[k][j];
					}
				}
			}
			return result;
		}

		Vec<COLS, T> operator*(const Vec<COLS, T>& v)
		{
			Vec<COLS, T> result;
			for (int i = 0; i < COLS; i++)
			{
				for (int j = 0; j < COLS; j++)
				{
					result[i] += m_elements[i][j] * v[j];
				}
			}
			return result;
		}

	private:
		ElementsType m_elements = {};
	};


	template <typename T>
	using Mat2 = Mat<2, 2, T>;
	
	template <typename T>
	using Mat3 = Mat<3, 3, T>;

	template <typename T>
	using Mat4 = Mat<4, 4, T>;

	using Mat2f = Mat2<float>;
	using Mat3f = Mat3<float>;
	using Mat4f = Mat4<float>;
}


template <size_t ROWS, size_t COLS, typename T>
odin::Mat<ROWS, COLS, T> operator*(T scalar, const odin::Mat<ROWS, COLS, T>& matrix)
{
	odin::Mat<ROWS, COLS, T> result;
	for (size_t i = 0; i < matrix.rows; i++)
	{
		for (size_t j = 0; j < matrix.cols; j++)
		{
			result[i][j] = scalar * matrix[i][j];
		}
	}
}


template <size_t ROWS, size_t COLS, typename T>
odin::Mat<ROWS, COLS, T> operator*(const odin::Mat<ROWS, COLS, T>& matrix, T scalar)
{
	odin::Mat<ROWS, COLS, T> result;
	for (size_t i = 0; i < matrix.rows; i++)
	{
		for (size_t j = 0; j < matrix.cols; j++)
		{
			result[i][j] = scalar * matrix[i][j];
		}
	}
}


template <size_t N, typename T>
odin::Mat<N, N, T> operator+(const odin::Mat<N, N, T>& lhs, const odin::Mat<N, N, T>& rhs)
{
	odin::Mat<N, N, T> result;
}


#endif