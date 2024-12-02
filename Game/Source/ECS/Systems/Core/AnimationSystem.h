#pragma once
#include "../Base/System.h"


class AnimationSystem : public System
{
public:
	AnimationSystem();
	~AnimationSystem();

	void Update(float deltaTime) override;
	void SetSignature()			 override;

private:
	void SelectAnimation(Entity entity);
	void UpdateAnimation(float deltaTime, Entity entity);

	void OnAnimationFinished();
};