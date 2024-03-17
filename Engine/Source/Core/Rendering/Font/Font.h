#pragma once
// #include "Data/Structs.h"
#include "../../../Data/Structs.h"

namespace Hi_Engine
{
	class TextRenderer;
	// struct Character;

	class Font
	{
	public:
		void AddCharacter(const char key, const Character& character);

	private:
		friend class TextRenderer;

		std::unordered_map<GLchar, Character> m_characters;	// replace with just char?
	};
}