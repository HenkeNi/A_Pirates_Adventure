#include "Pch.h"
#include "Font.h"


namespace Hi_Engine
{
	void Font::AddCharacter(const char key, const Character& character)
	{
		m_characters.insert_or_assign(key, character);
	}
}