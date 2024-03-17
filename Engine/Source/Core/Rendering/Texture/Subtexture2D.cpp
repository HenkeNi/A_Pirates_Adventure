#include "Pch.h"
#include "Subtexture2D.h"


namespace Hi_Engine
{
	Subtexture2D::Subtexture2D(Texture2D& texture, const glm::vec2& min, const glm::vec2& max)
		: m_texture{ texture }, m_isInverted{ false }
	{
		m_texCoords[0] = { min.x, min.y };
		m_texCoords[1] = { max.x, min.y };
		m_texCoords[2] = { max.x, max.y };
		m_texCoords[3] = { min.x, max.y };

		auto textureSize = texture.GetSize();

		float width  = max.x - min.x;
		float height = max.y - min.y;
		m_size = { textureSize.x * width, textureSize.y * height };
	}

	const Texture2D& Subtexture2D::GetTexture()	const
	{
		return m_texture;
	}

	const glm::vec2* Subtexture2D::GetTexCoords() const
	{
		return m_texCoords;
	}

	const glm::vec2& Subtexture2D::GetSize() const
	{
		return m_size;
	}

	Subtexture2D& Subtexture2D::CreateFromCoords(Texture2D& texture, const glm::vec2& coords, const glm::vec2& spriteSize)
	{
		auto textureSize = texture.GetSize();

		glm::vec2 min	= { (coords.x * spriteSize.x) / textureSize.x, (coords.y * spriteSize.y) / textureSize.y };
		glm::vec2 max		= { ((coords.x + 1) * spriteSize.x) / textureSize.x, ((coords.y + 1) * spriteSize.y) / textureSize.y };

		Subtexture2D result{ texture, min, max };
		return result;
	}

	void Subtexture2D::Invert()
	{
		std::swap(m_texCoords[0], m_texCoords[1]);
		std::swap(m_texCoords[2], m_texCoords[3]);
	
		m_isInverted = !m_isInverted;
	}

	bool Subtexture2D::IsInverted() const
	{
		return m_isInverted;
	}
}