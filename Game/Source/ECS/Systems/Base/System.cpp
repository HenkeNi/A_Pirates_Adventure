#include "Pch.h"
#include "System.h"


System::System(unsigned priority)
	: m_priority{ priority }, m_ecs{ nullptr }
{
}

void System::Init(ECS* ecs)
{
	m_ecs = ecs;
	SetSignature();
}