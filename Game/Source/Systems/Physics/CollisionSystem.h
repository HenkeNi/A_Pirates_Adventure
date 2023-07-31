#pragma once
#include "Base/System.h"

//class MapChunk;

class Entity;

class CollisionSystem : public System
{
public:
	CollisionSystem();
	~CollisionSystem();

	// maybe init/or  function => sets colliders to their correct position?!

	void Receive(Message& aMsg)			override;
	void LateUpdate(float aDeltaTime)	override;

	// Entity* GetMapChunkContainingEntity(const Entity* anEntity);	// move to MapGenerationSystem?

	// TODO; abstract collision checks into functions that can be called from other systems


private:
	void CheckMapCollisions(Entity* anEntity);

	void ResolveCollision();

	// Check collisions
	// Handle Collision / Resolve Collisions

	//7std::vector<MapChunk*> m_mapChunks;
};

