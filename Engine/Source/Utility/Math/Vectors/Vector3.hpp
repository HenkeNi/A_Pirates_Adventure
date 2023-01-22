#pragma once
#include <cassert>
#include <cmath>

namespace CommonUtilities
{
	template <class T>
	class Vector3
	{
	public:
		Vector3();
		Vector3(const T& aX, const T& aY, const T& aZ);
		Vector3(const Vector3&)						= default;
		~Vector3()									= default;

		Vector3& operator=(const Vector3&)			= default;
		Vector3  operator-()							const;

		/* -	Methods		- */
		T			LengthSqr()							const;
		T			Length()							const;
		T			Dot(const Vector3& another)			const;
		T			DistanceTo(const Vector3& another)	const;
		Vector3		DirectionTo(const Vector3& another)	const;
		Vector3		Cross(const Vector3& another)		const;
		Vector3		GetNormalized()						const;
		void		Normalize();

		/* -	Members		- */
		T x;
		T y;
		T z;
	};

#pragma region METHOD_DEFINITIONS

	template <class T>
	Vector3<T>::Vector3()
		: x{ 0 }, y{ 0 }, z{ 0 }
	{
	}

	template <class T>
	Vector3<T>::Vector3(const T& aX, const T& aY, const T& aZ)
		: x{ aX }, y{ aY }, z{ aZ }
	{
	}

	template <class T>
	T Vector3<T>::LengthSqr() const
	{
		return (x * x) + (y * y) + (z * z);
	}

	template <class T>
	T Vector3<T>::Length() const
	{
		return std::sqrt((x * x) + (y * y) + (z * z));
	}

	template <class T>
	T Vector3<T>::Dot(const Vector3<T>& another) const
	{
		return (x * another.x) + (y * another.y) + (z * another.z);
	}

	template<class T>
	T Vector3<T>::DistanceTo(const Vector3& another) const
	{
		Vector3<T> direction = { another.x - x, another.y - y };
		return direction.Length();
	}

	template<class T>
	Vector3<T> Vector3<T>::DirectionTo(const Vector3& another) const
	{
		Vector3<T> direction = { another.x - x, another.y - y };
		return direction.GetNormalized();
	}

	template <class T>
	Vector3<T> Vector3<T>::Cross(const Vector3& another) const
	{
		return { (y * another.z - z * another.y), (z * another.x - x * another.z), (x * another.y - y * another.x) };
	}

	template <class T>
	Vector3<T> Vector3<T>::GetNormalized() const
	{
		assert(Length() != 0);
		auto length = 1 / Length();

		return { x * length, y * length, z * length };
	}

	template <class T>
	void Vector3<T>::Normalize()
	{
		assert(Length() != 0);

		auto length = 1 / Length();
		x *= length;
		y *= length;
		z *= length;
	}

#pragma endregion METHOD_DEFINITIONS

#pragma region OVERLOADED_OPERATORS

	template <class T>
	Vector3<T> Vector3<T>::operator-()	const
	{
		return { -x, -y, -z };
	}

	template <class T>
	Vector3<T> operator+(const Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		return { aVector0.x + aVector1.x, aVector0.y + aVector1.y, aVector0.z + aVector1.z };
	}

	template <class T>
	Vector3<T> operator-(const Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		return { aVector0.x - aVector1.x, aVector0.y - aVector1.y, aVector0.z - aVector1.z };
	}

	template <class T>
	Vector3<T> operator*(const Vector3<T>& aVector, const T& aScalar)
	{
		return { aVector.x * aScalar,  aVector.y * aScalar, aVector.z * aScalar };
	}

	template <class T>
	Vector3<T> operator*(const T& aScalar, const Vector3<T>& aVector)
	{
		return aVector * aScalar;
	}

	template <class T>
	Vector3<T> operator/(const Vector3<T>& aVector, const T& aScalar)
	{
		assert(aScalar != 0);
		return { aVector.x * (1 / aScalar), aVector.y * (1 / aScalar), aVector.z * (1 / aScalar) };
	}

	template <class T>
	void operator+=(Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		aVector0 = aVector0 + aVector1;
	}

	template <class T>
	void operator-=(Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		aVector0 = aVector0 - aVector1;
	}

	template <class T>
	void operator*=(Vector3<T>& aVector, const T& aScalar)
	{
		aVector = aVector * aScalar;
	}

	template <class T>
	void operator/=(Vector3<T>& aVector, const T& aScalar)
	{
		assert(aScalar != 0);
		aVector = aVector / aScalar;
	}

	template <class T>
	bool operator==(const Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		return (aVector0.x == aVector1.x && aVector0.y == aVector1.y && aVector0.z == aVector1.z);
	}

	template <class T>
	bool operator!=(const Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		return !(aVector0 == aVector1);
	}

#pragma endregion OVERLOADED_OPERATORS
}