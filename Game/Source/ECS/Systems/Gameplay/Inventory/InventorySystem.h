#pragma once
#include "../../Base/System.h"


// Handles gathering of resources
class InventorySystem : public System
{
public:
	InventorySystem();
	~InventorySystem();

	void Receive(Message& message)	override;
	void Update(float deltaTime)	override;

	static bool CanPickup(Entity* entity);

private:
	bool CollectItem(class Entity* owner, class Entity* item);
};