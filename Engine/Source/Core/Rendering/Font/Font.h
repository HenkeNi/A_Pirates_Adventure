#pragma once
#include "Data/Structs.h"


namespace Hi_Engine
{
	class TextRenderer;

	class Font
	{
	public:
		void AddCharacter(const char aKey, const Character& aCharacter);

	private:
		friend class TextRenderer;

		std::unordered_map<GLchar, Character> m_characters;	// replace with just char?
	};
}