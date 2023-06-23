#pragma once
#include "Enumerations.h"
#include "SceneManagerProxy.h"

#include <any>


// Todo; change naming convention to sceneManager, rather thna m_sceneManager;

struct SharedContext
{
	SceneManagerProxy	 m_sceneManager;
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

struct Timer
{
	float m_elapsed;
	float m_duration;
};

template <typename T>
struct Range
{
	T m_min;
	T m_max;
};