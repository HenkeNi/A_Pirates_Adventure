#pragma once
#include "../Vectors/Vector2.hpp"

namespace Hi_Engine::Geometry
{
	using namespace Math;

	// TODO; mark noexcept and constexpr

	template <typename T>
	class Circle
	{
	public:
		Circle();
		Circle(const Vector2<T>& position, T radius);
		Circle(T xPos, T yPos, T radius);

		void Init(const Vector2<T>& position, T radius);
		[[nodiscard]] bool IsInside(const Vector2<T>& point) const;

		[[nodiscard]] const Vector2<T>& GetPosition()	const;
		[[nodiscard]] T GetRadius()		const;

	private:
		Vector2<T> m_position;
		T m_radius;
	};

#pragma region Templated_Methods

	template <typename T>
	Circle<T>::Circle()
		: m_position{}, m_radius{}
	{
	}

	template <typename T>
	Circle<T>::Circle(const Vector2<T>& position, T radius)
		: m_position{ position }, m_radius{ radius }
	{
	}

	template <typename T>
	Circle<T>::Circle(T xPos, T yPos, T radius)
		: m_position{ xPos, yPos }, m_radius{ radius }
	{
	}

	template <typename T>
	void Circle<T>::Init(const Vector2<T>& position, T radius)
	{
		m_position = position;
		m_radius = radius;
	}

	template <typename T>
	bool Circle<T>::IsInside(const Vector2<T>& point) const
	{
		auto distance = point - m_position;
		return distance.LengthSqr() <= (m_radius * m_radius);
	}

	template <typename T>
	const Vector2<T>& Circle<T>::GetPosition() const
	{
		return m_position;
	}
	
	template <typename T>
	T Circle<T>::GetRadius() const
	{
		return m_radius;
	}

#pragma endregion
}