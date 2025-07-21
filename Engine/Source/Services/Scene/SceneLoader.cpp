#include "Pch.h"
#include "SceneLoader.h"
#include "Services/ServiceRegistry.h"
#include "Registry/RegistryAliases.h"
#include "ECS/World/World.h"
#include "ECS/Factory/EntityFactory.h"

#include "ECS/Utility/EntityHandle.h"
#include "Scene/Scene.h"

namespace Hi_Engine
{
	std::vector<std::string> GetEnabledSystemTypes(const rapidjson::Document& doc)
	{
		std::vector<std::string> result;

		for (const auto& system : doc["systems"].GetArray())
		{
			const bool isActive = Utils::IsDebugBuild() ? system["debug"].GetBool() : system["release"].GetBool();

			// TODO; check if system is alread fetched! find...

			if (isActive )
				result.push_back(system["type"].GetString());
		}

		return result;
	}

	bool SceneLoader::Load(Scene& scene, const std::filesystem::path& jsonPath)
	{
		auto document = JsonUtils::LoadJsonDocument(jsonPath);

		if (!LoadSystems(scene, document))
		{
			Logger::LogError("[SceneLoader::Load] - Failed to load system!");
			return false;
		}

		if (!LoadEntities(scene, document))
		{
			Logger::LogError("[SceneLoader::Load] - Failed to load entities!");
			return false;
		}

		return true;
	}

	bool SceneLoader::Load(Scene& scene, SceneID id)
	{
		auto sceneRegistry = scene.m_serviceRegistry.TryGet<SceneRegistryService>();
		if (!sceneRegistry)
		{
			Logger::LogError("[SceneLoader::Load] - SceneRegistryService unavailable!");
			return false;
		}
		
		const auto& sceneEntry = sceneRegistry->Get(id);
		return Load(scene, sceneEntry.JsonPath);
	}

	bool SceneLoader::Unload(Scene& scene)
	{
		return false;
	}

	void SceneLoader::CancelLoading()
	{
	}

	bool SceneLoader::LoadEntities(Scene& scene, const rapidjson::Document& doc)
	{
		if (!doc.HasMember("entities") || !doc["entities"].IsArray())
		{
			return false;
		}

		auto* componentRegistry = scene.m_serviceRegistry.TryGet<ComponentRegistryService>();

		if (!componentRegistry)
		{
			Logger::LogError("[SceneLoader::LoadEntiites] - ComponentRegistryService unavailable!");
			return false;
		}

		for (const auto& entity : doc["entities"].GetArray())
		{
			std::string name = entity["entity_id"].GetString();

			auto optionalHandle = scene.m_entityFactory.CreateFromPrefab(scene.m_world, name);

			if (!optionalHandle.has_value())
			{
				Logger::LogWarning("[EntityFactory] - Failed to create entity!");
				continue;
			}

			auto& entityHandle = optionalHandle.value();

			if (!entity.HasMember("components_data") || !entity["components_data"].IsArray())
				continue;

			for (const auto& data : entity["components_data"].GetArray())
			{
				std::string type = data["type"].GetString();

				const auto& componentEntry = componentRegistry->Get(type); // move? or use string view?

				componentEntry.AddComponentFunc(entityHandle);

				auto componentProperties = GetProperties(data);
				componentEntry.InitFunc(entityHandle, componentProperties);
			}
		}
	}

	bool SceneLoader::LoadSystems(Scene& scene, const rapidjson::Document& doc)
	{
		if (!doc.HasMember("systems") || !doc["systems"].IsArray())
		{
			return false;
		}

		auto* systemRegistry = scene.m_serviceRegistry.TryGet<SystemRegistryService>();

		if (!systemRegistry)
		{
			Logger::LogError("[SceneLoader::LoadSystems] - SystemRegistryService unavailable!");
			return false;
		}

		const auto systems = GetEnabledSystemTypes(doc);

		for (const auto& name : systems)
		{
			const auto& systemEntry = systemRegistry->Get(name);
			auto system = systemEntry.CreatorFunction(scene.m_world, scene.m_serviceRegistry);

			scene.m_world.InsertSystem(std::move(system), systemEntry.Type);
		}
	}
}