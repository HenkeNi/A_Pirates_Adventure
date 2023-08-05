#pragma once
#include "Base/System.h"

/* Make sure, gets rendered after sprite/tiles */
class TextRenderSystem : public System
{
public:
	TextRenderSystem();
	~TextRenderSystem();

	void Receive(Message& aMsg)	override;
	void Draw()					override;
};