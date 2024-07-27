#pragma once
#include "../Base/System.h"

class RenderSystem : public System
{
public:
	RenderSystem();
	~RenderSystem();

	void Draw() override;
	void SetSignature() override;

private:
	void RenderMap(Entity camera);
	void RenderSprites(Entity camera);
	void RenderText(Entity camera);
	void RenderDebug(Entity camera);
};
