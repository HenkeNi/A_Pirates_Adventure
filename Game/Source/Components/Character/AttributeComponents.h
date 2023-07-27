#pragma once
#include "../Base/ComponentBase.h"


struct AttributeComponent : public ComponentBase
{
	// contains 
	// std::unordered_map<std::string, Stat<int>>		m_attributes;

};

struct CharacterStateComponent : public ComponentBase
{
	bool m_isIdle;
	bool m_isWalking;
	bool m_isRunning;
	bool m_isJumping;
	bool m_isAttacking;
	bool m_isAlive;
};