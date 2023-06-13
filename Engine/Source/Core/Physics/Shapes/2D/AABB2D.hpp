#pragma once
#include "Utility/Math/Vectors/Vector2.hpp"

namespace Hi_Engine::Physics
{
	using namespace CommonUtilities;

	template <class T>
	class AABB2D
	{
	public:
		AABB2D();
		AABB2D(const Vector2<T>& aMin, const Vector2<T>& aMax);

		void					Init(const Vector2<T>& aMin, const Vector2<T>& aMax);
		bool					IsInside(const Vector2<T>& aPoint)							const;

		const Vector2<T>&		GetMinPoint()												const;
		const Vector2<T>&		GetMaxPoint()												const;
		const Vector2<T>&		GetCenter()													const;

		T						GetWidth()													const;
		T						GetHeight()													const;

	private:
		Vector2<T>				m_minPoint;
		Vector2<T>				m_maxPoint;
	};

#pragma region Constructores

	template <class T>
	AABB2D<T>::AABB2D()
		: m_minPoint{ T(), T() }, m_maxPoint{ T(), T() }
	{
	}

	template <class T>
	AABB2D<T>::AABB2D(const Vector2<T>& aMin, const Vector2<T>& aMax)
		: m_minPoint{ aMin }, m_maxPoint{ aMax }
	{
	}

#pragma endregion Constructors

#pragma region Method_Definitions

	template <class T>
	void AABB2D<T>::Init(const Vector2<T>& aMin, const Vector2<T>& aMax)
	{
		m_minPoint = aMin;
		m_maxPoint = aMax;
	}

	template <class T>
	bool AABB2D<T>::IsInside(const Vector2<T>& aPoint) const
	{
		if (m_minPoint.x > aPoint.x) { return false; }
		if (m_minPoint.y > aPoint.y) { return false; }

		if (m_maxPoint.x < aPoint.x) { return false; }
		if (m_maxPoint.y < aPoint.y) { return false; }

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
	const Vector2<T>& AABB2D<T>::GetCenter() const
	{
		auto difference = Vector2<T>{ m_maxPoint - m_minPoint };
		return m_minPoint + (difference * 0.5f);
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