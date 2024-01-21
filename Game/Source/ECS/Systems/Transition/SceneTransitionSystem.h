#pragma once
#include "../Base/System.h"

class SceneTransitionSystem : public System
{
public:
	SceneTransitionSystem();
	~SceneTransitionSystem();

	void Receive(Message& aMsg)		override;
	void Update(float aDeltaTime)	override;
};