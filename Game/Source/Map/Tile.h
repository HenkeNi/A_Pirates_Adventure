#pragma once
#include "../Data/Enumerations.h"


struct Tile
{
	// Texture and shader
	Hi_Engine::Material		m_material; // Pointer? -> shared..?

	eTile m_type;
	CU::Vector4<float>		m_color = { 1.f, 1.f, 1.f, 1.f };
	//glm::vec2				m_size; // make static?
	float					m_size = 1.f; // make static?
	unsigned				m_textureID;
	CU::Vector2<unsigned>	m_chunkCoordinates; // or index? m_columnIndex; m_rowIndex;
};