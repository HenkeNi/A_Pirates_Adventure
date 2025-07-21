#pragma once
#include "ResourceAliases.h"
//#include "Resource/ResourceAliases.h" 

namespace Hi_Engine
{
	class TextureLoader
	{
	public:
		static void LoadFromJson(TextureAssetService& textureAssets, SubtextureAssetService& subtextureAssets, const std::filesystem::path& path);
	};

	class ShaderLoader
	{
	public:
		static void LoadFromJson(ShaderAssetService& service, const std::filesystem::path& path);
	};

	class AudioService;

	class AudioLoader
	{
	public:
		static void LoadFromJson(AudioService& audioService, AudioAssetService& assetService, const std::filesystem::path& path);
	};
}