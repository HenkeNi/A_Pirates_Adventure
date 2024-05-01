#pragma once
#include "Matrix4x4.hpp"
#include "../Vectors/Vector.hpp"
#include <array>


namespace Hi_Engine::Math
{
	template <typename T>
	class Matrix3x3
	{
	public:
		Matrix3x3();
		Matrix3x3(const Matrix3x3& matrix);
		Matrix3x3(const Matrix4x4<T>& matrix);

		Matrix3x3&			operator=(const Matrix3x3&)					= default;
		Matrix3x3&			operator=(const Matrix4x4<T>& matrix);

		Vector3<T>&			operator()(const int row);
		const Vector3<T>&	operator()(const int row)						const;

		T&					operator()(const int row, const int column);
		const T&			operator()(const int row, const int column)	const;

		static Matrix3x3	CreateRotationAroundX(T angleInRadians);
		static Matrix3x3	CreateRotationAroundY(T angleInRadians);
		static Matrix3x3	CreateRotationAroundZ(T angleInRadians);
		static Matrix3x3	Transpose(const Matrix3x3& matrixToTranspose);

	private:
		std::array<Vector3<T>, 3> m_matrix;
	};

#pragma region Method_Definitions

	/* - Creates an identity matrix - */
	template <typename T>
	Matrix3x3<T>::Matrix3x3()
	{
		m_matrix[0] = { 1.f, 0.f, 0.f };
		m_matrix[1] = { 0.f, 1.f, 0.f };
		m_matrix[2] = { 0.f, 0.f, 1.f };
	}

	/* - Copy constructor - */
	template <typename T>
	Matrix3x3<T>::Matrix3x3(const Matrix3x3<T>& matrix)
		: m_matrix{ matrix.m_matrix }
	{
	}

	/* - Copies the top left 3x3 part of the 4x4 Matrix - */
	template <typename T>
	Matrix3x3<T>::Matrix3x3(const Matrix4x4<T>& matrix)
	{
		*this = matrix;
	}

	/* - Creates a rotation matrice around x-axis - */
	template <typename T>
	Matrix3x3<T> Matrix3x3<T>::CreateRotationAroundX(T angleInRadians)
	{
		Matrix3x3<T> matrix;
		matrix.m_matrix[0] = { 1.f, 0.f, 0.f };
		matrix.m_matrix[1] = { 0.f, cos(angleInRadians), sin(angleInRadians) };
		matrix.m_matrix[2] = { 0.f, -sin(angleInRadians), cos(angleInRadians) };

		return matrix;
	}

	/* - Creates a rotation matrice around y-axis - */
	template <typename T>
	Matrix3x3<T> Matrix3x3<T>::CreateRotationAroundY(T angleInRadians)
	{
		Matrix3x3<T> matrix;
		matrix.m_matrix[0] = { cos(angleInRadians), 0, -sin(angleInRadians) };
		matrix.m_matrix[1] = { 0, 1, 0 };
		matrix.m_matrix[2] = { sin(angleInRadians), 0, cos(angleInRadians) };

		return matrix;
	}

	/* - Creates a rotation matrice around z-axis - */
	template <typename T>
	Matrix3x3<T> Matrix3x3<T>::CreateRotationAroundZ(T angleInRadians)
	{
		Matrix3x3<T> matrix;
		matrix.m_matrix[0] = { cos(angleInRadians), sin(angleInRadians), 0 };
		matrix.m_matrix[1] = { -sin(angleInRadians), cos(angleInRadians), 0 };
		matrix.m_matrix[2] = { 0, 0, 1 };

		return matrix;
	}

	/* - Transpose swaps the places between columns and rows - */
	template <typename T>
	Matrix3x3<T> Matrix3x3<T>::Transpose(const Matrix3x3<T>& matrixToTranspose)
	{
		Matrix3x3<T> matrix;
		for (int row = 1; row <= 3; ++row)
		{
			for (int col = 1; col <= 3; ++col)
			{
				matrix(col, row) = matrixToTranspose(row, col);
			}
		}
		return matrix;
	}

#pragma endregion METHOD_DEFINITIONS

#pragma region OPERATOR_OVERLOADS

	template <typename T>
	Matrix3x3<T>& Matrix3x3<T>::operator=(const Matrix4x4<T>& matrix)
	{
		for (int i = 1; i <= 3; ++i)
		{
			for (int j = 1; j <= 3; ++j)
			{
				(*this)(i, j) = matrix(i, j);
			}
		}
		return *this;
	}

	/* - Access Vector3 at specified row - */
	template <typename T>
	Vector3<T>& Matrix3x3<T>::operator()(const int row)
	{
		assert(row > 0 && row <= m_matrix.size());
		return m_matrix[row - 1];
	}

	/* - Access Vector3 at specified row (read only) - */
	template <typename T>
	const Vector3<T>& Matrix3x3<T>::operator()(const int row) const
	{
		assert(row > 0 && row <= m_matrix.size());
		return m_matrix[row - 1];
	}

	/* - Access element at specified position - */
	template <typename T>
	T& Matrix3x3<T>::operator()(const int row, const int column)
	{
		assert(row > 0 && row <= 3); // myMatrix.size());
		assert(column > 0 && column <= 3);

		return column == 1 ? m_matrix[row - 1].x : column == 2 ? m_matrix[row - 1].y : m_matrix[row - 1].z;
	}

	/* - Access element at specified position (read only) - */
	template <typename T>
	const T& Matrix3x3<T>::operator()(const int row, const int column) const
	{
		assert(row > 0 && row <= 3);
		assert(column > 0 && column <= 3);

		return column == 1 ? m_matrix[row - 1].x : column == 2 ? m_matrix[row - 1].y : m_matrix[row - 1].z;
	}

	template <typename T>
	void operator+=(Matrix3x3<T>& lhs, const Matrix3x3<T>& rhs)
	{
		for (int i = 1; i <= 3; ++i)
		{
			lhs(i) += rhs(i);
		}
	}

	template <typename T>
	void operator-=(Matrix3x3<T>& lhs, const Matrix3x3<T>& rhs)
	{
		for (int i = 1; i <= 3; ++i)
		{
			lhs(i) -= rhs(i);
		}
	}

	template <typename T>
	void operator*=(Matrix3x3<T>& lhs, const Matrix3x3<T>& rhs)
	{
		Matrix3x3<T> matrix;
		for (int i = 1; i <= 3; ++i)
		{
			for (int j = 1; j <= 3; ++j)
			{
				matrix(i, j) = 0.0f;
				for (int k = 1; k <= 3; ++k)
				{
					matrix(i, j) += lhs(i, k) * rhs(k, j);
				}
			}
		}
		lhs = matrix;
	}

	template <typename T>
	bool operator==(const Matrix3x3<T>& lhs, const Matrix3x3<T>& rhs)
	{
		for (int i = 1; i <= 3; ++i)
		{
			if (lhs(i) != rhs(i))
			{
				return false;
			}
		}
		return true;
	}

	template <typename T>
	Matrix3x3<T> operator+(const Matrix3x3<T>& lhs, const Matrix3x3<T>& rhs)
	{
		Matrix3x3<T> matrix;
		for (int i = 1; i <= 3; ++i)
		{
			matrix(i) = lhs(i) + rhs(i);
		}
		return matrix;
	}

	template <typename T>
	Matrix3x3<T> operator-(const Matrix3x3<T>& lhs, const Matrix3x3<T>& rhs)
	{
		Matrix3x3<T> matrix;
		for (int i = 1; i <= 3; ++i)
		{
			matrix(i) = lhs(i) - rhs(i);
		}
		return matrix;
	}

	template <typename T>
	Matrix3x3<T> operator*(const Matrix3x3<T>& lhs, const Matrix3x3<T>& rhs)
	{
		Matrix3x3<T> matrix;
		for (int i = 1; i <= 3; ++i)
		{
			for (int j = 1; j <= 3; ++j)
			{
				matrix(i, j) = 0.0f;
				for (int k = 1; k <= 3; ++k)
				{
					matrix(i, j) += lhs(i, k) * rhs(k, j);
				}
			}
		}
		return matrix;
	}

	template <typename T>
	Vector3<T> operator*(const Vector3<T>& vector, const Matrix3x3<T>& matrix)
	{
		Vector3<T> result;
		result.x = vector.x * matrix(1, 1) + vector.y * matrix(2, 1) + vector.z * matrix(3, 1);
		result.y = vector.x * matrix(1, 2) + vector.y * matrix(2, 2) + vector.z * matrix(3, 2);
		result.z = vector.x * matrix(1, 3) + vector.y * matrix(2, 3) + vector.z * matrix(3, 3);

		return result;
	}

#pragma endregion OPERATOR_OVERLOADS
}
