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
	//if () // map created
	//	;


	//if () // map destroyed
	//	;


}

void CollisionSystem::LateUpdate(float aDeltaTime)
{
	if (!m_entityManager)
		return;


	// query for tilemap component?!




	// fetch with transform and collider?!

	// fetch map

}