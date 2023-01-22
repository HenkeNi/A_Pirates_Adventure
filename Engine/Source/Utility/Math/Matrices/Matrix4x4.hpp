#pragma once
#include "../Vectors/Vector.hpp"
#include <array>

namespace CommonUtilities
{
	template <typename T>
	class Matrix4x4
	{
	public:
		Matrix4x4();
		Matrix4x4(const Matrix4x4& aMatrix);

		Matrix4x4&			operator=(const Matrix4x4&)					= default;

		Vector4<T>&			operator()(const int aRow);
		const Vector4<T>&	operator()(const int aRow)						const;

		T&					operator()(const int aRow, const int aColumn);
		const T&			operator()(const int aRow, const int aColumn)	const;

		static Matrix4x4	CreateRotationAroundX(T anAngleInRadians);
		static Matrix4x4	CreateRotationAroundY(T anAngleInRadians);
		static Matrix4x4	CreateRotationAroundZ(T anAngleInRadians);

		static Matrix4x4	GetFastInverse(const Matrix4x4<T>& aTransform);
		static Matrix4x4	Transpose(const Matrix4x4& aMatrixToTranspose);

	private:
		std::array<Vector4<T>, 4> myMatrix;

	};

#pragma region METHOD_DEFINITIONS

	/* - Creates the identity matrix - */
	template <typename T>
	Matrix4x4<T>::Matrix4x4()
	{
		myMatrix[0] = { 1.f, 0.f, 0.f, 0.f };
		myMatrix[1] = { 0.f, 1.f, 0.f, 0.f };
		myMatrix[2] = { 0.f, 0.f, 1.f, 0.f };
		myMatrix[3] = { 0.f, 0.f, 0.f, 1.f };
	}

	template <typename T>
	Matrix4x4<T>::Matrix4x4(const Matrix4x4& aMatrix)
		: myMatrix{ aMatrix.myMatrix }
	{
	}

	template <typename T>
	Matrix4x4<T> Matrix4x4<T>::CreateRotationAroundX(T anAngleInRadians)
	{
		Matrix4x4<T> matrix;
		matrix.myMatrix[0] = { 1.f, 0.f, 0.f, 0.f };
		matrix.myMatrix[1] = { 0.f,  cos(anAngleInRadians), sin(anAngleInRadians), 0.f };
		matrix.myMatrix[2] = { 0.f, -sin(anAngleInRadians), cos(anAngleInRadians), 0.f };
		matrix.myMatrix[3] = { 0.f, 0.f, 0.f, 1.f };

		return matrix;
	}

	template <typename T>
	Matrix4x4<T> Matrix4x4<T>::CreateRotationAroundY(T anAngleInRadians)
	{
		Matrix4x4<T> matrix;
		matrix.myMatrix[0] = { cos(anAngleInRadians), 0.f, -sin(anAngleInRadians), 0.f };
		matrix.myMatrix[1] = { 0.f, 1.f, 0.f, 0.f };
		matrix.myMatrix[2] = { sin(anAngleInRadians), 0.f, cos(anAngleInRadians), 0.f };
		matrix.myMatrix[3] = { 0.f, 0.f, 0.f, 1.f };

		return matrix;
	}

	template <typename T>
	Matrix4x4<T> Matrix4x4<T>::CreateRotationAroundZ(T anAngleInRadians)
	{
		Matrix4x4<T> matrix;
		matrix.myMatrix[0] = { cos(anAngleInRadians), sin(anAngleInRadians), 0.f, 0.f };
		matrix.myMatrix[1] = { -sin(anAngleInRadians), cos(anAngleInRadians), 0.f, 0.f };
		matrix.myMatrix[2] = { 0.f, 0.f, 1.f, 0.f };
		matrix.myMatrix[3] = { 0.f, 0.f, 0.f, 1.f };

		return matrix;
	}

	template <typename T>
	Matrix4x4<T> Matrix4x4<T>::GetFastInverse(const Matrix4x4<T>& aTransform)
	{
		// Copy the 3x3 part of aTransform
		Matrix4x4<T> rotationMatrix = aTransform;
		rotationMatrix(4) = { 0.f, 0.f, 0.f, 1.f };

		rotationMatrix = Transpose(rotationMatrix);

		Matrix4x4<T> matrix;
		for (int i = 1; i < 4; ++i)
		{
			matrix(4, i) = aTransform(4, i) * -1;
		}
		return matrix * rotationMatrix;
	}

	template <typename T>
	Matrix4x4<T> Matrix4x4<T>::Transpose(const Matrix4x4& aMatrixToTranspose)
	{
		Matrix4x4<T> matrix;
		for (int row = 1; row <= 4; ++row)
		{
			for (int col = 1; col <= 4; ++col)
			{
				matrix(col, row) = aMatrixToTranspose(row, col);
			}
		}
		return matrix;
	}

#pragma endregion METHOD_DEFINITIONS

#pragma region OPERATOR_OVERLOADS

	template <typename T>
	Vector4<T>& Matrix4x4<T>::operator()(const int aRow)
	{
		assert(aRow > 0 && aRow <= myMatrix.size());
		return myMatrix[aRow - 1];
	}

	template <typename T>
	const Vector4<T>& Matrix4x4<T>::operator()(const int aRow) const
	{
		assert(aRow > 0 && aRow <= myMatrix.size());
		return myMatrix[aRow - 1];
	}

	template <typename T>
	T& Matrix4x4<T>::operator()(const int aRow, const int aColumn)
	{
		assert(aRow > 0 && aRow <= 4);
		assert(aColumn > 0 && aColumn <= 4);

		return aColumn == 1 ? myMatrix[aRow - 1].x : aColumn == 2 ? myMatrix[aRow - 1].y : aColumn == 3 ? myMatrix[aRow - 1].z : myMatrix[aRow - 1].w;
	}

	template <typename T>
	const T& Matrix4x4<T>::operator()(const int aRow, const int aColumn) const
	{
		assert(aRow > 0 && aRow <= 4);
		assert(aColumn > 0 && aColumn <= 4);

		return aColumn == 1 ? myMatrix[aRow - 1].x : aColumn == 2 ? myMatrix[aRow - 1].y : aColumn == 3 ? myMatrix[aRow - 1].z : myMatrix[aRow - 1].w;
	}

	template <typename T>
	void operator+=(Matrix4x4<T>& aMatrix0, const Matrix4x4<T>& aMatrix1)
	{
		for (int i = 1; i <= 4; ++i)
		{
			aMatrix0(i) += aMatrix1(i);
		}
	}

	template <typename T>
	void operator-=(Matrix4x4<T>& aMatrix0, const Matrix4x4<T>& aMatrix1)
	{
		for (int i = 1; i <= 4; ++i)
		{
			aMatrix0(i) -= aMatrix1(i);
		}
	}

	template <typename T>
	void operator*=(Matrix4x4<T>& aMatrix0, const Matrix4x4<T>& aMatrix1)
	{
		Matrix4x4<T> matrix;
		for (int i = 1; i <= 4; ++i)
		{
			for (int j = 1; j <= 4; ++j)
			{
				matrix(i, j) = 0.0f;
				for (int k = 1; k <= 4; ++k)
				{
					matrix(i, j) += aMatrix0(i, k) * aMatrix1(k, j);
				}
			}
		}
		aMatrix0 = matrix;
	}

	template <typename T>
	bool operator==(const Matrix4x4<T>& aMatrix0, const Matrix4x4<T>& aMatrix1)
	{
		for (int i = 1; i <= 4; ++i)
		{
			if (aMatrix0(i) != aMatrix1(i))
			{
				return false;
			}
		}
		return true;
	}

	template <typename T>
	Matrix4x4<T> operator+(const Matrix4x4<T>& aMatrix0, const Matrix4x4<T>& aMatrix1)
	{
		Matrix4x4<T> matrix;
		for (int i = 1; i <= 4; ++i)
		{
			matrix(i) = aMatrix0(i) + aMatrix1(i);
		}
		return matrix;
	}

	template <typename T>
	Matrix4x4<T> operator-(const Matrix4x4<T>& aMatrix0, const Matrix4x4<T>& aMatrix1)
	{
		Matrix4x4<T> matrix;
		for (int i = 1; i <= 4; ++i)
		{
			matrix(i) = aMatrix0(i) - aMatrix1(i);
		}
		return matrix;
	}

	template <typename T>
	Matrix4x4<T> operator*(const Matrix4x4<T>& aMatrix0, const Matrix4x4<T>& aMatrix1)
	{
		Matrix4x4<T> matrix;
		for (int i = 1; i <= 4; ++i)
		{
			for (int j = 1; j <= 4; ++j)
			{
				matrix(i, j) = 0.0f;
				for (int k = 1; k <= 4; ++k)
				{
					matrix(i, j) += aMatrix0(i, k) * aMatrix1(k, j);
				}
			}
		}
		return matrix;
	}

	template <typename T>
	Vector4<T> operator*(const Vector4<T>& aVector, const Matrix4x4<T>& aMatrix)
	{
		Vector4<T> result;
		result.x = aVector.x * aMatrix(1, 1) + aVector.y * aMatrix(2, 1) + aVector.z * aMatrix(3, 1) + aVector.w * aMatrix(4, 1);
		result.y = aVector.x * aMatrix(1, 2) + aVector.y * aMatrix(2, 2) + aVector.z * aMatrix(3, 2) + aVector.w * aMatrix(4, 2);
		result.z = aVector.x * aMatrix(1, 3) + aVector.y * aMatrix(2, 3) + aVector.z * aMatrix(3, 3) + aVector.w * aMatrix(4, 3);
		result.w = aVector.x * aMatrix(1, 4) + aVector.y * aMatrix(2, 4) + aVector.z * aMatrix(3, 4) + aVector.w * aMatrix(4, 4);

		return result;
	}

#pragma endregion OPERATOR_OVERLOADS
}
