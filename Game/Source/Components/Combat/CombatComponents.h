#pragma once
#include "../ComponentBase.h"

// Rename file??

struct HealthComponent : public ComponentBase
{
	int		m_maxHealth;
	int		m_currentHealth;
};

struct WeaponComponent : public ComponentBase
{
	float	m_attackRange;
	float	m_attackSpeed;
	int		m_damageDealt;
};

struct BodyColliderComponent : public ComponentBase
{
	Hi_Engine::Physics::AABB2D<float> m_collider; // or use circle...
};

struct AttackColliderComponent : public ComponentBase
{
	Hi_Engine::Physics::AABB2D<float> m_collider;
	// circle collider?
	bool m_isEnabled;
};