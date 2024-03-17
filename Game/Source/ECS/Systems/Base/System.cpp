#include "Pch.h"
#include "System.h"

System::System(unsigned priority)
	: m_priority{ priority }, m_entityManager{ nullptr }
{
}

void System::Init(EntityManager* entityManager)
{
	m_entityManager = entityManager;
}