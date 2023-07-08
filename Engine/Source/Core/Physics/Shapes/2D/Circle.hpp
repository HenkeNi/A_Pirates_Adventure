#pragma once
#include "Utility/Math/Vectors/Vector2.hpp"

namespace Hi_Engine::Physics
{
	using namespace CommonUtilities;

	template <class T>
	class Circle
	{
	public:
		Circle();
		Circle(const Vector2<T>& aCenter, T aRadius);

		void				Init(const Vector2<T>& aCenter, T aRadius);
		bool				IsInside(const Vector2<T>& aPoint)				const;

		const Vector2<T>&	GetCenter()										const;
		T					GetRadius()										const;

	private:
		Vector2<T>			m_center;
		T					m_radius;
	};

#pragma region Constructors

	template <class T>
	Circle<T>::Circle()
		: m_center{}, m_radius{}
	{
	}

	template <class T>
	Circle<T>::Circle(const Vector2<T>& aCenter, T aRadius)
		: m_center{ aCenter }, m_radius{ aRadius }
	{
	}

#pragma endregion Constructors

#pragma region Method_Definitions

	template <class T>
	void Circle<T>::Init(const Vector2<T>& aCenter, T aRadius)
	{
		m_center = aCenter;
		m_radius = aRadius;
	}

	template <class T>
	bool Circle<T>::IsInside(const Vector2<T>& aPoint) const
	{
		auto distance = aPoint - m_center;
		return distance.LengthSqr() <= (m_radius * m_radius);
	}

	template <class T>
	const Vector2<T>& Circle<T>::GetCenter() const
	{
		return m_center;
	}
	
	template <class T>
	T Circle<T>::GetRadius() const
	{
		return m_radius;
	}

#pragma endregion Method_Definitions
}