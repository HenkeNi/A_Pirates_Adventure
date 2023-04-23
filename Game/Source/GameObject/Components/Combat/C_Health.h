#pragma once
#include "../Component.h"


// Stats class instead?? health, attack, etc...??


class C_Health : public Component
{
public:
	C_Health(GameObject* anOwner = nullptr);
	~C_Health();

	void HandleMessage(CompMessage aMessage)	override;
	void Update(float aDeltaTime)				override;

	void ModifyCurrentHealth(int anAmount);
	void IncreaseMaxHealth(int anAmount);
	bool IsAlive() const;

private:
	int m_currentHealth, m_maxHealth;

};