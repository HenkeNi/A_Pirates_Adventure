#pragma once
#include "ResourceService.h"
#include "../Rendering/Texture2D.h"
#include "../Rendering/Subtexture2D.h"
#include "../Audio/AudioClip.h"
#include "../Rendering/Shader.h"

namespace Hi_Engine
{
	using TextureAssetService = ResourceService<std::string, Texture2D>;
	using SubtextureAssetService = ResourceService<SubtextureData, Subtexture2D>; // SubtextureService instead?
	using AudioAssetService = ResourceService<std::string, AudioClip>;
	using ShaderAssetService = ResourceService<std::string, GLSLShader>;
	//using FontService = ResourceService<Font>;

}