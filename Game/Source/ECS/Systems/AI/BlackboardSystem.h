#pragma once
#include "../Base/System.h"

class BlackboardSystem : public System
{
public:
	BlackboardSystem();
	~BlackboardSystem();

	void Update(float deltaTime)	override;

private:
	void SetPlayerPosition();
};