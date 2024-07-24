#pragma once
#include "../../Base/System.h"

// Combine inventory and equipment?
class EquipmentSystem : public System, public Subscriber
{
public:
	EquipmentSystem();
	~EquipmentSystem();

	void Receive(Message& message)	override;
	void Update(float deltaTime)	override;

private:
	bool EquipItem(Entity owner, Entity item);
};