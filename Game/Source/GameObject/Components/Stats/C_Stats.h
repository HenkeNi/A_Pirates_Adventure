#pragma once
#include "../Component.h"


// OR IntegerStat / FloatStat--??

// C_PhysicalNeeds componetn instead??? -> Stat as ordinary class? 

class C_Stats : public Component
{
public:




private:
	std::unordered_map<std::string, Hi_Engine::MathExpression<float>>		m_floatStats;
	std::unordered_map<std::string, Hi_Engine::MathExpression<unsigned>>	m_intStats;
};

