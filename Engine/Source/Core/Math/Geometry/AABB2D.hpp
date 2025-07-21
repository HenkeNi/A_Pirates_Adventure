#pragma once
#include "../Vectors/Vector2.hpp"
#include "../../Utility/TypeTraits.h"

namespace Hi_Engine::Geometry
{
	using namespace Math;

	template <Numeric T>
	class AABB2D
	{
	public:
		constexpr AABB2D() = default;
		constexpr AABB2D(const Vector2<T>& min, const Vector2<T>& max);

		// ==================== Initialization ====================
		constexpr void Init(const Vector2<T>& min, const Vector2<T>& max) noexcept;

		// ==================== Accessors ====================
		[[nodiscard]] constexpr const Vector2<T>& GetMinPoint() const noexcept;

		[[nodiscard]] constexpr  const Vector2<T>& GetMaxPoint() const noexcept;
		
		[[nodiscard]] constexpr Vector2<T> GetCenter() const noexcept;
		
		[[nodiscard]] constexpr Vector2<T> GetSize() const noexcept;

		[[nodiscard]] constexpr T GetWidth() const noexcept;

		[[nodiscard]] constexpr T GetHeight() const noexcept;

		// ==================== Queries ====================
		[[nodiscard]] constexpr bool IsInside(const Vector2<T>& point) const noexcept;

		[[nodiscard]] constexpr bool Intersects(const AABB2D<T>& other) const noexcept; // Or use Intersection.hpp?

	private:
		Vector2<T> m_minPoint{};
		Vector2<T> m_maxPoint{};
	};

#pragma region Templeted_Methods

	template <Numeric T>
	constexpr AABB2D<T>::AABB2D(const Vector2<T>& min, const Vector2<T>& max)
		: m_minPoint{ min }, m_maxPoint{ max }
	{
	}

	template <Numeric T>
	constexpr void AABB2D<T>::Init(const Vector2<T>& min, const Vector2<T>& max) noexcept
	{
		m_minPoint = min;
		m_maxPoint = max;
	}

	template <Numeric T>
	constexpr const Vector2<T>& AABB2D<T>::GetMinPoint() const noexcept
	{
		return m_minPoint;
	}

	template <Numeric T>
	constexpr const Vector2<T>& AABB2D<T>::GetMaxPoint() const noexcept
	{
		return m_maxPoint;
	}

	template <Numeric T>
	constexpr Vector2<T> AABB2D<T>::GetCenter() const noexcept
	{
		return { (m_minPoint.x + m_maxPoint.x) / T{2}, (m_minPoint.y + m_maxPoint.y) / T{2}	};
	}

	template <Numeric T>
	constexpr Vector2<T> AABB2D<T>::GetSize()	const noexcept
	{
		return m_maxPoint - m_minPoint;
	}

	template <Numeric T>
	constexpr T AABB2D<T>::GetWidth()	const noexcept
	{
		return m_maxPoint.x - m_minPoint.x;
	}

	template <Numeric T>
	constexpr T AABB2D<T>::GetHeight() const noexcept
	{
		return m_maxPoint.y - m_minPoint.y;
	}

	template <Numeric T>
	constexpr bool AABB2D<T>::IsInside(const Vector2<T>& point) const noexcept
	{
		return point.x >= m_minPoint.x && point.x <= m_maxPoint.x
			&& point.y >= m_minPoint.y && point.y <= m_maxPoint.y;
	}

	template <Numeric T>
	constexpr bool AABB2D<T>::Intersects(const AABB2D<T>& other) const noexcept
	{
		return m_maxPoint.x >= other.m_minPoint.x
			&& m_minPoint.x <= other.m_maxPoint.x
			&& m_maxPoint.y >= other.m_minPoint.y
			&& m_minPoint.y <= other.m_maxPoint.y;
	}
#pragma endregion
}