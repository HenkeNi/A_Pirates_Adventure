#pragma once
#include "../../Base/System.h"


class SpriteRenderSystem : public System
{
public:
	SpriteRenderSystem();
	~SpriteRenderSystem();

	void Receive(Message& aMsg)	override;
	void Draw()					override;
};