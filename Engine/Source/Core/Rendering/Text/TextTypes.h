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

	struct Text
	{
		glm::vec2	Position;
		glm::vec4	Color;
		glm::vec2	TexCoords;
		//float		TexIndex;
	};



	//struct Character
	//{
	//	GLuint TextureID;   // ID handle of the glyph texture
	//	glm::ivec2 Size;    // Size of glyph
	//	glm::ivec2 Bearing; // Offset from baseline to left/top of glyph
	//	GLuint Advance;     // Offset to advance to next glyph
	//};
}