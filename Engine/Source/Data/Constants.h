#pragma once

namespace Hi_Engine::Constants
{
	constexpr float gravity = 9.8f;

	constexpr size_t maxQuadCount	= 10000;				// uint32_t instead??
	constexpr size_t maxVertexCount = maxQuadCount * 4;
	constexpr size_t maxIndexCount	= maxQuadCount * 6;

	constexpr uint32_t maxTextureSlots = 32;		// Or max textures?
	//constexpr uint32_t maxTextureSlots = 32;

}