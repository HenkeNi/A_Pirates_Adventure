#pragma once
#include "../Vectors/Vector2.hpp"

namespace Hi_Engine::Geometry
{
	using namespace Math;

	// RENAEM Line2D?
	template <class T>
	class LineSegment2D
	{
	public:
		LineSegment2D();
		LineSegment2D(const Vector2<T>& start, const Vector2<T>& end);

		void Init(const Vector2<T>& start, const Vector2<T>& end);
		bool IsOnLine(const Vector2<T>& point) const;

		const Vector2<T>& GetStartPoint() const;
		const Vector2<T>& GetEndPoint()	const;

		Vector2<T> GetPointAlongLine(T t) const;
		Vector2<T> GetDirection() const;

		T GetLength() const;
		T GetLengthSqr() const;

	private:
		Vector2<T> m_startPoint;
		Vector2<T> m_endPoint;
	};

#pragma region Method_Definitions

	template <class T>
	LineSegment2D<T>::LineSegment2D()
		: m_startPoint{}, m_endPoint{}
	{
	}

	template <class T>
	LineSegment2D<T>::LineSegment2D(const Vector2<T>& start, const Vector2<T>& end)
		: m_startPoint{ start }, m_endPoint{ end }
	{
	}

	template <class T>
	void LineSegment2D<T>::Init(const Vector2<T>& start, const Vector2<T>& end)
	{
		m_startPoint = start;
		m_endPoint = end;
	}

	template <class T>
	bool LineSegment2D<T>::IsOnLine(const Vector2<T>& point) const
	{
		if (point == m_startPoint || point == m_endPoint)
			return true;	

		/* Calculate differences in x and y */
		T diffX = (m_endPoint.x - m_startPoint.x);
		T diffY = (m_endPoint.y - m_startPoint.y);

		/* Calculate slope and y-intercept */
		T m = diffY / diffX;
		T b = m_startPoint.y - m * m_startPoint.x;

		/* Check line equation */
		return IsNearlyEqual(point.y, m * point.x + b);
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

	template <class T>
	T LineSegment2D<T>::GetLength() const
	{
		return sqrtf(m_startPoint.Dot(m_endPoint));
	}

	template <class T>
	T LineSegment2D<T>::GetLengthSqr() const
	{
		return m_startPoint.Dot(m_endPoint);	
	}

#pragma endregion Method_Definitions
}