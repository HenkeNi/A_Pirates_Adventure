#pragma once
#include <string>

namespace Constants
{
	constexpr const char* Filepath = "../Bin/Assets/";	// place in dir class??

	constexpr unsigned MapChunkLength = 10;
	constexpr unsigned MapChunkSize = MapChunkLength * MapChunkLength;

	constexpr std::size_t MaxEntities = 5000;
}