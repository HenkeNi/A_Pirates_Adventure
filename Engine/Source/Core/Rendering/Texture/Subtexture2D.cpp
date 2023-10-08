#include "Pch.h"
#include "Subtexture2D.h"


namespace Hi_Engine
{
	Subtexture2D::Subtexture2D(Texture2D& aTexture, const glm::vec2& aMin, const glm::vec2& aMax)
		: m_texture{ aTexture }, m_isInverted{ false }
	{
		m_texCoords[0] = { aMin.x, aMin.y };
		m_texCoords[1] = { aMax.x, aMin.y };
		m_texCoords[2] = { aMax.x, aMax.y };
		m_texCoords[3] = { aMin.x, aMax.y };
	}

	const Texture2D& Subtexture2D::GetTexture()	const
	{
		return m_texture;
	}

	const glm::vec2* Subtexture2D::GetTexCoords() const
	{
		return m_texCoords;
	}

	Subtexture2D& Subtexture2D::CreateFromCoords(Texture2D& aTexture, const glm::vec2& someCoords, const glm::vec2& aSpriteSize)
	{
		auto textureSize = aTexture.GetSize();

		glm::vec2 min	= { (someCoords.x * aSpriteSize.x) / textureSize.x, (someCoords.y * aSpriteSize.y) / textureSize.y };
		glm::vec2 max		= { ((someCoords.x + 1) * aSpriteSize.x) / textureSize.x, ((someCoords.y + 1) * aSpriteSize.y) / textureSize.y };

		Subtexture2D result{ aTexture, min, max };
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