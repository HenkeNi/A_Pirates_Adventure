#pragma once
#include "../Base/System.h"

class Entity;

class CollisionSystem : public System
{
public:
	CollisionSystem();
	~CollisionSystem();

	void Receive(Message& message)		override;
	void LateUpdate(float deltaTime)	override;

	static bool CanCollide(Entity* first, Entity* second);

private:
	void AlignCollider(Entity* entity);
	void AlignDynamicColliders(std::vector<Entity*>& entities);

	void ResetColliders(std::vector<Entity*>& entities);
	void HandleEntityCollisions(std::vector<Entity*>& entities); // rename EntityVsEntity collisions?

	//void UpdateDynamicColliders();
	// void AdjustColliderPosition(Entity* entity);



	// TODO; have a collision grid that gets updated when objects are placed in the world...

	// void HandleObjectCollisions(Entity* entity, float aDeltaTime);
	void HandleTileCollisions(Entity* entity, float deltaTime);
	void CheckMapCollisions(Entity* entity);
	void ResolveCollision(Entity* entity, struct Tile* tile);

	// Check collisions
	// Handle Collision / Resolve Collisions


// OR maybe colliders are just small structs (min/max) and free floating functions... DOWNSIDE=> visually debugging collider is less accurate..


	// float SweptAABB(Entity* entity);
};