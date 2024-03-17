#pragma once
#include "../../../../Utility/Math/Vectors/Vector2.hpp"

namespace Hi_Engine::Physics
{
	using namespace CommonUtilities;

	template <class T>
	class Circle
	{
	public:
		Circle();
		Circle(const Vector2<T>& position, T tadius);

		void				Init(const Vector2<T>& position, T radius);
		bool				IsInside(const Vector2<T>& point)				const;

		const Vector2<T>&	GetPosition()									const;
		T					GetRadius()										const;

	private:
		Vector2<T>			m_position;
		T					m_radius;
	};

#pragma region Method_Definitions

	template <class T>
	Circle<T>::Circle()
		: m_position{}, m_radius{}
	{
	}

	template <class T>
	Circle<T>::Circle(const Vector2<T>& position, T radius)
		: m_position{ position }, m_radius{ radius }
	{
	}

	template <class T>
	void Circle<T>::Init(const Vector2<T>& position, T radius)
	{
		m_position = position;
		m_radius = radius;
	}

	template <class T>
	bool Circle<T>::IsInside(const Vector2<T>& point) const
	{
		auto distance = point - m_position;
		return distance.LengthSqr() <= (m_radius * m_radius);
	}

	template <class T>
	const Vector2<T>& Circle<T>::GetPosition() const
	{
		return m_position;
	}
	
	template <class T>
	T Circle<T>::GetRadius() const
	{
		return m_radius;
	}

#pragma endregion Method_Definitions
}