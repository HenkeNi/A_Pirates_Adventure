#pragma once
#include <string>
#include <unordered_map>

namespace Hi_Engine
{
	// TODO; a range??
	// TODO: store in map <eExpressionType, std::unorederedmap<Key, T> ??
	// TODO: rename class?

	template <typename T, typename Key = std::string>
	class MathExpression
	{
	public:
		MathExpression(T aBaseValue = 0);

		void	SetBaseValue(T aValue);
		void	IncrementBaseValue(T aValue);

		T		GetTotalValue()	 const;
		T		GetBaseValue()	const;

		void	AddCoefficient(const Key& aKey,  T aValue);
		void	AddPreAdditive(const Key& aKey,  T aValue);
		void	AddPostAdditive(const Key& aKey, T aValue);

		T		GetCoefficient(const Key& aKey);
		T		GetPreAdditive(const Key& aKey);
		T		GetPostAdditive(const Key& aKey);

		void	RemoveCoefficient(const Key& aKey);
		void	RemovePreAdditive(const Key& aKey);
		void	RemovePostAdditive(const Key& aKey);

	private:
		void	CalculateTotalValue();
		void	CalculateCoefficient();
		void	CalculatePreAdditive();
		void	CalculatePostAdditive();

		std::unordered_map<Key, T>	m_coefficients, m_preAdditives, m_postAdditives;
		T							m_baseValue, m_totalValue;
		T							m_calculatedCoefficient, m_calculatedPreAdditive, m_calculatedPostAdditive; // CachedCoefficient...?
	};

#pragma region Constructors

	template <typename T, typename Key>
	MathExpression<T, Key>::MathExpression(T aBaseValue)
		: m_baseValue{ aBaseValue }, m_totalValue{ aBaseValue }
	{
	}

#pragma endregion Constructors

#pragma region Method_Definitons

	template <typename T, typename Key>
	void MathExpression<T, Key>::SetBaseValue(T aValue)
	{
		m_baseValue = aValue;
	}

	template <typename T, typename Key>
	void MathExpression<T, Key>::IncrementBaseValue(T aValue)
	{
		m_baseValue += aValue;
	}

	template <typename T, typename Key>
	T MathExpression<T, Key>::GetTotalValue() const
	{
		return m_totalValue;
	}
	
	template <typename T, typename Key>
	T MathExpression<T, Key>::GetBaseValue()	const
	{
		return m_baseValue;
	}

	template <typename T, typename Key>
	void MathExpression<T, Key>::AddCoefficient(const Key& aKey, T aValue)
	{
		m_coefficients.insert_or_assign(aKey, aValue);
		CalculateCoefficient();
	}
	
	template <typename T, typename Key>
	void MathExpression<T, Key>::AddPreAdditive(const Key& aKey, T aValue)
	{
		m_preAdditives.insert_or_assign(aKey, aValue);
		CalculatePreAdditive();
	}
	
	template <typename T, typename Key>
	void MathExpression<T, Key>::AddPostAdditive(const Key& aKey, T aValue)
	{
		m_postAdditives.insert_or_assign(aKey, aValue);
		CalculatePostAdditive();
	}

	template <typename T, typename Key>
	T MathExpression<T, Key>::GetCoefficient(const Key& aKey)
	{
		if (m_coefficients.find(aKey) != m_coefficients.end())
		{
			return m_coefficients[aKey];
		}

		return 0;
	}
	
	template <typename T, typename Key>
	T MathExpression<T, Key>::GetPreAdditive(const Key& aKey)
	{
		if (m_preAdditives.find(aKey) != m_preAdditives.end())
		{
			return m_preAdditives[aKey];
		}

		return 0;
	}
	
	template <typename T, typename Key>
	T MathExpression<T, Key>::GetPostAdditive(const Key& aKey)
	{
		if (m_postAdditives.find(aKey) != m_postAdditives.end())
		{
			return m_postAdditives[aKey];
		}

		return 0;
	}

	template <typename T, typename Key>
	void MathExpression<T, Key>::RemoveCoefficient(const Key& aKey)
	{
		m_coefficients.erase(aKey);
	}
	
	template <typename T, typename Key>
	void MathExpression<T, Key>::RemovePreAdditive(const Key& aKey)
	{
		m_preAdditives.erase(aKey);
	}
	
	template <typename T, typename Key>
	void MathExpression<T, Key>::RemovePostAdditive(const Key& aKey)
	{
		m_postAdditives.erase(aKey);
	}

	template <typename T, typename Key>
	void MathExpression<T, Key>::CalculateTotalValue()
	{
		return m_calculatedCoefficient * (m_calculatedPreAdditive + m_baseValue) + m_postAdditives;
	}

	template <typename T, typename Key>
	void MathExpression<T, Key>::CalculateCoefficient()
	{
		T total;
		for (const auto& coefficient : m_coefficients)
			total += coefficient.second;

		CalculateTotalValue();
		return total;
	}
	
	template <typename T, typename Key>
	void MathExpression<T, Key>::CalculatePreAdditive()
	{
		T total;
		for (const auto& preAdditive : m_preAdditives)
			total += preAdditive.second;

		CalculateTotalValue();
		return total;
	}

	template <typename T, typename Key>
	void MathExpression<T, Key>::CalculatePostAdditive()
	{
		T total;
		for (const auto& postAdditive : m_postAdditives)
			total += postAdditive.second;

		CalculateTotalValue();
		return total;
	}

#pragma endregion Method_Definitions
}