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
		Vector4(const T& x, const T& y, const T& z, const T& w);
		Vector4(const Vector4&)					= default;
		~Vector4()								= default;

		Vector4& operator=(const Vector4&)		= default;
		Vector4  operator-()						const;

		/* -	Methods		- */
		T			LengthSqr()						const;
		T			Length()						const;
		T			Dot(const Vector4 & vector)		const;
		Vector4		GetNormalized()					const;
		void		Normalize();

		/* - Members -*/
		T x;
		T y;
		T z;
		T w;
	};

#pragma region Method_Definitions

	template <class T>
	Vector4<T>::Vector4()
		: x{ 0 }, y{ 0 }, z{ 0 }, w{ 0 }
	{
	}

	template <class T>
	Vector4<T>::Vector4(const T& x, const T& y, const T& z, const T& w)
		: x{ x }, y{ y }, z{ z }, w{ w }
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
	T Vector4<T>::Dot(const Vector4<T>& vector) const
	{
		return (x * vector.x) + (y * vector.y) + (z * vector.z) + (w * vector.w);
	}

	template <class T>
	Vector4<T> Vector4<T>::GetNormalized() const
	{
		assert(Length() != 0);
		auto length = 1 / Length();

		return { x * length, y * length, z * length, w * length };
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

#pragma endregion Method_Definitions

#pragma region Operators

	template <class T>
	Vector4<T> Vector4<T>::operator-() const
	{
		return { -x, -y, -z, -w };
	}

	template <class T>
	Vector4<T> operator+(const Vector4<T>& lhs, const Vector4<T>& rhs)
	{
		return { lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w };
	}

	template <class T>
	Vector4<T> operator-(const Vector4<T>& lhs, const Vector4<T>& rhs)
	{
		return { lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w };
	}

	template <class T>
	Vector4<T> operator*(const Vector4<T>& vector, const T& scalar)
	{
		return { vector.x * scalar,  vector.y * scalar, vector.z * scalar, vector.w * scalar };
	}

	template <class T>
	Vector4<T> operator*(const T& scalar, const Vector4<T>& vector)
	{
		return vector * scalar;
	}

	template <class T>
	Vector4<T> operator/(const Vector4<T>& vector, const T& scalar)
	{
		assert(scalar != 0);
		return { vector.x * (1 / scalar), vector.y * (1 / scalar), vector.z * (1 / scalar), vector.w * (1 / scalar) };
	}

	template <class T>
	void operator+=(Vector4<T>& lhs, const Vector4<T>& rhs)
	{
		lhs = lhs + rhs;
	}

	template <class T>
	void operator-=(Vector4<T>& lhs, const Vector4<T>& rhs)
	{
		lhs = lhs - rhs;
	}

	template <class T>
	void operator*=(Vector4<T>& vector, const T& scalar)
	{
		vector = vector * scalar;
	}

	template <class T>
	void operator/=(Vector4<T>& vector, const T& scalar)
	{
		assert(scalar != 0);
		vector = vector / scalar;
	}

	template <class T>
	bool operator==(const Vector4<T>& lhs, const Vector4<T>& rhs)
	{
		return (lhs.x == rhs.x &&
			lhs.y == rhs.y &&
			lhs.z == rhs.z &&
			lhs.w == rhs.w);
	}

	template <class T>
	bool operator!=(const Vector4<T>& lhs, const Vector4<T>& rhs)
	{
		return !(lhs == rhs);
	}

#pragma endregion Operators
}