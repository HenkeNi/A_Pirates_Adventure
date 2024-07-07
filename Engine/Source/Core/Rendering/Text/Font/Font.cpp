#include "Pch.h"
#include "Font.h"
#include <Rendering/Texture/Texture2D.h>
#include "../../../Resources/ResourceHolder.h"
#include "Dependencies/FreeType/include/ft2build.h"
#include "Rendering/Text/Renderer/TextRenderer.h"

namespace Hi_Engine
{
	void Font::Init(const rapidjson::Value& value)
	{
		m_name = value["name"].GetString();
		std::string path = value["filepath"].GetString();
		int size = value["size"].GetInt();


		
		// Load font as face
		FT_Face face;
		if (FT_New_Face(TextRenderer::ft, path.c_str(), 0, &face))
			assert(false && "ERROR: Failed to load font");

		// Set size to load glyphs as
		FT_Set_Pixel_Sizes(face, 0, size);

		// Disable byte-alignment restriction
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		const auto& glyph = face->glyph;

		// Compile, and store, the first 128 ASCII characters
		for (unsigned char c = 0; c < 128; ++c)
		{
			// Load character glyph 
			if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			{
				std::cout << "ERROR: Failed to load Glyph\n";
				continue;
			}

			std::string identifier = m_name + "_" + std::to_string(c);
			auto texture = std::make_unique<Texture2D>();
			//texture->SetFormat(GL_RED);
			//texture->SetFiltering(true);
			texture->Create({ (int)glyph->bitmap.width, (int)glyph->bitmap.rows }, GL_RED, true, glyph->bitmap.buffer);

			ResourceHolder<Texture2D>::GetInstance().Insert(identifier, std::move(texture));
			//ResourceHolder<Texture2D>::GetInstance().GetResource(identifier)
			//	.Create({ (int)glyph->bitmap.width, (int)glyph->bitmap.rows }, glyph->bitmap.buffer);

			Character character;
			character.Size = { glyph->bitmap.width, glyph->bitmap.rows };
			character.m_bearing = { (int)glyph->bitmap_left, (int)glyph->bitmap_top };
			character.m_textureID = identifier;
			character.m_advance = glyph->advance.x;

			AddCharacter(c, std::move(character));
		}

		glBindTexture(GL_TEXTURE_2D, 0);

		// destroy FreeType once we're finished
		FT_Done_Face(face);
		FT_Done_FreeType(TextRenderer::ft);
	}

	void Font::AddCharacter(const char key, const Character& character)
	{
		m_characters.insert_or_assign(key, character);
	}
}