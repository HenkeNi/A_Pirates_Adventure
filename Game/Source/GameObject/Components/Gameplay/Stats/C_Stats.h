#pragma once
#include "../../Component.h"
#include "Modifier/StatModifier.hpp"

// OR IntegerStat / FloatStat--??

// C_PhysicalNeeds componetn instead??? -> Stat as ordinary class? 

// templated??
class C_Stats : public Component
{
public:
	C_Stats(GameObject* anOwner);
	~C_Stats();

	void Restore();


private:
	std::unordered_map<std::string, StatModifier<float>>		m_floatStats;
	std::unordered_map<std::string, StatModifier<unsigned>>		m_intStats;
};

