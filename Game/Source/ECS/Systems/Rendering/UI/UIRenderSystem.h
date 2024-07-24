#pragma once
#include "../../Base/System.h"


class UIRenderSystem : public System
{
public:
	UIRenderSystem();
	~UIRenderSystem();

	void Draw() override;
	void SetSignature() override;

private:
	// void RenderHUD();
	void RenderUI();
	//void RenderInventory(); // FIX! somehow

	//void RenderGrid(); // Test!

	// Put in math namespace instad??

	FVector2 ConvertToScreenCoordinates(const FVector2& normalizedPosition, const FVector2& screenSize) const;
};