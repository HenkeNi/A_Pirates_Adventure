#include "Pch.h"
#include "CollisionSystem.h"
#include "Entities/EntityManager.h"


#include "Entities/Entity.h"
#include "Components/Core/CoreComponents.h"
#include "../Utility/Map/MapUtils.h"
#include "Components/AI/AIComponents.h"
#include "Components/Map/MapComponents.h"
//#include <../Engine/Source/Utility/Math/Mathf.hpp>

CollisionSystem::CollisionSystem()
	: System{ 1 }
{
	// Update collider when game starts?

}

CollisionSystem::~CollisionSystem()
{
}

void CollisionSystem::Init()
{
	// TODO initialize collider positions...
}

void CollisionSystem::Receive(Message& aMsg)
{
}


//bool SweptAABBTest(HitboxComponent& aSource, Hi_Engine::Physics::AABB2D<float>& other, float& aPenetration, CU::Vector2<float>& aNormal)
//{
//
//	float aXmin = aSource.Collider.GetMinPoint().x;
//	float aXmax = aSource.Collider.GetMaxPoint().x;
//
//	float bXmin = other.GetMinPoint().x;
//	float bXmax = other.GetMaxPoint().x;
//
//	// Y axis projection
//	float aYmin = aSource.Collider.GetMinPoint().y;
//	float aYmax = aSource.Collider.GetMaxPoint().y;
//
//	float bYmin = other.GetMinPoint().y;
//	float bYmax = other.GetMaxPoint().y;
//
//	// Check for non-intersection and early exit clause.
//	if (aXmin > bXmax) return false;
//	if (bXmin > aXmax) return false;
//
//	if (aYmin > bYmax) return false;
//	if (bYmin > aYmax) return false;
//
//	// If we reach this point, then there is a collision. 
//	// We now have to compute the manifold
//
//	aPenetration = std::numeric_limits<float>::max();
//
//	// Other collider on the right?
//	if (bXmin < aXmax && aXmin < bXmax)
//	{
//		aPenetration = std::abs(bXmin - aXmax);
//		aNormal.x = -1.f;
//		aNormal.y = 0.f;
//	}
//	// Other collider on the left?
//	if (aXmin < bXmax && bXmin < aXmax)
//	{
//		aPenetration = std::abs(aXmin - bXmax);
//		aNormal.x = 1.f;
//		aNormal.y = 0.f;
//	}
//	// Repeat for Y axis
//	// Other collider above?
//	float py;
//	if (bYmin < aYmax && aYmin < bYmax)
//	{
//		py = std::abs(bYmin - aYmax);
//		if (py < aPenetration)
//		{
//			aPenetration = py;
//			aNormal.x = 0.f;
//			aNormal.y = -1.f;
//		}
//	}
//	// Other collider below?
//	if (aXmin < bXmax && bXmin < aXmax)
//	{
//		py = std::abs(aXmin - bXmax);
//		if (py < aPenetration)
//		{
//			aPenetration = py;
//			aNormal.x = 0.f;
//			aNormal.y = 1.f;
//		}
//	}
//	return true;
//
//}
//float SweptAABBV2(const Hi_Engine::Physics::AABB2D<float>& aSource, const CU::Vector2<float>& aSrcVelocity, const Hi_Engine::Physics::AABB2D<float>& aTarget, CU::Vector2<float>& aNormal)
//{
//	float vx = aSrcVelocity.x;
//	float vy = aSrcVelocity.y;
//
//	float targetMinX = aTarget.GetMinPoint().x;
//	float targetMaxX = aTarget.GetMaxPoint().x;
//
//	float sourceMinX = aSource.GetMinPoint().x;
//	float sourceMaxX = aSource.GetMaxPoint().x;
//
//
//	float targetMinY = aTarget.GetMinPoint().y;
//	float targetMaxY = aTarget.GetMaxPoint().y;
//
//	float sourceMinY = aSource.GetMinPoint().y;
//	float sourceMaxY = aSource.GetMaxPoint().y;
//
//
//	float xInvEntry, yInvEntry;
//	float xInvExit, yInvExit;
//
//	// find the distance between the objects on the near and far sides for both x and y 
//	if (vx > 0.0f)
//	{
//		xInvEntry = targetMinX - sourceMaxX;
//		xInvExit = targetMaxX - sourceMinX;
//	}
//	else
//	{
//		xInvEntry = targetMaxX - sourceMinX;
//		xInvExit = targetMinX - sourceMaxX;
//	}
//
//	if (vy > 0.0f)
//	{
//		yInvEntry = targetMinY - sourceMaxY;
//		yInvExit = targetMaxY - sourceMinY;
//	}
//	else
//	{
//		yInvEntry = targetMaxY - sourceMinY;
//		yInvExit = targetMinY - sourceMaxY;
//	}
//
//
//
//	// find time of collision and time of leaving for each axis (if statement is to prevent divide by zero) 
//	float xEntry, yEntry;
//	float xExit, yExit;
//
//	if (vx == 0.0f)
//	{
//		xEntry = -std::numeric_limits<float>::infinity();
//		xExit = std::numeric_limits<float>::infinity();
//	}
//	else
//	{
//		xEntry = xInvEntry / vx;
//		xExit = xInvExit / vx;
//	}
//
//	if (vy == 0.0f)
//	{
//		yEntry = -std::numeric_limits<float>::infinity();
//		yExit = std::numeric_limits<float>::infinity();
//	}
//	else
//	{
//		yEntry = yInvEntry / vy;
//		yExit = yInvExit / vy;
//	}
//
//	// find the earliest/latest times of collisionfloat 
//	float entryTime = std::max(xEntry, yEntry);
//	float exitTime = std::min(xExit, yExit);
//
//	// if there was no collision
//	if (entryTime > exitTime || xEntry < 0.0f && yEntry < 0.0f || xEntry > 1.0f || yEntry > 1.0f)
//	{
//		aNormal.x = 0.0f;
//		aNormal.y = 0.0f;
//		return 1.0f;
//	}
//	else
//	{
//		std::cout << "Collision Swapth\n";
//
//		// Collision occured
//		// calculate normal of collided surface
//		if (xEntry > yEntry)
//		{
//			if (xInvEntry < 0.0f)
//			{
//				aNormal.x = 1.0f;
//				aNormal.y = 0.0f;
//			}
//			else
//			{
//				aNormal.x = -1.0f;
//				aNormal.y = 0.0f;
//			}
//		}
//		else
//		{
//			if (yInvEntry < 0.0f)
//			{
//				aNormal.x = 0.0f;
//				aNormal.y = 1.0f;
//			}
//			else
//			{
//				aNormal.x = 0.0f;
//				aNormal.y = -1.0f;
//			}
//		} // return the time of collisionreturn entryTime; 
//		
//		return entryTime;
//	}
//}

//void ResolveCollisionSwept(Entity* aSource, Hi_Engine::Physics::AABB2D<float> aOther)
//{
//	CU::Vector2<float> normal;
//	float penetration = 0.f;
//
//	bool result = SweptAABBTest(*aSource->GetComponent<HitboxComponent>(), aOther, penetration, normal);
//
//	if (result)
//	{
//		aSource->GetComponent<TransformComponent>()->CurrentPos.x += (normal.x * penetration);
//		aSource->GetComponent<TransformComponent>()->CurrentPos.z += (normal.y * penetration);
//	}
//}




//
//bool Intersecting(const Hi_Engine::Physics::AABB2D<float>& A1, VelocityComponent& aVelocity, const Hi_Engine::Physics::AABB2D<float>& A2, float& entryTime, float& exitTime)
//{
//	auto& velocity = aVelocity.Velocity;
//
//	float xInvEntry, yInvEntry;
//	float xInvExit, yInvExit;
//
//
//	// Find the distance between the objects on the near and far sides for both x and y
//	if (velocity.x > 0.0f) {
//		xInvEntry = (A2.GetMinPoint().x - A1.GetMaxPoint().x) / velocity.x;   // (other.x - (x + width)) / velocity.x;
//		xInvExit = (A2.GetMaxPoint().x - A1.GetMinPoint().x) / velocity.x;   // ((other.x + other.width) - x) / velocity.x;
//	}
//	else {
//		xInvEntry = (A2.GetMaxPoint().x - A1.GetMinPoint().x) / velocity.x; // ((other.x + other.width) - x) / velocity.x;
//		xInvExit = (A2.GetMinPoint().x - A1.GetMaxPoint().x) / velocity.x; // (other.x - (x + width)) / velocity.x;
//	}
//
//
//	if (velocity.y > 0.0f) {
//		yInvEntry = (A2.GetMinPoint().y - A1.GetMaxPoint().y) / velocity.z; // (other.y - (y + height)) / velocity.y;
//		yInvExit = (A2.GetMaxPoint().y - A1.GetMinPoint().y) / velocity.z;  //((other.y + other.height) - y) / velocity.y;
//	}
//	else {
//		yInvEntry = (A2.GetMaxPoint().y - A1.GetMinPoint().y) / velocity.z; // ((other.y + other.height) - y) / velocity.y;
//		yInvExit =		(A2.GetMinPoint().y - A1.GetMaxPoint().y) / velocity.z; // (other.y - (y + height)) / velocity.y;
//	}
//
//
//	// Find the time of collision and time of leaving for each axis
//	float entryTimeX = std::max(xInvEntry, yInvEntry);
//	float exitTimeX = std::min(xInvExit, yInvExit);
//
//
//	// If there's no collision along the x-axis
//	if (entryTimeX > exitTimeX || xInvEntry < 0.0f || xInvEntry > 1.0f) {
//		entryTime = 0.0f;
//		exitTime = 1.0f;
//		return false;
//	}
//
//
//	// If there's a collision along the x-axis, check the y-axis
//	float entryTimeY = std::max(xInvEntry, yInvEntry);
//	float exitTimeY = std::min(xInvExit, yInvExit);
//
//
//	// If there's no collision along the y-axis
//	if (entryTimeY > exitTimeY || yInvEntry < 0.0f || yInvEntry > 1.0f) {
//		entryTime = 0.0f;
//		exitTime = 1.0f;
//		return false;
//	}
//
//
//	// There is a collision along both axes, find the earliest time of collision
//	entryTime = std::max(entryTimeX, entryTimeY);
//	exitTime = std::min(exitTimeX, exitTimeY);
//
//
//	return true;
//}

void CollisionSystem::LateUpdate(float aDeltaTime)
{
	if (!m_entityManager)
		return;

	UpdateColliders();

	auto entities = m_entityManager->FindAll<ColliderComponent>();


	for (int i = 0; i < entities.size(); ++i)
	{
		for (int j = i + 1; j < entities.size(); ++j)
		{
			if (CanCollide(entities[i], entities[j]))
			{
				auto* collider1 = entities[i]->GetComponent<ColliderComponent>();
				auto* collider2 = entities[j]->GetComponent<ColliderComponent>();

				if (collider1->Type == eColliderType::Trigger || collider2->Type == eColliderType::Trigger)
				{
					if (Hi_Engine::Physics::Intersects(collider1->Collider, collider2->Collider))
					{
						// sstd::cout << "Is triggerred\n";

						PostMaster::GetInstance().SendMessage({ eMessage::TriggerActivated, (collider1->Type == eColliderType::Trigger ? entities[i] : entities[j]) });
						// Send event..?!

						// Remove trigger component?
					}
				}
			}
		}
	}


	//for (auto& entity : entities)
	//{
	//	// check if any dynamic is colliding with any triggers?

	//	auto* collider = entity->GetComponent<ColliderComponent>();

	//	// Check is triggers are 
	//	if (collider->Type == eColliderType::Trigger)
	//	{
	//		for (auto& dynamic : entities)
	//		{
	//			auto* dynamicCollider = entity->GetComponent<ColliderComponent>();

	//			if (dynamicCollider->Type != eColliderType::Dynamic)
	//				continue;



	//			//if (dynamic == ent)
	//		}
	//	}
	//	
	//}


	//auto entities = m_entityManager->FindAll<HitboxComponent, TransformComponent>();
	//auto entities = m_entityManager->FindAll<PlayerControllerComponent, TransformComponent>();
	//
	//for (auto& entity : entities)
	//{
	//	auto* hitbox = entity->GetComponent<HitboxComponent>(); // rename HitboxComponent to BoxCollider? or something?

	//	if (hitbox->IsStatic)
	//		continue;

	//	// TODO; check object vs object collisions...

	//	HandleTileCollisions(entity, aDeltaTime);
	//}
}

void CollisionSystem::UpdateColliders()
{
	auto entities = m_entityManager->FindAll<ColliderComponent>();

	for (auto& entity : entities)
	{
		auto* transformComponent = entity->GetComponent<TransformComponent>();
		auto* velocityComponent = entity->GetComponent<VelocityComponent>();

		if (auto* attackCollider = entity->GetComponent<AttackComponent>())
		{
			const auto& velocity = velocityComponent->Velocity;

			auto& aabb = attackCollider->Collider;
			auto& offset = attackCollider->Offset;

			// Update collider offset
			auto colliderWidth = aabb.GetWidth();

			offset.x = velocity.x > 0.f ? colliderWidth : velocity.x < 0.f ? -colliderWidth : 0;
			offset.y = velocity.y > 0.f ? colliderWidth : velocity.y < 0.f ? -colliderWidth : 0;
			//offset.z = velocity.z > 0.f ? colliderWidth : velocity.z < 0.f ? -colliderWidth : 0;

			// Update collider position
			const auto position = transformComponent->CurrentPos + attackCollider->Offset;

			float halfWidth = aabb.GetWidth() * 0.5f;
			float halfHeight = aabb.GetHeight() * 0.5f;

			aabb.Init({ position.x - halfWidth, position.y - halfHeight }, { position.x + halfWidth, position.y + halfHeight });
		}

		if (auto* hitboxCollider = entity->GetComponent<HitboxComponent>())
		{
			auto& aabb = hitboxCollider->Collider;
			const auto position = transformComponent->CurrentPos;

			float halfWidth = aabb.GetWidth() * 0.5f;
			float halfHeight = aabb.GetHeight() * 0.5f;

			aabb.Init({ position.x - halfWidth, position.y - halfHeight }, { position.x + halfWidth, position.y + halfHeight });
		}

		if (auto* collider = entity->GetComponent<ColliderComponent>())
		{
			if (collider->Type == eColliderType::Dynamic)
			{
				auto& aabb = collider->Collider;
				const auto position = transformComponent->CurrentPos;

				float halfWidth = aabb.GetWidth() * 0.5f;
				float halfHeight = aabb.GetHeight() * 0.5f;

				aabb.Init({ position.x - halfWidth, position.y - halfHeight }, { position.x + halfWidth, position.y + halfHeight });
			}
		}
	}
}

//Entity* CollisionSystem::GetMapChunkContainingEntity(const Entity* anEntity)
//{
//	auto mapChunks = m_entityManager->FindAll<MapChunkComponent>();
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

bool CollisionSystem::CanCollide(Entity* aFirst, Entity* aSecond) const
{
	auto* collider1 = aFirst->GetComponent<ColliderComponent>();
	auto* collider2 = aSecond->GetComponent<ColliderComponent>();

	if (collider1->Type == eColliderType::Dynamic || collider2->Type == eColliderType::Dynamic)
		return true;

	return false;
}

void CollisionSystem::CheckMapCollisions(Entity* anEntity)
{
	//// auto entityPosition = anEntity->GetComponent<TransformComponent>()->m_currentPos;
	//
	//// Check all 4 corners of the collider...?

	//auto hitbox = anEntity->GetComponent<HitboxComponent>();

	//// temp
	//auto center = hitbox->Collider.GetCenter();

	//auto mapChunk = MapUtils::GetMapChunkAtPosition(m_entityManager->FindAll<MapChunkComponent>(), center);
	//Tile* tile = MapUtils::GetTileAtWorldPosition(mapChunk, center);
	//if (!tile)
	//	return;

	//if (tile->IsCollidable)
	//{
	//	Hi_Engine::Physics::AABB2D<float> tileBounds;
	//	tileBounds.Init({ tile->Position.x, tile->Position.y }, { tile->Position.x + 1.f, tile->Position.y + 1.f });

	//	auto hitbox = anEntity->GetComponent<HitboxComponent>()->Collider;
	//	auto& velocity = anEntity->GetComponent<VelocityComponent>()->Velocity;

	//	// Dont check against the dynamic?
	//	CommonUtilities::Vector2<float> contactPoint;
	//	CommonUtilities::Vector2<float> contactNormal;
	//	float contactTime = 0.f;
	//	float dt = 0.01f;

	//	if (Hi_Engine::Physics::Intersects(hitbox, { velocity.x, velocity.z }, tileBounds, { 0.f, 0.f }, contactPoint, contactNormal, contactTime, dt))
	//	{
	//		CommonUtilities::Vector2 vec = CommonUtilities::Vector2(std::abs(velocity.x), std::abs(velocity.z)) * (1 - contactTime);
	//		velocity.x += contactNormal.x * vec.x;
	//		velocity.z += contactNormal.y * vec.y;
	//	}

	//	// ResolveCollision(anEntity, tile);
	//	
	//}








	////std::cout << "Tile: " << tile->m_coordinates.x << ", " << tile->m_coordinates.y << '\n';

	//// get tile player is occupying...


	//
	//







	//// check if mapChunks contains player's position?!

	////for (auto& mapChunk : someMapChunks)
	////{
	////	auto mapChunkChunk = mapChunk->GetComponent<MapChunkComponent>();
	////	auto chunkTransform = mapChunk->GetComponent<TransformComponent>();
	////	auto chunkPosition = chunkTransform->m_currentPos;

	////	if (entityPosition.x < chunkPosition.x || entityPosition.z < chunkPosition.z)
	////		continue;

	////	if (entityPosition.x > chunkPosition.x + mapChunkChunk->m_width || entityPosition.y > chunkPosition.y + mapChunkChunk->m_height)
	////		continue;

}

void CollisionSystem::ResolveCollision(Entity* anEntity, Tile* aTile)
{
	// Move first x, then y-axis? each step check collisions...
	
	auto transformComponent = anEntity->GetComponent<TransformComponent>();
	transformComponent->CurrentPos = transformComponent->PreviousPos;

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
//
//float CollisionSystem::SweptAABB(Entity* anEntity)
//{
//	auto* hitbox = anEntity->GetComponent<HitboxComponent>();
//	auto* velocity = anEntity->GetComponent<VelocityComponent>();
//
//
//
//
//	return 0.f;
//}

void CollisionSystem::HandleTileCollisions(Entity* anEntity, float aDeltaTime)
{
	if (!anEntity)
		return;

	auto* transformComponent = anEntity->GetComponent<TransformComponent>();
	auto* velocityComponent = anEntity->GetComponent<VelocityComponent>();
	auto* hitboxComponent = anEntity->GetComponent<HitboxComponent>();

	auto& collider = hitboxComponent->Collider;

	// Scaled bounds
	auto center = collider.GetCenter();
	auto scaledSize = collider.GetSize() * 2.f;

	Hi_Engine::Physics::AABB2D<float> collisionsBounds{ center - scaledSize, center + scaledSize };


	// Get the mapchunks around the player (4 corners of the hitbox)
	std::vector<Entity*> mapChunks;

	auto* chunk = MapUtils::GetMapChunkAtPosition(m_entityManager->FindAll<MapChunkComponent>(), hitboxComponent->Collider.GetCenter());



	auto* mapChunk = MapUtils::GetMapChunkAtPosition(m_entityManager->FindAll<MapChunkComponent>(), hitboxComponent->Collider.GetCenter());

	if (!mapChunk)
		return;

	auto* mapChunkComponent = mapChunk->GetComponent<MapChunkComponent>();
	const auto& mapChunkPosition = mapChunk->GetComponent<TransformComponent>()->CurrentPos;
	//const auto& tiles = mapChunkComponent->Tiles;
	auto& tiles = mapChunkComponent->Tiles;


	//std::vector<std::pair<int, float>> z; // index and contact time?!
	std::vector<std::pair<int, Hi_Engine::HitResult<float>>> results;

	// Calculate order of the collision checks
	for (int i = 0; i < tiles.size(); ++i)
	{
		if (tiles[i].Type == eTile::Sand)
			continue;

		tiles[i].Color = { 0.4f, 0.4f, 0.4f, 1.f };

		static float size = 1.f; // FIX!

		glm::vec3 position = { mapChunkPosition.x, mapChunkPosition.y, mapChunkPosition.y };
		position.x += tiles[i].Coordinates.x * size;
		position.z += tiles[i].Coordinates.y * size;

		Hi_Engine::Physics::AABB2D<float> tileBounds({ position.x, position.z }, { position.x + size, position.y + size });


		// Draw map AABB...


		Hi_Engine::HitResult<float> result = Hi_Engine::Physics::Intersects(hitboxComponent->Collider, { velocityComponent->Velocity.x, velocityComponent->Velocity.y }, tileBounds, aDeltaTime);

		std::cout << result.IsColliding << "\n";

		if (result.IsColliding)
		{
			results.push_back({ i, result });
		}
	}

	//continue;
	// sort the result (deal with closes collisions first)
	std::sort(results.begin(), results.end(), [](const std::pair<int, Hi_Engine::HitResult<float>>& a, const std::pair<int, Hi_Engine::HitResult<float>>& b)
	{
		return a.second.ContactTime < b.second.ContactTime;
	});


	for (const auto& result : results)
	{
		CommonUtilities::Vector2<float> vec = CommonUtilities::Vector2(std::abs(velocityComponent->Velocity.x), std::abs(velocityComponent->Velocity.y)) * (1 - result.second.ContactTime);
		velocityComponent->Velocity.x += result.second.ContactNormal.x * vec.x;
		velocityComponent->Velocity.y += result.second.ContactNormal.y * vec.y;
	}

}