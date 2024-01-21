#pragma once
#include "../Base/System.h"

//class MapChunk;

class Entity;

class CollisionSystem : public System
{
public:
	CollisionSystem();
	~CollisionSystem();

	// maybe init/or  function => sets colliders to their correct position?!

	void Init();

	void Receive(Message& aMsg)			override;
	void LateUpdate(float aDeltaTime)	override;

	// Entity* GetMapChunkContainingEntity(const Entity* anEntity);	// move to MapGenerationSystem?

	// TODO; abstract collision checks into functions that can be called from other systems


private:
	bool CanCollide(Entity* aFirst, Entity* aSecond) const;

	// TODO; have a collision grid that gets updated when objects are placed in the world...

	// void HandleObjectCollisions(Entity* anEntity, float aDeltaTime);
	void HandleTileCollisions(Entity* anEntity, float aDeltaTime);

	void CheckMapCollisions(Entity* anEntity);

	void ResolveCollision(Entity* anEntity, struct Tile* aTile);

	// Check collisions
	// Handle Collision / Resolve Collisions

	//7std::vector<MapChunk*> m_mapChunks;



	// float SweptAABB(Entity* anEntity);
};

