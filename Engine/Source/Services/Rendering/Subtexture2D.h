#pragma once
#include <../../../ThirdParty/glm/glm.hpp>

namespace Hi_Engine
{
	// TODO; store subteuxtre as nested type in ttextrue?

	struct SubtextureData
	{
		std::string TextureName;
		int Row;
		int Column;

		bool operator==(const SubtextureData& other) const {
			return (TextureName == other.TextureName && Row == other.Row && Column == other.Column);
		}
	};

	class Texture2D;

	// Rework this class!! is it redudnat? when is it used?? currently spritecomponent stores id...
	class Subtexture2D 
	{
	public:
		Subtexture2D(const Texture2D& texture);
		//Subtexture2D(Texture2D& texture, const glm::vec2& min, const glm::vec2& max);

		void Init(const rapidjson::Value& value); // remove?

		void Init(const glm::vec2& min, const glm::vec2& max); // FIX!

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
		const Texture2D& m_texture; // TODO; store as referene or raw pointer????? or id to it...
		glm::vec2	m_texCoords[4];
		glm::vec2	m_size;
		std::string m_name;
		bool		m_isInverted;

		// STORE SIZE?
	};
}

template <>
struct std::hash<Hi_Engine::SubtextureData> {

	std::size_t operator()(const Hi_Engine::SubtextureData& subtexture) const {
		std::size_t res = 17;
		res = res * 31 + std::hash<std::string>()(subtexture.TextureName);
		res = res * 31 + std::hash<int>()(subtexture.Row);
		res = res * 31 + std::hash<int>()(subtexture.Column);

		return res;
	}
};