#pragma once
#include <cassert>
#include <cmath>

namespace CommonUtilities
{
	template <class T>
	class Vector4
	{
	public:
		Vector4();
		Vector4(const T& aX, const T& aY, const T& aZ, const T& aW);
		Vector4(const Vector4&)					= default;
		~Vector4()								= default;

		Vector4& operator=(const Vector4&)		= default;
		Vector4  operator-()						const;

		/* -	Methods		- */
		T			LengthSqr()						const;
		T			Length()						const;
		T			Dot(const Vector4 & aVector)	const;
		Vector4		GetNormalized()					const;
		void		Normalize();

		/* - Members -*/
		T x;
		T y;
		T z;
		T w;
	};

#pragma region METHOD_DEFINITIONS

	template <class T>
	Vector4<T>::Vector4()
		: x{ 0 }, y{ 0 }, z{ 0 }, w{ 0 }
	{
	}

	template <class T>
	Vector4<T>::Vector4(const T& aX, const T& aY, const T& aZ, const T& aW)
		: x{ aX }, y{ aY }, z{ aZ }, w{ aW }
	{
	}

	template <class T>
	T Vector4<T>::LengthSqr() const
	{
		return (x * x) + (y * y) + (z * z) + (w * w);
	}

	template <class T>
	T Vector4<T>::Length() const
	{
		return std::sqrt((x * x) + (y * y) + (z * z) + (w * w));
	}

	template <class T>
	T Vector4<T>::Dot(const Vector4<T>& aVector) const
	{
		return (x * aVector.x) + (y * aVector.y) + (z * aVector.z) + (w * aVector.w);
	}

	template <class T>
	Vector4<T> Vector4<T>::GetNormalized() const
	{
		assert(Length() != 0);
		auto length = 1 / Length();

		return { x * length, y * Length, z * Length, w * Length };
	}

	template <class T>
	void Vector4<T>::Normalize()
	{
		assert(Length() != 0);

		auto length = 1 / Length();
		x *= length;
		y *= length;
		z *= length;
		w *= length;
	}

#pragma endregion METHOD_DEFINITIONS

#pragma region OVERLOADED_OPERATORS

	template <class T>
	Vector4<T> Vector4<T>::operator-() const
	{
		return { -x, -y, -z, -w };
	}

	template <class T>
	Vector4<T> operator+(const Vector4<T>& aVector0, const Vector4<T>& aVector1)
	{
		return { aVector0.x + aVector1.x, aVector0.y + aVector1.y, aVector0.z + aVector1.z, aVector0.w + aVector1.w };
	}

	template <class T>
	Vector4<T> operator-(const Vector4<T>& aVector0, const Vector4<T>& aVector1)
	{
		return { aVector0.x - aVector1.x, aVector0.y - aVector1.y, aVector0.z - aVector1.z, aVector0.w - aVector1.w };
	}

	template <class T>
	Vector4<T> operator*(const Vector4<T>& aVector, const T& aScalar)
	{
		return { aVector.x * aScalar,  aVector.y * aScalar, aVector.z * aScalar, aVector.w * aScalar };
	}

	template <class T>
	Vector4<T> operator*(const T& aScalar, const Vector4<T>& aVector)
	{
		return aVector * aScalar;
	}

	template <class T>
	Vector4<T> operator/(const Vector4<T>& aVector, const T& aScalar)
	{
		assert(aScalar != 0);
		return { aVector.x * (1 / aScalar), aVector.y * (1 / aScalar), aVector.z * (1 / aScalar), aVector.w * (1 / aScalar) };
	}

	template <class T>
	void operator+=(Vector4<T>& aVector0, const Vector4<T>& aVector1)
	{
		aVector0 = aVector0 + aVector1;
	}

	template <class T>
	void operator-=(Vector4<T>& aVector0, const Vector4<T>& aVector1)
	{
		aVector0 = aVector0 - aVector1;
	}

	template <class T>
	void operator*=(Vector4<T>& aVector, const T& aScalar)
	{
		aVector = aVector * aScalar;
	}

	template <class T>
	void operator/=(Vector4<T>& aVector, const T& aScalar)
	{
		assert(aScalar != 0);
		aVector = aVector / aScalar;
	}

	template <class T>
	bool operator==(const Vector4<T>& aVector0, const Vector4<T>& aVector1)
	{
		return (aVector0.x == aVector1.x &&
			aVector0.y == aVector1.y &&
			aVector0.z == aVector1.z &&
			aVector0.w == aVector1.w);
	}

	template <class T>
	bool operator!=(const Vector4<T>& aVector0, const Vector4<T>& aVector1)
	{
		return !(aVector0 == aVector1);
	}

#pragma endregion OVERLOADED_OPERATORS
}