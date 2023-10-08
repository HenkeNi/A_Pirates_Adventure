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



		m_invertedTexCoords[0] = m_texCoords[1];
		m_invertedTexCoords[1] = m_texCoords[0];
		m_invertedTexCoords[2] = m_texCoords[3];
		m_invertedTexCoords[3] = m_texCoords[2];
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

	void Subtexture2D::SetCoords(const glm::vec2* someTexCoords)
	{
		for (int i = 0; i < 4; ++i)
		{
			m_texCoords[i] = someTexCoords[i];

			// TODO; update inverted...
		}
	}

	void Subtexture2D::Invert()
	{
		//glm::vec2 min = { (someCoords.x * aSpriteSize.x) / textureSize.x, (someCoords.y * aSpriteSize.y) / textureSize.y };
		//glm::vec2 max = { ((someCoords.x + 1) * aSpriteSize.x) / textureSize.x, ((someCoords.y + 1) * aSpriteSize.y) / textureSize.y };

		auto temp = m_texCoords[0];

		m_texCoords[0] = m_texCoords[1];
		m_texCoords[1] = temp;

		auto temp2 = m_texCoords[2];
		m_texCoords[2] = m_texCoords[3];
		m_texCoords[3] = temp2;


		// m_texCoords[0] = { aMin.x, aMin.y };	// Upper left
		// m_texCoords[1] = { aMax.x, aMin.y };	// Upper right
		// m_texCoords[2] = { aMax.x, aMax.y };	// Lower right
		// m_texCoords[3] = { aMin.x, aMax.y };	// Lower left
	
		m_isInverted = !m_isInverted;
	}

	bool Subtexture2D::IsInverted() const
	{
		return m_isInverted;
	}
}