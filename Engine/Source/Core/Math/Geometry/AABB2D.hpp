#pragma once
#include "../Vectors/Vector2.hpp"

namespace Hi_Engine::Geometry
{
	using namespace Math;

	template <class T>
	class AABB2D
	{
	public:
		AABB2D();
		AABB2D(const Vector2<T>& min, const Vector2<T>& max);

		void					Init(const Vector2<T>& min, const Vector2<T>& max);
		bool					IsInside(const Vector2<T>& point)							const;

		const Vector2<T>&		GetMinPoint()												const;
		const Vector2<T>&		GetMaxPoint()												const;
		Vector2<T>				GetCenter()													const;
		Vector2<T>				GetSize()													const;

		T						GetWidth()													const;
		T						GetHeight()													const;

	private:
		Vector2<T>				m_minPoint;
		Vector2<T>				m_maxPoint;
	};

#pragma region Constructores

	template <class T>
	AABB2D<T>::AABB2D()
		: m_minPoint{}, m_maxPoint{}
	{
	}

	template <class T>
	AABB2D<T>::AABB2D(const Vector2<T>& min, const Vector2<T>& max)
		: m_minPoint{ min }, m_maxPoint{ max }
	{
	}

#pragma endregion Constructors

#pragma region Method_Definitions

	template <class T>
	void AABB2D<T>::Init(const Vector2<T>& min, const Vector2<T>& max)
	{
		m_minPoint = min;
		m_maxPoint = max;
	}

	template <class T>
	bool AABB2D<T>::IsInside(const Vector2<T>& point) const
	{
		if (m_minPoint.x > point.x) { return false; }
		if (m_minPoint.y > point.y) { return false; }

		if (m_maxPoint.x < point.x) { return false; }
		if (m_maxPoint.y < point.y) { return false; }

		return true;
	}

	template <class T>
	const Vector2<T>& AABB2D<T>::GetMinPoint() const
	{
		return m_minPoint;
	}

	template <class T>
	const Vector2<T>& AABB2D<T>::GetMaxPoint() const
	{
		return m_maxPoint;
	}

	template <class T>
	Vector2<T> AABB2D<T>::GetCenter() const
	{
		auto center = Vector2<T>{ (m_minPoint.x + m_maxPoint.x) / T{ 2 }, (m_minPoint.y + m_maxPoint.y) / T{ 2 } }; // *T{ 0.5 };
		return center;
	}

	template <class T>
	Vector2<T> AABB2D<T>::GetSize()	const
	{
		return Vector2<T>{ m_maxPoint.x - m_minPoint.x, m_maxPoint.y - m_minPoint.y };
	}

	template <class T>
	T AABB2D<T>::GetWidth()	const
	{
		return m_maxPoint.x - m_minPoint.x;
	}

	template <class T>
	T AABB2D<T>::GetHeight() const
	{
		return m_maxPoint.y - m_minPoint.y;
	}

#pragma endregion Method_Definitions
}