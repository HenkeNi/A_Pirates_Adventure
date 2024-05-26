#pragma once

namespace Hi_Engine
{
	enum class eTextAlginment
	{
		Align_Left,
		Align_Center,
		Align_Right,
		Align_Top,
		Align_Bottom
	};

	struct TextRenderData
	{
		class GLSLShader* GLSLShader;
		class Font* Font;
		float				Scale;
		FVector4			Color;
		FVector2			Position; //??
		std::string			Text;
		eTextAlginment		Alignment;
	};
}