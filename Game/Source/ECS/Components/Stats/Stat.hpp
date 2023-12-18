#pragma once


namespace
{
	template <typename T>
	using ModifierMap = std::unordered_map<std::string, T>;
}

enum class eModifierType
{
	Coefficient,
	PreAdditive,
	PostAdditive,
	Count
};

template <typename T>
struct StatModifier
{
	eModifierType	Type;
	std::string		Identifier;
	T				Value;
};


template <typename T>
class Stat
{
public:
	Stat(T aBaseValue = 0);

	void SetBaseValue(T aValue);
	void IncrementBaseValue(T aValue);

	T	 GetTotalValue();
	T  	 GetBaseValue()									const;
	T	 GetModifier(const std::string& anIdentifier)	const; // TODO; get all of same type as well? or get all?	std::optional?  

	void AddModifier(eModifierType aType, const std::string& anIdentifier, T aValue);
	void RemoveModifier(const std::string& anIdentifier);									// pass in modifier type as well?

private:
	void UpdateTotalValue();

	std::array<ModifierMap<T>, (int)eModifierType::Count>	m_modifiers;
	T														m_baseValue, m_totalValue;
	bool													m_isTotalValueCached;
};

#pragma region Constructors

template <typename T>
Stat<T>::Stat(T aBaseValue)
	: m_baseValue{ aBaseValue }, m_totalValue{ aBaseValue }, m_isTotalValueCached{ false }
{
}

#pragma endregion Constructors

#pragma region Method_Definitions

template <typename T>
void Stat<T>::SetBaseValue(T aValue)
{
	m_baseValue = aValue;
	m_isTotalValueCached = false;
}

template <typename T>
void Stat<T>::IncrementBaseValue(T aValue)
{
	m_baseValue += aValue;
	m_isTotalValueCached = false;
}

template <typename T>
T Stat<T>::GetTotalValue()
{
	if (!m_isTotalValueCached)
		UpdateTotalValue();

	return m_totalValue;
}

template <typename T>
T Stat<T>::GetBaseValue() const
{
	return m_baseValue;
}

template <typename T>
T Stat<T>::GetModifier(const std::string& anIdentifier)	const
{
	for (auto& type : m_modifiers)
	{
		auto itr = std::find_if(type.begin(), type.end(), [&](auto& aModifier) { return aModifier.first == anIdentifier; });

		if (itr != m_modifiers.end())
			return itr->value;
	}

	return 0;
}

template <typename T>
void Stat<T>::AddModifier(eModifierType aType, const std::string& anIdentifier, T aValue)
{
	m_modifiers[(int)aType].insert_or_assign(anIdentifier, aValue);
	m_isTotalValueCached = false;
}

template <typename T>
void Stat<T>::RemoveModifier(const std::string& anIdentifier)	// pass in type?
{
	for (auto& type : m_modifiers)
	{
		auto itr = std::find_if(type.begin(), type.end(), [&](auto& aModifier) { return aModifier.first == anIdentifier; });

		if (itr != type.end())
			type.erase(itr);
	}


	m_isTotalValueCached = false;
}

template <typename T>
void Stat<T>::UpdateTotalValue()
{
	T coefficient{}, preAdditive{}, postAdditive{};

	for (const auto& modifier : m_modifiers[(int)eModifierType::Coefficient])
		coefficient += modifier.second;

	for (const auto& modifier : m_modifiers[(int)eModifierType::PreAdditive])
		preAdditive += modifier.second;

	for (const auto& modifier : m_modifiers[(int)eModifierType::PostAdditive])
		postAdditive += modifier.second;

	coefficient = coefficient == 0 ? 1 : coefficient;

	m_totalValue = coefficient * (preAdditive + m_baseValue) + postAdditive;
	m_isTotalValueCached = true;
}

#pragma endregion Method_Definitions
