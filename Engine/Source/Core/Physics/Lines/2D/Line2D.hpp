#pragma once
#include "Utility/Math/Vectors/Vector2.hpp"

namespace Hi_Engine::Physics
{
	using namespace CommonUtilities;

	template <class T>
	class Line2D
	{
	public:
		Line2D();
		Line2D(const Vector2<T>& aStart, const Vector2<T>& aDirection);

		void				Init(const Vector2<T>& aStart, const Vector2<T>& aDirection);
		void				InitWith2Points(const Vector2<T>& aPoint1, const Vector2<T>& aPoint2);

		const Vector2<T>&	GetStartPoint()			const;
		const Vector2<T>&	GetDirection()			const;

		Vector2<T>			GetPointAlongLine(T t)	const;

	private:
		Vector2<T>			m_startPoint;
		Vector2<T>			m_direction;
	};

#pragma region Constructores

	template <class T>
	Line2D<T>::Line2D()
		: m_startPoint{}, m_direction{}
	{
	}

	template <class T>
	Line2D<T>::Line2D(const Vector2<T>& aStart, const Vector2<T>& aDirection)
		: m_startPoint{ aStart }, m_direction{ aDirection }
	{
	}

#pragma endregion Constructores

#pragma region Method_Definitions

	template <class T>
	void Line2D<T>::Init(const Vector2<T>& aStart, const Vector2<T>& aDirection)
	{
		m_startPoint = aStart;
		m_direction = aDirection;
	}

	template <class T>
	void Line2D<T>::InitWith2Points(const Vector2<T>& aPoint1, const Vector2<T>& aPoint2)
	{
		m_startPoint = aPoint1;
		m_direction = aPoint2 - aPoint1;
	}

	template <class T>
	const Vector2<T>& Line2D<T>::GetStartPoint() const
	{
		return m_startPoint;
	}

	template <class T>
	const Vector2<T>& Line2D<T>::GetDirection() const
	{
		return m_direction;
	}

	template <class T>
	Vector2<T> Line2D<T>::GetPointAlongLine(T t) const
	{
		return m_startPoint + (m_direction * t);
	}

#pragma endregion Method_Definitions
}