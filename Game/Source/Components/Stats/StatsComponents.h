#pragma once
#include "../ComponentBase.h"
#include "Stat.hpp"

// Stats such as Health, Stamina, Armor(?), Regeneration -> separate stat components or all in one?

//struct StatsComponent : public ComponentBase
//{
//	std::unordered_map<std::string, StatModifier<float>>		m_floatStats;
//	std::unordered_map<std::string, StatModifier<unsigned>>		m_intStats;
//};



struct HealthComponent : public ComponentBase
{
	Stat<int>		m_healthStat;
	int				m_currentValue; // make sure is updated when removing modifiers...
 	bool			m_isAlive;		// Needed?
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


