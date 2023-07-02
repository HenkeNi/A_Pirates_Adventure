#include "Pch.h"
#include "CollisionSystem.h"
#include "Entity.h"

#include "Core/CoreComponents.h"


CollisionSystem::CollisionSystem()
	: System{ 1 }
{
}

CollisionSystem::~CollisionSystem()
{
}

void CollisionSystem::Receive(Message& aMsg)
{

}

void CollisionSystem::LateUpdate(float aDeltaTime)
{
	if (!m_entityManager)
		return;

	// fetch with transform and collider?!
}