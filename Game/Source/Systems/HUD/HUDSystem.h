#pragma once
#include "Base/System.h"


class HUDSystem : public System
{
public:
	HUDSystem();
	~HUDSystem();

	void Receive(Message& aMsg)		override;
	void Update(float aDeltaTime)	override;

private:

};