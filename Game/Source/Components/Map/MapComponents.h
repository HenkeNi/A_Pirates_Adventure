#pragma once
#include "../Base/ComponentBase.h"
#include "../../Data/Structs.h"
#include <vector>
#include <Utility/Math/Vectors/Vector3.hpp>

namespace CU = CommonUtilities;

struct MapChunkComponent : public ComponentBase
{
	CU::Vector2<int>	m_coordinates;
	// CU::Vector3<float>	m_position; - stored in TransformComponent
	std::vector<Tile>	m_tiles;
	unsigned			m_width, m_height;		// replace with size??


	//	unsigned				m_chunkID;

	// neighbours??
};