#pragma once
#include "Enumerations.h"
#include "SceneManagerProxy.h"
#include <any>


// Todo; change naming convention to sceneManager, rather thna m_sceneManager;

struct SharedContext
{
	SceneManagerProxy		m_sceneManager;
	class SystemManager&	m_systemManager;
};

struct CompMessage
{
	eComponentMessage	m_messageType;
	const std::any&		m_data;
};

struct CollisionData // Data used for resolving/handling collisions
{
	unsigned m_damageDealt = 0;
};

template <typename T>
struct Range
{
	T m_min;
	T m_max;
};







struct BaseComponentData
{
	virtual ~BaseComponentData() {}
};


template <typename Derived>
struct ComponentData
{
	Derived* Get()
	{
		return static_cast<Derived*>(this);
	}
};


struct TransformComponentData : public ComponentData<TransformComponentData>
{
	float m_x;
	float m_y;
};

struct SpriteComponentData : public ComponentData<SpriteComponentData>
{
	std::string m_sprite;
};