#pragma once
#include "../../Base/System.h"

class Entity;

class SpriteAnimationSystem : public System
{
public:
	SpriteAnimationSystem();
	~SpriteAnimationSystem();

	void Receive(Message& aMsg)		override;
	void Update(float aDeltaTime)	override;

private:
	std::string GetCurrentState(Entity* anEntity) const; // ???

	void UpdateSpriteOrientation(struct VelocityComponent* aVelocityComponent, struct TransformComponent* aTransformComponent);

};