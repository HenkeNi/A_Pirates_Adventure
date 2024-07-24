#pragma once
#include "../../Base/System.h"


// Handles gathering of resources
class InventorySystem : public System, public Subscriber
{
public:
	InventorySystem();
	~InventorySystem();

	void Receive(Message& message)	override;
	void Update(float deltaTime)	override;

	static bool CanPickup(Entity entity);

private:
	bool CollectItem(Entity owner, Entity item);
};