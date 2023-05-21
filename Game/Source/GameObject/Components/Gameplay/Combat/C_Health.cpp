#include "Pch.h"
#include "C_Health.h"

namespace CU = CommonUtilities;


C_Health::C_Health(GameObject* anOwner)
	: Component{ anOwner }, m_maxHealth{ 0 }, m_currentHealth{ 0 }
{
}

C_Health::~C_Health()
{
}

void C_Health::HandleMessage(const CompMessage& aMsg)
{
}

void C_Health::Update(float aDeltaTime)
{
}

void C_Health::ModifyCurrentHealth(int anAmount)
{
	m_currentHealth = CU::Clamp(m_currentHealth + anAmount, 0, m_maxHealth);
}

void C_Health::IncreaseMaxHealth(int anAmount)
{
	m_maxHealth += anAmount;
}

bool C_Health::IsAlive() const
{
	return m_currentHealth > 0;
}
