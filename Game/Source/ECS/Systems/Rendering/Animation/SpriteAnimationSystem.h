#pragma once
#include "../../Base/System.h"

class Entity;

class SpriteAnimationSystem : public System
{
public:
	SpriteAnimationSystem();
	~SpriteAnimationSystem();

	void Update(float deltaTime)	override;

private:
	std::string GetCurrentState(Entity* entity) const; // ???

	void UpdateSpriteOrientation(struct VelocityComponent* velocityComponent, struct TransformComponent* transformComponent);
};