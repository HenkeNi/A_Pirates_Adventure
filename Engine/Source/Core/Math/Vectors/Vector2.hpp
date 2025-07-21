#pragma once
#include <cassert>
#include <cmath>

namespace Hi_Engine::Math
{
	// make struct instead? since members are public anyways? make a Math.hpp file? (make functions standalone)
	//template <typename T>
	//struct vec2
	//{
	//	constexpr vec2()
	//		: X{}, Y{}
	//	{
	//	}

	//	constexpr vec2(T x_, T y_)
	//		: x{ x_ }, y{ y_ }
	//	{
	//	}
	//template <typename U1, typename U2>
		//constexpr Vector2(T&& x_, T&& y_);
	//	T x;
	//	T y;
	//};
	//
	//template <typename T>
	//vec2(T, T) -> vec2<T>;


	template <typename T>
	class Vector2
	{
	public:
		constexpr Vector2();
		constexpr Vector2(T x_, T y_);

		Vector2 operator-() const;

		T LengthSqr() const;
		T Length() const;
		T Dot(const Vector2& other)	const;
		T DistanceTo(const Vector2& other) const; 
		T AngleTo(const Vector2& other) const; // TODO...
		Vector2 DirectionTo(const Vector2& other) const; 
		Vector2 GetNormalized() const;
		void Normalize(); 

		T x;
		T y;
	};

	template <typename T>
	Vector2(T, T) -> Vector2<T>;

#pragma region Method_Definitions
 
	template <typename T>
	constexpr Vector2<T>::Vector2()
		: x{}, y{}
	{
	}

	template <typename T>
	constexpr Vector2<T>::Vector2(T x_, T y_)
		: x{ x_ }, y{ y_ }
	{
	}

	template <typename T>
	T Vector2<T>::LengthSqr() const
	{
		return (x * x) + (y * y);
	}

	template <typename T>
	T Vector2<T>::Length() const
	{
		return std::sqrt((x * x) + (y * y));
	}

	template <typename T>
	T Vector2<T>::Dot(const Vector2<T>& other) const
	{
		return (x * other.x) + (y * other.y);
	}

	template <typename T>
	T Vector2<T>::DistanceTo(const Vector2<T>& other) const
	{
		Vector2<T> direction = { other.x - x, other.y - y };
		return direction.Length();
	}

	template <typename T>
	T Vector2<T>::AngleTo(const Vector2<T>& other) const
	{
		return -1; // TODO..
	}

	template <typename T>
	Vector2<T> Vector2<T>::DirectionTo(const Vector2<T>& other) const
	{
		Vector2<T> direction = Vector2<T>{ other.x - x, other.y - y };
		return direction.GetNormalized();
	}

	template <typename T>
	Vector2<T> Vector2<T>::GetNormalized() const
	{
		assert(Length() != 0);	
		auto length = 1 / Length();

		return { x * length, y * length };
	}

	template <typename T>
	void Vector2<T>::Normalize()
	{
		assert(Length() != 0);
		auto length = 1 / Length();

		x *= length;
		y *= length;
	}

#pragma endregion Method_Definitions

#pragma region Operators

	template <typename T>
	Vector2<T> Vector2<T>::operator-() const
	{
		return { -x, -y };
	}

	template <typename T>
	Vector2<T> operator+(const Vector2<T>& lhs, const Vector2<T>& rhs)
	{
		return { lhs.x + rhs.x, lhs.y + rhs.y };
	}

	template <typename T>
	Vector2<T> operator-(const Vector2<T>& lhs, const Vector2<T>& rhs)
	{
		return { lhs.x - rhs.x, lhs.y - rhs.y };
	}

	template <typename T>
	Vector2<T> operator*(const Vector2<T>& vector, const T& scalar)
	{
		return { vector.x * scalar, vector.y * scalar };
	}

	template <typename T>
	Vector2<T> operator*(const T& scalar, const Vector2<T>& vector)
	{
		return vector * scalar;
	}

	template <typename T>
	Vector2<T> operator/(const Vector2<T>& vector, const T& scalar)
	{
		assert(scalar != 0);
		return Vector2<T>(vector.x * (1 / scalar), vector.y * (1 / scalar));
	}

	template <typename T>
	void operator+=(Vector2<T>& lhs, const Vector2<T>& rhs)
	{
		lhs = lhs + rhs;
	}

	template <typename T>
	void operator-=(Vector2<T>& lhs, const Vector2<T>& rhs)
	{
		lhs = lhs - rhs;
	}

	template <typename T>
	void operator*=(Vector2<T>& vector, const T& scalar)
	{
		vector = vector * scalar;
	}

	template <typename T>
	void operator/=(Vector2<T>& vector, const T& scalar)
	{
		assert(scalar != 0);
		vector = vector / scalar;
	}

	template <typename T>
	bool operator==(const Vector2<T>& lhs, const Vector2<T>& rhs)
	{
		return (lhs.x == rhs.x && lhs.y == rhs.y);
	}

	template <typename T>
	bool operator!=(const Vector2<T>& lhs, const Vector2<T>& rhs)
	{
		return !(lhs == rhs);
	}

#pragma endregion Operators
} 