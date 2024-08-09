#pragma once
#include "../../Base/System.h"


class SpriteAnimationSystem : public System
{
public:
	SpriteAnimationSystem();
	~SpriteAnimationSystem();

	void Update(float deltaTime)	override;
	void SetSignature() override;

private:
	std::string GetCurrentState(Entity entity) const; // ???

	void UpdateSpriteOrientation(struct VelocityComponent* velocityComponent, struct TransformComponent* transformComponent);
};