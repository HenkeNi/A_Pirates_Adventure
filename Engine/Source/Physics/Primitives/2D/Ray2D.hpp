#pragma once
#include "../../../Core/Math/Vectors/Vector2.hpp"

namespace Hi_Engine::Physics
{
	using namespace Math;

	template <class T>
	class Ray2D
	{
	public:
		Ray2D();
		Ray2D(const Vector2<T>& origin, const Vector2<T>& direction);

		void				Init(const Vector2<T>& origin, const Vector2<T>& direction);
		void				InitWith2Points(const Vector2<T>& lhs, const Vector2<T>& rhs);

		const Vector2<T>&	GetOrigin()				const;
		const Vector2<T>&	GetDirection()			const;

		Vector2<T>			GetPointAlongLine(T t)	const;

	private:
		Vector2<T>			m_origin;
		Vector2<T>			m_direction;
	};

#pragma region Method_Definitions

	template <class T>
	Ray2D<T>::Ray2D()
		: m_origin{}, m_direction{}
	{
	}

	template <class T>
	Ray2D<T>::Ray2D(const Vector2<T>& origin, const Vector2<T>& direction)
		: m_origin{ origin }, m_direction{ direction }
	{
	}

	template <class T>
	void Ray2D<T>::Init(const Vector2<T>& origin, const Vector2<T>& direction)
	{
		m_origin = origin;
		m_direction = direction;
	}

	template <class T>
	void Ray2D<T>::InitWith2Points(const Vector2<T>& lhs, const Vector2<T>& rhs)
	{
		m_origin = lhs;
		m_direction = rhs - lhs;
	}

	template <class T>
	const Vector2<T>& Ray2D<T>::GetOrigin() const
	{
		return m_origin;
	}

	template <class T>
	const Vector2<T>& Ray2D<T>::GetDirection() const
	{
		return m_direction;
	}

	template <class T>
	Vector2<T> Ray2D<T>::GetPointAlongLine(T t) const
	{
		return m_origin + (m_direction * t);
	}

#pragma endregion Method_Definitions
}