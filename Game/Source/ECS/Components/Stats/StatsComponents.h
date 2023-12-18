#pragma once
#include "../Base/Component.h"
#include "Stat.hpp"

// Stats such as Health, Stamina, Armor(?), Regeneration -> separate stat components or all in one?

//struct StatsComponent : public ComponentBase
//{
//	std::unordered_map<std::string, StatModifier<float>>		m_floatStats;
//	std::unordered_map<std::string, StatModifier<unsigned>>		m_intStats;
//};

// Rename attributes?

struct HealthComponent : public Component
{
	Stat<int>		HealthStat; // DONT!?

	// unsigned		m_maxHealth; // renaem?
	int				CurrentValue = 100; // make sure is updated when removing modifiers... (100 is just temp -> init somewhere)...
	bool			IsInvincible;

	// TODO; store in effects? Or have an effect component?

};

struct StaminaComponent : public Component
{
	unsigned MaxStamina;
	int CurrentValue;
	// bool m_is;
};





// HERE??? or Needed???
struct PhysicalNeeds : public Component
{
	std::unordered_map<std::string, float> Needs;

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


