#pragma once
#include "../Base/ComponentBase.h"


struct AttributeComponent : public ComponentBase
{
	// contains 
	// std::unordered_map<std::string, Stat<int>>		m_attributes;

};

struct CharacterStateComponent : public ComponentBase
{
	bool IsIdle;
	bool IsWalking;
	bool IsRunning;
	bool IsJumping;
	bool IsAttacking;
	bool IsAlive;


	// State machine??
};