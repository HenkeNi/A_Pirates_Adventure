#pragma once
#include "../../Base/System.h"


// Handles gathering of resources
class InventorySystem : public System
{
public:
	InventorySystem();
	~InventorySystem();

	void Receive(Message& aMsg)		override;
	void Update(float aDeltaTime)	override;
private:


};