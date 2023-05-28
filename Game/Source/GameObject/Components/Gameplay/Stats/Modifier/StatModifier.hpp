#pragma once
#include <string>
#include <unordered_map>

// TODO; a range??
// TODO: store in map <eExpressionType, std::unorederedmap<Key, T> ??
// TODO: rename class?

enum class eModifierType
{
	Coefficient,
	PreAdditive,
	PostAdditive
};

template <typename Key = std::string>
struct ModifierKey 
{
	eModifierType m_modifierType;
	Key m_key;
};

template <typename Type, typename Key = std::string>
class StatModifier
{
public:
	StatModifier(Type aBaseValue = 0);

	void	SetBaseValue(Type aValue);
	void	ModifyBaseValue(Type aModifier);

	Type	GetTotalValue()	const;
	Type	GetBaseValue()	const;

	void	AddCoefficient(const Key& aKey, Type aValue);
	void	AddPreAdditive(const Key& aKey, Type aValue);
	void	AddPostAdditive(const Key& aKey, Type aValue);

	Type	GetCoefficient(const Key& aKey);
	Type	GetPreAdditive(const Key& aKey);
	Type	GetPostAdditive(const Key& aKey);

	void	RemoveCoefficient(const Key& aKey);
	void	RemovePreAdditive(const Key& aKey);
	void	RemovePostAdditive(const Key& aKey);

private:
	void	CalculateTotalValue();
	void	CalculateCoefficient();
	void	CalculatePreAdditive();
	void	CalculatePostAdditive();

	std::unordered_map<eModifierType, std::unordered_map<Key, Type>> m_modifiers;	// 

	std::unordered_map<Key, Type>	m_coefficients;
	std::unordered_map<Key, Type>	m_preAdditives;
	std::unordered_map<Key, Type>	m_postAdditives;
	Type							m_baseValue, m_totalValue;
	Type							m_cachedCoefficient, m_cachedPreAdditive, m_cachedPostAdditive;
};

#pragma region Constructors

	template <typename Type, typename Key>
	StatModifier<Type, Key>::StatModifier(Type aBaseValue)
		: m_baseValue{ aBaseValue }, m_totalValue{ aBaseValue }
	{
	}

#pragma endregion Constructors

#pragma region Method_Definitons

	template <typename Type, typename Key>
	void StatModifier<Type, Key>::SetBaseValue(Type aValue)
	{
		m_baseValue = aValue;
	}

	template <typename Type, typename Key>
	void StatModifier<Type, Key>::ModifyBaseValue(Type aModifier)
	{
		m_baseValue += aModifier;
	}

	template <typename Type, typename Key>
	Type StatModifier<Type, Key>::GetTotalValue() const
	{
		return m_totalValue;
	}
	
	template <typename Type, typename Key>
	Type StatModifier<Type, Key>::GetBaseValue()	const
	{
		return m_baseValue;
	}

	template <typename Type, typename Key>
	void StatModifier<Type, Key>::AddCoefficient(const Key& aKey, Type aValue)
	{
		m_coefficients.insert_or_assign(aKey, aValue);
		CalculateCoefficient();
	}
	
	template <typename Type, typename Key>
	void StatModifier<Type, Key>::AddPreAdditive(const Key& aKey, Type aValue)
	{
		m_preAdditives.insert_or_assign(aKey, aValue);
		CalculatePreAdditive();
	}
	
	template <typename Type, typename Key>
	void StatModifier<Type, Key>::AddPostAdditive(const Key& aKey, Type aValue)
	{
		m_postAdditives.insert_or_assign(aKey, aValue);
		CalculatePostAdditive();
	}

	template <typename Type, typename Key>
	Type StatModifier<Type, Key>::GetCoefficient(const Key& aKey)
	{
		if (m_coefficients.find(aKey) != m_coefficients.end())
		{
			return m_coefficients[aKey];
		}

		return 0;
	}
	
	template <typename Type, typename Key>
	Type StatModifier<Type, Key>::GetPreAdditive(const Key& aKey)
	{
		if (m_preAdditives.find(aKey) != m_preAdditives.end())
		{
			return m_preAdditives[aKey];
		}

		return 0;
	}
	
	template <typename Type, typename Key>
	Type StatModifier<Type, Key>::GetPostAdditive(const Key& aKey)
	{
		if (m_postAdditives.find(aKey) != m_postAdditives.end())
		{
			return m_postAdditives[aKey];
		}

		return 0;
	}

	template <typename Type, typename Key>
	void StatModifier<Type, Key>::RemoveCoefficient(const Key& aKey)
	{
		m_coefficients.erase(aKey);
	}
	
	template <typename Type, typename Key>
	void StatModifier<Type, Key>::RemovePreAdditive(const Key& aKey)
	{
		m_preAdditives.erase(aKey);
	}
	
	template <typename Type, typename Key>
	void StatModifier<Type, Key>::RemovePostAdditive(const Key& aKey)
	{
		m_postAdditives.erase(aKey);
	}

	template <typename Type, typename Key>
	void StatModifier<Type, Key>::CalculateTotalValue()
	{
		return m_cachedCoefficient * (m_cachedPreAdditive + m_baseValue) + m_cachedPostAdditive;
	}

	template <typename Type, typename Key>
	void StatModifier<Type, Key>::CalculateCoefficient()
	{
		Type total;
		for (const auto& coefficient : m_coefficients)
			total += coefficient.second;

		CalculateTotalValue();
		return total;
	}
	
	template <typename Type, typename Key>
	void StatModifier<Type, Key>::CalculatePreAdditive()
	{
		Type total;
		for (const auto& preAdditive : m_preAdditives)
			total += preAdditive.second;

		CalculateTotalValue();
		return total;
	}

	template <typename Type, typename Key>
	void StatModifier<Type, Key>::CalculatePostAdditive()
	{
		Type total;
		for (const auto& postAdditive : m_postAdditives)
			total += postAdditive.second;

		CalculateTotalValue();
		return total;
	}

#pragma endregion Method_Definitions