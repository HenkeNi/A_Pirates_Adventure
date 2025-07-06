#pragma once
// #include "Data/Structs.h"
//#include <../../../ThirdParty/GLEW/include/GL/glew.h> // use typedef for GLchar?
// #include <Dependencies/GLEW/include/GL/glew.h>
//#include <Dependencies/GLEW/include/GL/glew.h>
#include <../Dependencies/rapidjson/document.h>

typedef char GLchar;

// TODO; put in Render types?

namespace Hi_Engine
{
	struct Character
	{
		std::string		m_textureID;
		glm::ivec2		Size = { 0, 0 };       // Size of glyph
		glm::ivec2		m_bearing = { 0, 0 };    // Offset from baseline to left/top of glyph
		unsigned int	m_advance = 0;    // Offset to advance to next glyph
	};

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
		std::shared_ptr<class GLSLShader> GLSLShader; // weak ptr instead? or raw
		std::shared_ptr<class Font> Font;
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

	class TextRenderer;
	// struct Character;

	class Font
	{
	public:
		void Init(const rapidjson::Value& value);
		void AddCharacter(const char key, const Character& character);
		inline const std::string& GetName() const { return m_name; }

	private:
		friend class TextRenderer;

		std::unordered_map<GLchar, Character> m_characters;	// replace with just char?
		std::string m_name;
	};
}