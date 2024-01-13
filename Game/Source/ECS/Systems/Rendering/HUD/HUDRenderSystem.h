#pragma once
#include "../../Base/System.h"

class HUDRenderSystem : public System
{
public:
	HUDRenderSystem();
	~HUDRenderSystem();

	void Receive(Message& aMsg)	override;
	void Draw()					override;
};