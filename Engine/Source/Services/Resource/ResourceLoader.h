#pragma once
#include "ResourceAliases.h"
//#include "Resource/ResourceAliases.h" 

namespace Hi_Engine
{
	void LoadTexturesFromJson(class ServiceRegistry& registry, const std::filesystem::path& path);

	void LoadShadersFromJson(ShaderAssetService& service, const std::filesystem::path& path);

	void LoadAudioFromJson(AudioAssetService& service, const std::filesystem::path& path);
}