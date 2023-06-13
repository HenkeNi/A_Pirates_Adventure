#pragma once
#include "../Entity/EntityManager.h"
#include "SystemManager.h"


class GameWorld
{
public:
	GameWorld();
	~GameWorld();

	void Init();
	void Update(float aDeltaTime);
	void LateUpdate(float aDeltaTime);
	void Draw();

	// Create entity?
	// get entities?

private:
	//EntityManager	m_entityManager;
	//SystemManager	m_systemManager;
};

