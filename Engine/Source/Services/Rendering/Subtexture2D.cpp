#include "Pch.h"
#include "Subtexture2D.h"
#include "Texture2D.h"
//#include "Services/Resource/ResourceService.h"
#include "Dependencies/stb_image/stb_image.h"

namespace Hi_Engine
{
	//Subtexture2D::Subtexture2D(Texture2D& texture, const glm::vec2& min, const glm::vec2& max)
	Subtexture2D::Subtexture2D(const Texture2D& texture)
		: m_texture{ texture }, m_isInverted{ false }
	{
	}

	void Subtexture2D::Init(const rapidjson::Value& value)
	{
		std::string parent = value["parent_id"].GetString();
		// m_texture = ResourceHolder<Texture2D>::GetInstance().GetResource(parent);

		float minX = value["min_uv"][0].GetFloat();
		float minY = value["min_uv"][1].GetFloat();

		float maxX = value["max_uv"][0].GetFloat();
		float maxY = value["max_uv"][1].GetFloat();

		m_name = value["id"].GetString();

		m_texCoords[0] = { minX, minY };
		m_texCoords[1] = { maxX, minY };
		m_texCoords[2] = { maxX, maxY };
		m_texCoords[3] = { minX, maxY };

		float width  = maxX - minX;
		float height = maxY - minY;
		m_size = { m_size.x * width, m_size.y * height };
	}

	void Subtexture2D::Init(const glm::vec2& min, const glm::vec2& max)
	{
		//m_texture = texture;
		float width = max.x - min.x;
		float height = max.y - min.y;
		m_size = { m_size.x * width, m_size.y * height };

		m_texCoords[0] = { min.x, min.y };
		m_texCoords[1] = { max.x, min.y };
		m_texCoords[2] = { max.x, max.y };
		m_texCoords[3] = { min.x, max.y };
	}

	const Texture2D& Subtexture2D::GetTexture() const
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

	//Subtexture2D& Subtexture2D::CreateFromCoords(Texture2D& texture, const glm::vec2& coords, const glm::vec2& spriteSize)
	//{
	//	auto textureSize = texture.GetSize();

	//	glm::vec2 min	= { (coords.x * spriteSize.x) / textureSize.x, (coords.y * spriteSize.y) / textureSize.y };
	//	glm::vec2 max		= { ((coords.x + 1) * spriteSize.x) / textureSize.x, ((coords.y + 1) * spriteSize.y) / textureSize.y };

	//	Subtexture2D result{ texture, min, max };
	//	return result;
	//}

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