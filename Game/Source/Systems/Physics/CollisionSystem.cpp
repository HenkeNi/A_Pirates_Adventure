#include "Pch.h"
#include "CollisionSystem.h"
#include "EntityManager.h"


#include "Entity.h"
#include "Core/CoreComponents.h"
#include "../Utility/Map/MapUtils.h"

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

	// query for tilemap component?!

	auto entities = m_entityManager->FindAllWithComponents<HitboxColliderComponent, TransformComponent>();
	// auto mapChunks = m_entityManager->FindAllWithComponents<MapChunkComponent>();

	for (auto& entity : entities)
	{
		auto* collider = entity->GetComponent<HitboxColliderComponent>();
		if (collider->m_isStatic)
			continue;
		// TODO; check if collider is static...

		// Check entity - entity collisions...

		CheckMapCollisions(entity);

		
	

	}

	// fetch with transform and collider?!

	// fetch map
}

//Entity* CollisionSystem::GetMapChunkContainingEntity(const Entity* anEntity)
//{
//	auto mapChunks = m_entityManager->FindAllWithComponents<MapChunkComponent>();
//
//	// Convert entity position to coordinates
//
//	for (const auto& mapChunk : mapChunks)
//	{
//		auto mapTransform = mapChunk->GetComponent<TransformComponent>();
//
//
//	}
//
//	return nullptr;
//}

void CollisionSystem::CheckMapCollisions(Entity* anEntity)
{
	// auto entityPosition = anEntity->GetComponent<TransformComponent>()->m_currentPos;
	
	// Check all 4 corners of the collider...?

	auto hitbox = anEntity->GetComponent<HitboxColliderComponent>();

	// temp
	auto center = hitbox->m_collider.GetCenter();

	auto mapChunk = MapUtils::GetMapChunkAtPosition(m_entityManager->FindAllWithComponents<MapChunkComponent>(), center);
	Tile* tile = MapUtils::GetTileAtWorldPosition(mapChunk, center);
	if (!tile)
		return;

	if (tile->m_isCollidable)
	{
		ResolveCollision(anEntity, tile);
		
	}

	//std::cout << "Tile: " << tile->m_coordinates.x << ", " << tile->m_coordinates.y << '\n';

	// get tile player is occupying...


	
	







	// check if mapChunks contains player's position?!

	//for (auto& mapChunk : someMapChunks)
	//{
	//	auto mapChunkChunk = mapChunk->GetComponent<MapChunkComponent>();
	//	auto chunkTransform = mapChunk->GetComponent<TransformComponent>();
	//	auto chunkPosition = chunkTransform->m_currentPos;

	//	if (entityPosition.x < chunkPosition.x || entityPosition.z < chunkPosition.z)
	//		continue;

	//	if (entityPosition.x > chunkPosition.x + mapChunkChunk->m_width || entityPosition.y > chunkPosition.y + mapChunkChunk->m_height)
	//		continue;

}

void CollisionSystem::ResolveCollision(Entity* anEntity, Tile* aTile)
{
	// Move first x, then y-axis? each step check collisions...
	
	auto transformComponent = anEntity->GetComponent<TransformComponent>();
	transformComponent->m_currentPos = transformComponent->m_previousPos;

	//auto velocityComponent = anEntity->GetComponent<VelocityComponent>();

	//static float tileSize = 1.f;

	//if (velocityComponent->m_velocity.z < 0.f)
	//	transformComponent->m_currentPos.z += 1;
	//	//transformComponent->m_currentPos.z = aTile->m_position.z + tileSize;
	//else
	//	transformComponent->m_currentPos.z -= 1;
	//	//transformComponent->m_currentPos.z = aTile->m_position.z;

	//if (velocityComponent->m_velocity.x < 0.f)
	//	transformComponent->m_currentPos.x += 1;
	//	//transformComponent->m_currentPos.x = aTile->m_position.x + tileSize;
	//else 
	//	transformComponent->m_currentPos.x -= 1;
	//	//transformComponent->m_currentPos.x = aTile->m_position.x;

}