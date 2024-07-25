#pragma once
#include "../../Base/System.h"

/* Make sure, gets rendered after sprite/tiles */
class TextRenderSystem : public System
{
public:
	TextRenderSystem();
	~TextRenderSystem();

	void Draw() override;
	void SetSignature() override;
};