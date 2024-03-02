#pragma once
#include "../../Base/System.h"


class EquipmentSystem : public System
{
public:
	EquipmentSystem();
	~EquipmentSystem();

	void Receive(Message& aMsg)		override;
	void Update(float aDeltaTime)	override;

private:
	bool EquipItem(class Entity* anOwner, class Entity* anItem);
};