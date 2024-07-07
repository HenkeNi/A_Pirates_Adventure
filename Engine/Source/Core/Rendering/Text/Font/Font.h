#pragma once
// #include "Data/Structs.h"
#include "../../../../Data/Structs.h"
//#include <../../../ThirdParty/GLEW/include/GL/glew.h> // use typedef for GLchar?
// #include <Dependencies/GLEW/include/GL/glew.h>
//#include <Dependencies/GLEW/include/GL/glew.h>

typedef char GLchar;

namespace Hi_Engine
{
	struct Character
	{
		std::string		m_textureID;
		glm::ivec2		Size = { 0, 0 };       // Size of glyph
		glm::ivec2		m_bearing = { 0, 0 };    // Offset from baseline to left/top of glyph
		unsigned int	m_advance = 0;    // Offset to advance to next glyph
	};


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