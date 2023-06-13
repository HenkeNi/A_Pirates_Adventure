#include "Pch.h"
#include "CollisionSystem.h"
#include "../Entity/Entity.h"

#include "../Entity/Components/Core/CoreComponents.h"


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
	// fetch with transform and collider?!
}