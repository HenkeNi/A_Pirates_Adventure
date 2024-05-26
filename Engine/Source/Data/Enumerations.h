#pragma once

namespace Hi_Engine
{
	enum class ePriority
	{
		Low, 
		Moderate, 
		High, 
		NotSpecified
	};

	enum class eWindowEvent
	{
		None, 
		Resize, 
		LostFocus, 
		GainedFocus,
		Close
	};

	enum class eRenderCommandType
	{
		SetShader,
		SetCamera,
		SetProjectionMatrix,
		DrawSprite,
		DrawBatch
	};
}