#pragma once
#include "../../../../Utility/Math/Vectors/Vector2.hpp"

namespace Hi_Engine::Physics
{
	using namespace CommonUtilities;

	template <class T>
	class OBB2D
	{
	public:
		OBB2D();
		OBB2D(const Vector2<T>& center, const Vector2<T>& size, T rotation);

		void				Init(const Vector2<T>& center, const Vector2<T>& size, T rotation);
		bool				IsInside(const Vector2<T>& point)		const;								// TODO; fix?! 

		const Vector2<T>&	GetCenter()								const;
		const Vector2<T>&	GetSize()								const;
		const T&			GetRotation()							const;

	private:
		Vector2<T>&			m_center;
		Vector2<T>&			m_size;
		T					m_rotation;
	};

#pragma region Method_Definitions

	template <class T>
	OBB2D<T>::OBB2D()
		: m_center{ T(), T() }, m_size{ T(), T() }, m_rotation{ T() }
	{
	}

	template <class T>
	OBB2D<T>::OBB2D(const Vector2<T>& center, const Vector2<T>& size, T rotation)
		: m_center{ center }, m_size{ size }, m_rotation{ rotation }
	{
	}

	template <class T>
	void OBB2D<T>::Init(const Vector2<T>& center, const Vector2<T>& size, T rotation)
	{
		m_center = center;
		m_size = size;
		m_rotation = rotation;
	}

	template <class T>
	bool OBB2D<T>::IsInside(const Vector2<T>& point) const
	{
		Vector2<T> diff = point - m_center;
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