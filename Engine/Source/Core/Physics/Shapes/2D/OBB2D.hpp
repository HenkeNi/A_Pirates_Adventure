#pragma once
#include "Utility/Math/Vectors/Vector2.hpp"

namespace Hi_Engine::Physics
{
	using namespace CommonUtilities;

	template <class T>
	class OBB2D
	{
	public:
		OBB2D();
		OBB2D(const Vector2<T>& aCenter, const Vector2<T>& aSize, T aRotation);

		void				Init(const Vector2<T>& aCenter, const Vector2<T>& aSize, T aRotation);
		bool				IsInside(const Vector2<T>& aPoint)		const;

		const Vector2<T>&	GetCenter()								const;
		const Vector2<T>&	GetSize()								const;
		const T&			GetRotation()							const;

	private:
		Vector2<T>&			m_center;
		Vector2<T>&			m_size;
		T					m_rotation;
	};

#pragma region Constructors

	template <class T>
	OBB2D<T>::OBB2D()
		: m_center{ T(), T() }, m_size{ T(), T() }, m_rotation{ T() }
	{
	}

	template <class T>
	OBB2D<T>::OBB2D(const Vector2<T>& aCenter, const Vector2<T>& aSize, T aRotation)
		: m_center{ aCenter }, m_size{ aSize }, m_rotation{ aRotation }
	{
	}

#pragma endregion Constructors

#pragma region Method_Definitions

	template <class T>
	void OBB2D<T>::Init(const Vector2<T>& aCenter, const Vector2<T>& aSize, T aRotation)
	{
		m_center = aCenter;
		m_size	= aSize;
		m_rotation = aRotation;
	}

	template <class T>
	bool OBB2D<T>::IsInside(const Vector2<T>& aPoint) const
	{
		Vector2<T> diff = aPoint - m_center;
		T rotatedX = diff.x * cos(m_rotation) - diff.y * sin(m_rotation);
		T rotatedY = diff.x * sin(m_rotation) + diff.y * cos(m_rotation);

		return (std::abs(rotatedX) < m_size.x / 2) && (std::abs(rotatedY) < m_size.y / 2);
	}

	template <class T>
	const Vector2<T>& OBB2D<T>::GetCenter() const
	{
		return m_center;
	}

	template <class T>
	const Vector2<T>& OBB2D<T>::GetSize() const
	{
		return m_size;
	}

	template <class T>
	const T& OBB2D<T>::GetRotation() const
	{
		return m_rotation;
	}

#pragma endregion Method_Definitions
}