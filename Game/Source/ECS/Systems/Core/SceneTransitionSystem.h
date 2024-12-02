#pragma once
#include "../Base/System.h"

// Remove unless needed for animations etc?
class SceneTransitionSystem : public System, public Subscriber
{
public:
	SceneTransitionSystem();
	~SceneTransitionSystem();

	void Receive(Message& message)	override;
	void Update(float deltaTime)	override;
	void SetSignature()				override;
};