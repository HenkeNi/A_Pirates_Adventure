#pragma once
#include "Base/System.h"

class Entity;

// rename AnimationSystem?
class SpriteAnimationSystem : public System
{
public:
	SpriteAnimationSystem();
	~SpriteAnimationSystem();

	void Receive(Message& aMsg)		override;
	void Update(float aDeltaTime)	override;

	// void Draw()					override;

private:

	std::string GetCurrentState(Entity* anEntity) const; // ???
};

