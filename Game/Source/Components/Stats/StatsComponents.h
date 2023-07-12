#pragma once
#include "../ComponentBase.h"
#include "Stat.hpp"

// Stats such as Health, Stamina, Armor(?), Regeneration -> separate stat components or all in one?

//struct StatsComponent : public ComponentBase
//{
//	std::unordered_map<std::string, StatModifier<float>>		m_floatStats;
//	std::unordered_map<std::string, StatModifier<unsigned>>		m_intStats;
//};

// Rename attributes?

struct HealthComponent : public ComponentBase
{
	Stat<int>		m_healthStat; // DONT!?

	// unsigned		m_maxHealth; // renaem?
	int				m_currentValue = 100; // make sure is updated when removing modifiers... (100 is just temp -> init somewhere)...
	bool			m_isInvincible;

	// TODO; store in effects? Or have an effect component?

};

struct StaminaComponent : public ComponentBase
{
	unsigned m_maxStamina;
	int m_currentValue;
	// bool m_is;
};





// HERE??? or Needed???
struct PhysicalNeeds : public ComponentBase
{
	std::unordered_map<std::string, float> m_needs;

};


	//enum class eModifierType
	//{
	//	Coefficient,
	//	PreAdditive,
	//	PostAdditive
	//};

	//template <typename T>
	//struct Modifier
	//{
	//	enum class eModifierType
	//	{
	//		Coefficient,
	//		PreAdditive,
	//		PostAdditive
	//	} m_type;
	//	std::string		m_identifier;
	//	T m_value;
	//};


