#pragma once
#include "../../Base/System.h"

// TODO; just have a RenderSystem?
class SpriteRenderSystem : public System
{
public:
	SpriteRenderSystem();
	~SpriteRenderSystem();

	void Receive(Message& message)	override;
	void Draw()						override;
};