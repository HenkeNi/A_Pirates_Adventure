#pragma once
#include <cstdint>
#include <string>

namespace Hi_Engine::Constants
{
	constexpr size_t MaxQuadCount	= 10000;				// uint32_t instead??
	constexpr size_t MaxVertexCount = MaxQuadCount * 4;
	constexpr size_t MaxIndexCount	= MaxQuadCount * 6;

	constexpr uint32_t MaxTextureSlots = 32;		// Or max textures?

	inline const std::string TextureDirectory{ "../Game/Assets/Textures/" };
	//constexpr double PI = 3.14159;
}	