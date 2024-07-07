#pragma once
#include <../../../ThirdParty/glm/glm.hpp>

namespace Hi_Engine
{
	class Texture2D;

	class Subtexture2D
	{
	public:
		Subtexture2D();
		//Subtexture2D(Texture2D& texture, const glm::vec2& min, const glm::vec2& max);

		void Init(const rapidjson::Value& value);

		void Temp(Texture2D* texture, const glm::vec2& min, const glm::vec2& max);

		const Texture2D& GetTexture()	const;
		const glm::vec2* GetTexCoords() const;
		// const glm::vec2* GetInvertedTexCoords() const;

		const glm::vec2& GetSize() const;
		inline const std::string& GetName() const { return m_name; }

		// Maybe remove??
		// static Subtexture2D& CreateFromCoords(Texture2D& texture, const glm::vec2& coords, const glm::vec2& spriteSize);

		void Invert();
		bool IsInverted() const;

	private:
		Texture2D*	m_texture;
		glm::vec2	m_texCoords[4];
		glm::vec2	m_size;
		std::string m_name;
		bool		m_isInverted;

		// STORE SIZE?
	};
}