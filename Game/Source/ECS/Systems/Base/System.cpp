#include "Pch.h"
#include "System.h"

System::System(unsigned aPriority)
	: m_priority{ aPriority }, m_entityManager{ nullptr }
{
}

void System::Init(EntityManager* anEntityManager)
{
	m_entityManager = anEntityManager;
}