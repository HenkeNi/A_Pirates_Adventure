#pragma once
#include "../ComponentBase.h"

// Rename file??


// Dont have health? Use Stats Component instead?
//struct HealthComponent : public ComponentBase
//{
//	int		m_maxHealth;
//	int		m_currentHealth;
//};


// Place in equipment??

struct WeaponComponent : public ComponentBase
{
	float	m_attackRange;
	float	m_attackSpeed;
	int		m_damageDealt;
};


// place in Physics??

// Interaction component or HitboxComponent?
struct HitboxColliderComponent : public ComponentBase
{
	Hi_Engine::Physics::AABB2D<float> m_collider; // or use circle...
};

struct AttackColliderComponent : public ComponentBase
{
	Hi_Engine::Physics::AABB2D<float>	m_collider;
	CU::Vector3<float>					m_offset = { 20.f, 0.f, 20.f };
	// circle collider?
	bool								m_isEnabled;
};