#pragma once
#include <../../../ThirdParty/glm/glm.hpp>

namespace Hi_Engine
{
	class Texture2D;

	class Subtexture2D
	{
	public:
		Subtexture2D(Texture2D& aTexture, const glm::vec2& aMin, const glm::vec2& aMax);

		const Texture2D& GetTexture()	const;
		const glm::vec2* GetTexCoords() const;
		const glm::vec2* GetInvertedTexCoords() const;

		// Maybe remove??
		static Subtexture2D& CreateFromCoords(Texture2D& aTexture, const glm::vec2& someCoords, const glm::vec2& aSpriteSize);

		void SetCoords(const glm::vec2* someTexCoords);	// remove?

		void Invert(); // reanem: FLip?
		bool IsInverted() const;



	private:
		Texture2D&	m_texture;
		glm::vec2	m_texCoords[4];


		glm::vec2	m_invertedTexCoords[4]; // TEST...

		bool m_isInverted;	// Temp
	};
}