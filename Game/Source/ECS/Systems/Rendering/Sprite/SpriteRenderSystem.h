#pragma once
#include "../../Base/System.h"

// TODO; just have a RenderSystem?
class SpriteRenderSystem : public System
{
public:
	SpriteRenderSystem();
	~SpriteRenderSystem();

	void Draw() override;
	void SetSignature() override;
};