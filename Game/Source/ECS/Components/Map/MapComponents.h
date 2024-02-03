#pragma once
#include "../Base/Component.h"
//#include "../../DataTypes/Structs.h"
#include <vector>
#include <Utility/Math/Vectors/Vector3.hpp>

namespace CU = CommonUtilities;

struct MapChunkComponent : public Component
{
	CU::Vector2<int>	Coordinates;
	// CU::Vector3<float>	m_position; - stored in TransformComponent
	std::vector<Tile>	Tiles;
	unsigned			Width, Height;		// replace with size?? Transform instead??


	//	unsigned				m_chunkID;

	// neighbours??

	// HERE? or a new component...
	std::vector<Hi_Engine::SpriteRenderData> RenderData;

};