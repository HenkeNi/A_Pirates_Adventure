#pragma once
#include "../Vectors/Vector.hpp"
#include <array>

namespace Hi_Engine::Math
{
	template <typename T>
	class Matrix4x4
	{
	public:
		Matrix4x4();
		Matrix4x4(const Matrix4x4& matrix);

		Matrix4x4&			operator=(const Matrix4x4&)					= default;

		Vector4<T>&			operator()(const int row);
		const Vector4<T>&	operator()(const int row)						const;

		T&					operator()(const int row, const int column);
		const T&			operator()(const int row, const int column)	const;

		static Matrix4x4	CreateRotationAroundX(T angleInRadians);
		static Matrix4x4	CreateRotationAroundY(T angleInRadians);
		static Matrix4x4	CreateRotationAroundZ(T angleInRadians);

		static Matrix4x4	GetFastInverse(const Matrix4x4<T>& transform);
		static Matrix4x4	Transpose(const Matrix4x4& matrixToTranspose);

	private:
		std::array<Vector4<T>, 4> m_matrix;

	};

#pragma region METHOD_DEFINITIONS

	/* - Creates the identity matrix - */
	template <typename T>
	Matrix4x4<T>::Matrix4x4()
	{
		m_matrix[0] = { 1.f, 0.f, 0.f, 0.f };
		m_matrix[1] = { 0.f, 1.f, 0.f, 0.f };
		m_matrix[2] = { 0.f, 0.f, 1.f, 0.f };
		m_matrix[3] = { 0.f, 0.f, 0.f, 1.f };
	}

	template <typename T>
	Matrix4x4<T>::Matrix4x4(const Matrix4x4& matrix)
		: m_matrix{ matrix.m_matrix }
	{
	}

	template <typename T>
	Matrix4x4<T> Matrix4x4<T>::CreateRotationAroundX(T angleInRadians)
	{
		Matrix4x4<T> matrix;
		matrix.m_matrix[0] = { 1.f, 0.f, 0.f, 0.f };
		matrix.m_matrix[1] = { 0.f,  cos(angleInRadians), sin(angleInRadians), 0.f };
		matrix.m_matrix[2] = { 0.f, -sin(angleInRadians), cos(angleInRadians), 0.f };
		matrix.m_matrix[3] = { 0.f, 0.f, 0.f, 1.f };

		return matrix;
	}

	template <typename T>
	Matrix4x4<T> Matrix4x4<T>::CreateRotationAroundY(T angleInRadians)
	{
		Matrix4x4<T> matrix;
		matrix.m_matrix[0] = { cos(angleInRadians), 0.f, -sin(angleInRadians), 0.f };
		matrix.m_matrix[1] = { 0.f, 1.f, 0.f, 0.f };
		matrix.m_matrix[2] = { sin(angleInRadians), 0.f, cos(angleInRadians), 0.f };
		matrix.m_matrix[3] = { 0.f, 0.f, 0.f, 1.f };

		return matrix;
	}

	template <typename T>
	Matrix4x4<T> Matrix4x4<T>::CreateRotationAroundZ(T angleInRadians)
	{
		Matrix4x4<T> matrix;
		matrix.m_matrix[0] = { cos(angleInRadians), sin(angleInRadians), 0.f, 0.f };
		matrix.m_matrix[1] = { -sin(angleInRadians), cos(angleInRadians), 0.f, 0.f };
		matrix.m_matrix[2] = { 0.f, 0.f, 1.f, 0.f };
		matrix.m_matrix[3] = { 0.f, 0.f, 0.f, 1.f };

		return matrix;
	}

	template <typename T>
	Matrix4x4<T> Matrix4x4<T>::GetFastInverse(const Matrix4x4<T>& transform)
	{
		// Copy the 3x3 part of aTransform
		Matrix4x4<T> rotationMatrix = transform;
		rotationMatrix(4) = { 0.f, 0.f, 0.f, 1.f };

		rotationMatrix = Transpose(rotationMatrix);

		Matrix4x4<T> matrix;
		for (int i = 1; i < 4; ++i)
		{
			matrix(4, i) = transform(4, i) * -1;
		}
		return matrix * rotationMatrix;
	}

	template <typename T>
	Matrix4x4<T> Matrix4x4<T>::Transpose(const Matrix4x4& matrixToTranspose)
	{
		Matrix4x4<T> matrix;
		for (int row = 1; row <= 4; ++row)
		{
			for (int col = 1; col <= 4; ++col)
			{
				matrix(col, row) = matrixToTranspose(row, col);
			}
		}
		return matrix;
	}

#pragma endregion METHOD_DEFINITIONS

#pragma region OPERATOR_OVERLOADS

	template <typename T>
	Vector4<T>& Matrix4x4<T>::operator()(const int row)
	{
		assert(row > 0 && row <= m_matrix.size());
		return m_matrix[row - 1];
	}

	template <typename T>
	const Vector4<T>& Matrix4x4<T>::operator()(const int row) const
	{
		assert(row > 0 && row <= m_matrix.size());
		return m_matrix[row - 1];
	}

	template <typename T>
	T& Matrix4x4<T>::operator()(const int row, const int column)
	{
		assert(row > 0 && row <= 4);
		assert(column > 0 && column <= 4);

		return column == 1 ? m_matrix[row - 1].x : column == 2 ? m_matrix[row - 1].y : column == 3 ? m_matrix[row - 1].z : m_matrix[row - 1].w;
	}

	template <typename T>
	const T& Matrix4x4<T>::operator()(const int row, const int column) const
	{
		assert(row > 0 && row <= 4);
		assert(column > 0 && column <= 4);

		return column == 1 ? m_matrix[row - 1].x : column == 2 ? m_matrix[row - 1].y : column == 3 ? m_matrix[row - 1].z : m_matrix[row - 1].w;
	}

	template <typename T>
	void operator+=(Matrix4x4<T>& lhs, const Matrix4x4<T>& rhs)
	{
		for (int i = 1; i <= 4; ++i)
		{
			lhs(i) += rhs(i);
		}
	}

	template <typename T>
	void operator-=(Matrix4x4<T>& lhs, const Matrix4x4<T>& rhs)
	{
		for (int i = 1; i <= 4; ++i)
		{
			lhs(i) -= rhs(i);
		}
	}

	template <typename T>
	void operator*=(Matrix4x4<T>& lhs, const Matrix4x4<T>& rhs)
	{
		Matrix4x4<T> matrix;
		for (int i = 1; i <= 4; ++i)
		{
			for (int j = 1; j <= 4; ++j)
			{
				matrix(i, j) = 0.0f;
				for (int k = 1; k <= 4; ++k)
				{
					matrix(i, j) += lhs(i, k) * rhs(k, j);
				}
			}
		}
		lhs = matrix;
	}

	template <typename T>
	bool operator==(const Matrix4x4<T>& lhs, const Matrix4x4<T>& rhs)
	{
		for (int i = 1; i <= 4; ++i)
		{
			if (lhs(i) != rhs(i))
			{
				return false;
			}
		}
		return true;
	}

	template <typename T>
	Matrix4x4<T> operator+(const Matrix4x4<T>& lhs, const Matrix4x4<T>& rhs)
	{
		Matrix4x4<T> matrix;
		for (int i = 1; i <= 4; ++i)
		{
			matrix(i) = lhs(i) + rhs(i);
		}
		return matrix;
	}

	template <typename T>
	Matrix4x4<T> operator-(const Matrix4x4<T>& lhs, const Matrix4x4<T>& rhs)
	{
		Matrix4x4<T> matrix;
		for (int i = 1; i <= 4; ++i)
		{
			matrix(i) = lhs(i) - rhs(i);
		}
		return matrix;
	}

	template <typename T>
	Matrix4x4<T> operator*(const Matrix4x4<T>& lhs, const Matrix4x4<T>& rhs)
	{
		Matrix4x4<T> matrix;
		for (int i = 1; i <= 4; ++i)
		{
			for (int j = 1; j <= 4; ++j)
			{
				matrix(i, j) = 0.0f;
				for (int k = 1; k <= 4; ++k)
				{
					matrix(i, j) += lhs(i, k) * rhs(k, j);
				}
			}
		}
		return matrix;
	}

	template <typename T>
	Vector4<T> operator*(const Vector4<T>& vector, const Matrix4x4<T>& matrix)
	{
		Vector4<T> result;
		result.x = vector.x * matrix(1, 1) + vector.y * matrix(2, 1) + vector.z * matrix(3, 1) + vector.w * matrix(4, 1);
		result.y = vector.x * matrix(1, 2) + vector.y * matrix(2, 2) + vector.z * matrix(3, 2) + vector.w * matrix(4, 2);
		result.z = vector.x * matrix(1, 3) + vector.y * matrix(2, 3) + vector.z * matrix(3, 3) + vector.w * matrix(4, 3);
		result.w = vector.x * matrix(1, 4) + vector.y * matrix(2, 4) + vector.z * matrix(3, 4) + vector.w * matrix(4, 4);

		return result;
	}

#pragma endregion OPERATOR_OVERLOADS
}
