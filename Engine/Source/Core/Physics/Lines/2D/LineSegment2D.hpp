#pragma once
#include "Utility/Math/Vectors/Vector2.hpp"

namespace Hi_Engine::Physics
{
	using namespace CommonUtilities;

	template <class T>
	class LineSegment2D
	{
	public:
		LineSegment2D();
		LineSegment2D(const Vector2<T>& aStart, const Vector2<T>& anEnd);

		void				Init(const Vector2<T>& aStart, const Vector2<T>& anEnd);

		const Vector2<T>&	GetStartPoint()			const;
		const Vector2<T>&	GetEndPoint()			const;

		Vector2<T>			GetPointAlongLine(T t)	const;
		Vector2<T>			GetDirection()			const;

	private:
		Vector2<T>			m_startPoint;
		Vector2<T>			m_endPoint;
	};

#pragma region Constructors

	template <class T>
	LineSegment2D<T>::LineSegment2D()
		: m_startPoint{}, m_endPoint{}
	{
	}

	template <class T>
	LineSegment2D<T>::LineSegment2D(const Vector2<T>& aStart, const Vector2<T>& anEnd)
		: m_startPoint{ aStart }, m_endPoint{ anEnd }
	{
	}

#pragma endregion Constructors

#pragma region Method_Definitions

	template <class T>
	void LineSegment2D<T>::Init(const Vector2<T>& aStart, const Vector2<T>& anEnd)
	{
		m_startPoint = aStart;
		m_endPoint = anEnd;
	}

	template <class T>
	const Vector2<T>& LineSegment2D<T>::GetStartPoint() const
	{
		return m_startPoint;
	}
	
	template <class T>
	const Vector2<T>& LineSegment2D<T>::GetEndPoint() const
	{
		return m_endPoint;
	}

	template <class T>
	Vector2<T> LineSegment2D<T>::GetPointAlongLine(T t)	const
	{
		auto direction = m_endPoint - m_startPoint;
		return m_startPoint + (direction * t);
	}

	template <class T>
	Vector2<T> LineSegment2D<T>::GetDirection() const
	{
		return m_endPoint - m_startPoint;
	}

#pragma endregion Method_Definitions
}