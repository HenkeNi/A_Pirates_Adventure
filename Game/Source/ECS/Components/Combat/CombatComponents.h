#pragma once
#include "../Base/Component.h"


struct HitboxComponent : public Component
{
	Hi_Engine::Physics::AABB2D<float>	Collider; // or use circle...
	bool								IsStatic;
};

struct AttackComponent : public Component
{
	Hi_Engine::Physics::AABB2D<float>	Collider;
	CU::Vector3<float>					Offset = { 20.f, 0.f, 20.f };
	// circle collider?
	bool								IsEnabled;
};













// Dont have health? Use Stats Component instead?
//struct HealthComponent : public ComponentBase
//{
//	int		m_maxHealth;
//	int		m_currentHealth;
//};


// Place in equipment??

struct WeaponComponent : public Component
{
	float	AttackRange;
	float	AttackSpeed;
	int		DamageDealt;
};


// place in Physics??






// MOVE


struct EnemySpawnerComponent : public Component
{

};



struct ItemSpawnerComponent : public Component
{

};