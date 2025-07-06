#include "Pch.h"
#include "ResourceLoader.h"
#include "Core/Utility/JsonUtils.h"
#include <Dependencies/rapidjson/document.h> 

#include "Services/ServiceRegistry.h"
#include "Services/Rendering/Texture2D.h"

namespace Hi_Engine
{
	inline const std::string TextureDirectory{ "../Game/Assets/Textures/" };

	void LoadTexturesFromJson(ServiceRegistry& registry, const std::filesystem::path& path)
	{
		auto& textureService = registry.Get<TextureAssetService>();
		auto& subTextureService = registry.Get<SubtextureAssetService>();

		auto document = JsonUtils::LoadJsonDocument(path);

		for (const auto& entry : document.GetArray())
		{
			std::string id = entry["id"].GetString();
			std::string path = TextureDirectory + entry["path"].GetString();
			std::string filtering = entry["filtering"].GetString();

			auto texture = std::make_shared<Texture2D>();
			texture->Init(id, path, filtering);
			
			textureService.Insert(texture->GetName(), texture);





			int rows = entry["rows"].GetInt();
			int cols = entry["cols"].GetInt();

			const auto& [textureWidth, textureHeight] = texture->GetSize();

			float spriteWidth = (float)textureWidth / cols;
			float spriteHeight = (float)textureHeight / rows;

			for (int row = rows - 1; row >= 0; --row)
			{
				for (int col = cols - 1; col >= 0; --col)
				{
					float minX = (col * spriteWidth) / textureWidth;
					float minY = (row * spriteHeight) / textureHeight;
					float maxX = ((col + 1) * spriteWidth) / textureWidth;
					float maxY = ((row + 1) * spriteHeight) / textureHeight;

					auto subtexture = std::make_shared<Subtexture2D>(*texture);
					subtexture->Init(glm::vec2{ minX, minY }, glm::vec2{ maxX, maxY }); // or store reference / raw pointer?

					int invertedRow = (rows - 1) - row;
					subTextureService.Insert({ texture->GetName(), invertedRow, (int)col }, std::move(subtexture));
					//ResourceHolder<Subtexture2D, SubtextureData>::GetInstance().Insert({ m_name, invertedRow, (int)col }, subtexture);
				}
			}
		}
	}

	void LoadShadersFromJson(ShaderAssetService& service, const std::filesystem::path& path)
	{
		auto document = JsonUtils::LoadJsonDocument(path);

		service.Clear(); // TEST:..

		for (const auto& entry : document.GetArray())
		{
			auto shader = std::make_shared<GLSLShader>();
			if (shader)
			{
				shader->Init(entry);
				const auto& name = shader->GetName();
				service.Insert(name, std::move(shader)); // FIX! 
				//service.Insert(shader->GetName(), std::move(shader)); // FIX! 
			}
		}
	}

	void LoadAudioFromJson(AudioAssetService& service, const std::filesystem::path& path)
	{
		auto document = JsonUtils::LoadJsonDocument(path);

		for (const auto& entry : document.GetArray())
		{
			auto audioSource = std::make_shared<AudioSource>();
			audioSource->Init(entry); // read data her instead?+

			const auto& name = audioSource->GetName();
			service.Insert(name, std::move(audioSource)); // FIX! 
		}
	}
}