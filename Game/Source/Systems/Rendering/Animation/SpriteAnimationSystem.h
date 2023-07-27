#pragma once
#include "Base/System.h"

class SpriteAnimationSystem : public System
{
public:
	SpriteAnimationSystem();
	~SpriteAnimationSystem();

	void Receive(Message& aMsg)		override;
	void Update(float aDeltaTime)	override;

	// void Draw()					override;
};

