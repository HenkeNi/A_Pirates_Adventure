#pragma once
#include <cassert>
#include <cmath>

namespace Hi_Engine::Math
{
	// TODO: maybe make struct with free floating functions??
	template <class T>
	class Vector3
	{
	public:
		Vector3();
		Vector3(const T& x, const T& y, const T& z);
		Vector3(const Vector3&)						= default;
		~Vector3()									= default;

		Vector3& operator=(const Vector3&)			= default;
		Vector3  operator-()							const;

		/* -	Methods		- */
		T			LengthSqr()							const;
		T			Length()							const;
		T			Dot(const Vector3& other)			const;
		T			DistanceTo(const Vector3& other)	const;		// TODO: Make static?
		Vector3		DirectionTo(const Vector3& other)	const;
		Vector3		Cross(const Vector3& other)			const;
		Vector3		GetNormalized()						const;
		void		Normalize();

		/* -	Members		- */
		T x;
		T y;
		T z;
	};

	template <class T>
	Vector3(T, T, T) -> Vector3<T>;

#pragma region Method_Definitions

	template <class T>
	Vector3<T>::Vector3()
		: x{ 0 }, y{ 0 }, z{ 0 }
	{
	}

	template <class T>
	Vector3<T>::Vector3(const T& x, const T& y, const T& z)
		: x{ x }, y{ y }, z{ z }
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
	T Vector3<T>::Dot(const Vector3<T>& other) const
	{
		return (x * other.x) + (y * other.y) + (z * other.z);
	}

	template<class T>
	T Vector3<T>::DistanceTo(const Vector3<T>& other) const
	{
		auto direction = Vector3<T>{ other.x - x, other.y - y, other.z - z };
		return direction.Length();
	}

	template<class T>
	Vector3<T> Vector3<T>::DirectionTo(const Vector3<T>& other) const
	{
		Vector3<T> direction = { other.x - x, other.y - y, other.z - z };
		return direction.GetNormalized();
	}

	template <class T>
	Vector3<T> Vector3<T>::Cross(const Vector3<T>& other) const
	{
		return { (y * other.z - z * other.y), (z * other.x - x * other.z), (x * other.y - y * other.x) };
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

#pragma endregion Method_Definitions

#pragma region Operators

	template <class T>
	Vector3<T> Vector3<T>::operator-()	const
	{
		return { -x, -y, -z };
	}

	template <class T>
	Vector3<T> operator+(const Vector3<T>& lhs, const Vector3<T>& rhs)
	{
		return { lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z };
	}

	template <class T>
	Vector3<T> operator-(const Vector3<T>& lhs, const Vector3<T>& rhs)
	{
		return { lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z };
	}

	template <class T>
	Vector3<T> operator*(const Vector3<T>& vector, const T& scalar)
	{
		return { vector.x * scalar,  vector.y * scalar, vector.z * scalar };
	}

	template <class T>
	Vector3<T> operator*(const T& scalar, const Vector3<T>& vector)
	{
		return vector * scalar;
	}

	template <class T>
	Vector3<T> operator/(const Vector3<T>& vector, const T& scalar)
	{
		assert(scalar != 0);
		return { vector.x * (1 / scalar), vector.y * (1 / scalar), vector.z * (1 / scalar) };
	}

	template <class T>
	void operator+=(Vector3<T>& lhs, const Vector3<T>& rhs)
	{
		lhs = lhs + rhs;
	}

	template <class T>
	void operator-=(Vector3<T>& lhs, const Vector3<T>& rhs)
	{
		lhs = lhs - rhs;
	}

	template <class T>
	void operator*=(Vector3<T>& vector, const T& scalar)
	{
		vector = vector * scalar;
	}

	template <class T>
	void operator/=(Vector3<T>& vector, const T& scalar)
	{
		assert(scalar != 0);
		vector = vector / scalar;
	}

	template <class T>
	bool operator==(const Vector3<T>& lhs, const Vector3<T>& rhs)
	{
		return (lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z);
	}

	template <class T>
	bool operator!=(const Vector3<T>& lhs, const Vector3<T>& rhs)
	{
		return !(lhs == rhs);
	}

#pragma endregion Operators
}