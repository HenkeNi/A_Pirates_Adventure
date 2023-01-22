#pragma once
#include "Matrix4x4.hpp"
#include "../Vectors/Vector.hpp"
#include <array>


namespace CommonUtilities
{
	template <typename T>
	class Matrix3x3
	{
	public:
		Matrix3x3();
		Matrix3x3(const Matrix3x3& aMatrix);
		Matrix3x3(const Matrix4x4<T>& aMatrix);

		Matrix3x3&			operator=(const Matrix3x3&)					= default;
		Matrix3x3&			operator=(const Matrix4x4<T>& aMatrix);

		Vector3<T>&			operator()(const int aRow);
		const Vector3<T>&	operator()(const int aRow)						const;

		T&					operator()(const int aRow, const int aColumn);
		const T&			operator()(const int aRow, const int aColumn)	const;

		static Matrix3x3	CreateRotationAroundX(T anAngleInRadians);
		static Matrix3x3	CreateRotationAroundY(T anAngleInRadians);
		static Matrix3x3	CreateRotationAroundZ(T anAngleInRadians);
		static Matrix3x3	Transpose(const Matrix3x3& aMatrixToTranspose);

	private:
		std::array<Vector3<T>, 3> myMatrix;
	};

#pragma region METHOD_DEFINITIONS

	/* - Creates an identity matrix - */
	template <typename T>
	Matrix3x3<T>::Matrix3x3()
	{
		myMatrix[0] = { 1.f, 0.f, 0.f };
		myMatrix[1] = { 0.f, 1.f, 0.f };
		myMatrix[2] = { 0.f, 0.f, 1.f };
	}

	/* - Copy constructor - */
	template <typename T>
	Matrix3x3<T>::Matrix3x3(const Matrix3x3<T>& aMatrix)
		: myMatrix{ aMatrix.myMatrix }
	{
	}

	/* - Copies the top left 3x3 part of the 4x4 Matrix - */
	template <typename T>
	Matrix3x3<T>::Matrix3x3(const Matrix4x4<T>& aMatrix)
	{
		*this = aMatrix;
	}

	/* - Creates a rotation matrice around x-axis - */
	template <typename T>
	Matrix3x3<T> Matrix3x3<T>::CreateRotationAroundX(T anAngleInRadians)
	{
		Matrix3x3<T> matrix;
		matrix.myMatrix[0] = { 1.f, 0.f, 0.f };
		matrix.myMatrix[1] = { 0.f, cos(anAngleInRadians), sin(anAngleInRadians) };
		matrix.myMatrix[2] = { 0.f, -sin(anAngleInRadians), cos(anAngleInRadians) };

		return matrix;
	}

	/* - Creates a rotation matrice around y-axis - */
	template <typename T>
	Matrix3x3<T> Matrix3x3<T>::CreateRotationAroundY(T anAngleInRadians)
	{
		Matrix3x3<T> matrix;
		matrix.myMatrix[0] = { cos(anAngleInRadians), 0, -sin(anAngleInRadians) };
		matrix.myMatrix[1] = { 0, 1, 0 };
		matrix.myMatrix[2] = { sin(anAngleInRadians), 0, cos(anAngleInRadians) };

		return matrix;
	}

	/* - Creates a rotation matrice around z-axis - */
	template <typename T>
	Matrix3x3<T> Matrix3x3<T>::CreateRotationAroundZ(T anAngleInRadians)
	{
		Matrix3x3<T> matrix;
		matrix.myMatrix[0] = { cos(anAngleInRadians), sin(anAngleInRadians), 0 };
		matrix.myMatrix[1] = { -sin(anAngleInRadians), cos(anAngleInRadians), 0 };
		matrix.myMatrix[2] = { 0, 0, 1 };

		return matrix;
	}

	/* - Transpose swaps the places between columns and rows - */
	template <typename T>
	Matrix3x3<T> Matrix3x3<T>::Transpose(const Matrix3x3<T>& aMatrixToTranspose)
	{
		Matrix3x3<T> matrix;
		for (int row = 1; row <= 3; ++row)
		{
			for (int col = 1; col <= 3; ++col)
			{
				matrix(col, row) = aMatrixToTranspose(row, col);
			}
		}
		return matrix;
	}

#pragma endregion METHOD_DEFINITIONS

#pragma region OPERATOR_OVERLOADS

	template <typename T>
	Matrix3x3<T>& Matrix3x3<T>::operator=(const Matrix4x4<T>& aMatrix)
	{
		for (int i = 1; i <= 3; ++i)
		{
			for (int j = 1; j <= 3; ++j)
			{
				(*this)(i, j) = aMatrix(i, j);
			}
		}
		return *this;
	}

	/* - Access Vector3 at specified row - */
	template <typename T>
	Vector3<T>& Matrix3x3<T>::operator()(const int aRow)
	{
		assert(aRow > 0 && aRow <= myMatrix.size());
		return myMatrix[aRow - 1];
	}

	/* - Access Vector3 at specified row (read only) - */
	template <typename T>
	const Vector3<T>& Matrix3x3<T>::operator()(const int aRow) const
	{
		assert(aRow > 0 && aRow <= myMatrix.size());
		return myMatrix[aRow - 1];
	}

	/* - Access element at specified position - */
	template <typename T>
	T& Matrix3x3<T>::operator()(const int aRow, const int aColumn)
	{
		assert(aRow > 0 && aRow <= 3); // myMatrix.size());
		assert(aColumn > 0 && aColumn <= 3);

		return aColumn == 1 ? myMatrix[aRow - 1].x : aColumn == 2 ? myMatrix[aRow - 1].y : myMatrix[aRow - 1].z;
	}

	/* - Access element at specified position (read only) - */
	template <typename T>
	const T& Matrix3x3<T>::operator()(const int aRow, const int aColumn) const
	{
		assert(aRow > 0 && aRow <= 3);
		assert(aColumn > 0 && aColumn <= 3);

		return aColumn == 1 ? myMatrix[aRow - 1].x : aColumn == 2 ? myMatrix[aRow - 1].y : myMatrix[aRow - 1].z;
	}

	template <typename T>
	void operator+=(Matrix3x3<T>& aMatrix0, const Matrix3x3<T>& aMatrix1)
	{
		for (int i = 1; i <= 3; ++i)
		{
			aMatrix0(i) += aMatrix1(i);
		}
	}

	template <typename T>
	void operator-=(Matrix3x3<T>& aMatrix0, const Matrix3x3<T>& aMatrix1)
	{
		for (int i = 1; i <= 3; ++i)
		{
			aMatrix0(i) -= aMatrix1(i);
		}
	}

	template <typename T>
	void operator*=(Matrix3x3<T>& aMatrix0, const Matrix3x3<T>& aMatrix1)
	{
		Matrix3x3<T> matrix;
		for (int i = 1; i <= 3; ++i)
		{
			for (int j = 1; j <= 3; ++j)
			{
				matrix(i, j) = 0.0f;
				for (int k = 1; k <= 3; ++k)
				{
					matrix(i, j) += aMatrix0(i, k) * aMatrix1(k, j);
				}
			}
		}
		aMatrix0 = matrix;
	}

	template <typename T>
	bool operator==(const Matrix3x3<T>& aMatrix0, const Matrix3x3<T>& aMatrix1)
	{
		for (int i = 1; i <= 3; ++i)
		{
			if (aMatrix0(i) != aMatrix1(i))
			{
				return false;
			}
		}
		return true;
	}

	template <typename T>
	Matrix3x3<T> operator+(const Matrix3x3<T>& aMatrix0, const Matrix3x3<T>& aMatrix1)
	{
		Matrix3x3<T> matrix;
		for (int i = 1; i <= 3; ++i)
		{
			matrix(i) = aMatrix0(i) + aMatrix1(i);
		}
		return matrix;
	}

	template <typename T>
	Matrix3x3<T> operator-(const Matrix3x3<T>& aMatrix0, const Matrix3x3<T>& aMatrix1)
	{
		Matrix3x3<T> matrix;
		for (int i = 1; i <= 3; ++i)
		{
			matrix(i) = aMatrix0(i) - aMatrix1(i);
		}
		return matrix;
	}

	template <typename T>
	Matrix3x3<T> operator*(const Matrix3x3<T>& aMatrix0, const Matrix3x3<T>& aMatrix1)
	{
		Matrix3x3<T> matrix;
		for (int i = 1; i <= 3; ++i)
		{
			for (int j = 1; j <= 3; ++j)
			{
				matrix(i, j) = 0.0f;
				for (int k = 1; k <= 3; ++k)
				{
					matrix(i, j) += aMatrix0(i, k) * aMatrix1(k, j);
				}
			}
		}
		return matrix;
	}

	template <typename T>
	Vector3<T> operator*(const Vector3<T>& aVector, const Matrix3x3<T>& aMatrix)
	{
		Vector3<T> result;
		result.x = aVector.x * aMatrix(1, 1) + aVector.y * aMatrix(2, 1) + aVector.z * aMatrix(3, 1);
		result.y = aVector.x * aMatrix(1, 2) + aVector.y * aMatrix(2, 2) + aVector.z * aMatrix(3, 2);
		result.z = aVector.x * aMatrix(1, 3) + aVector.y * aMatrix(2, 3) + aVector.z * aMatrix(3, 3);

		return result;
	}

#pragma endregion OPERATOR_OVERLOADS
}
