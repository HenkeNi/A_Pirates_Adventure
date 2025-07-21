#pragma once
#include "SceneTypes.h"

namespace Hi_Engine
{
	class Scene;

	class SceneLoader
	{
	public:
		bool Load(Scene& scene, const std::filesystem::path& jsonPath);
		bool Load(Scene& scene, SceneID id);
		bool Unload(Scene& scene);

		//void LoadAsync(Scene& scene, std::function<void(bool)> callback);
		void CancelLoading();

	private:
		bool LoadEntities(Scene& scene, const rapidjson::Document& doc);
		bool LoadSystems(Scene& scene, const rapidjson::Document& doc);
	};
}