#pragma once


class TextureManager
{
public:

	bool IsTextureBound(unsigned texID, float& outTexIndex);


private:
	static constexpr int MaxTextureSlots = 23;

	std::array<uint32_t, MaxTextureSlots> m_textureSlots;

	uint32_t	m_currentTextureSlotIndex = 1; // texture 0 == white texture...

	GLuint		m_whiteTexture = 0;
	uint32_t	m_whiteTextureSlot = 0;
};