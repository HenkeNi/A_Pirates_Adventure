#include "Pch.h"
#include "Font.h"


namespace Hi_Engine
{
	void Font::AddCharacter(const char aKey, const Character& aCharacter)
	{
		m_characters.insert_or_assign(aKey, aCharacter);
	}
}