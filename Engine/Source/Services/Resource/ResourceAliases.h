#pragma once
#include "ResourceService.h"
#include "Services/Rendering/Texture2D.h"
#include "Services/Rendering/Subtexture2D.h"
#include "Services/Audio/AudioSource.h"
#include "Services/Rendering/Shader.h"

namespace Hi_Engine
{
	using TextureAssetService = ResourceService<Texture2D>;
	using SubtextureAssetService = ResourceService<Subtexture2D, SubtextureData>; // SubtextureService instead?
	using AudioAssetService = ResourceService<AudioSource>;
	using ShaderAssetService = ResourceService<GLSLShader>;
	//using FontService = ResourceService<Font>;

}