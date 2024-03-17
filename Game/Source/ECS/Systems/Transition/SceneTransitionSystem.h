#pragma once
#include "../Base/System.h"

class SceneTransitionSystem : public System
{
public:
	SceneTransitionSystem();
	~SceneTransitionSystem();

	void Receive(Message& message)	override;
	void Update(float deltaTime)	override;
};