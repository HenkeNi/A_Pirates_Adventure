#pragma once
#include "../../Base/System.h"

class UIRenderSystem : public System
{
public:
	UIRenderSystem();
	~UIRenderSystem();

	void Receive(Message& aMsg)	override;
	void Draw()					override;

private:
	void RenderHUD();
	void RenderUI();
};