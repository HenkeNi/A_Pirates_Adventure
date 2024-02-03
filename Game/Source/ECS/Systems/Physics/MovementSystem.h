#pragma once
#include "../Base/System.h"

class Entity;

// Move camera, crosshair here? or in a followsystem? TeleportComponnet => desired position,,
class MovementSystem : public System
{
public:
	MovementSystem();
	~MovementSystem();

	void Receive(Message& aMsg)		override;
	void Update(float aDeltaTime)	override;

	static bool	HasMoved(const Entity* anEntity);

private:

	// maybe do in Collision System? or maybe colliders dont have a direct position... rename update compoennts?
	//void UpdateColliders(Entity* anEntity); // Collisio nsysem should update! otherwise collsion resolution, etc will not update collider, and startign entities that dont move wont have collider in right place..
};

// OR maybe colliders are just small structs (min/max) and free floating functions... DOWNSIDE=> visually debugging collider is less accurate..