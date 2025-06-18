#include "Pch.h"
#include "Scene.h"
#include "Registry/TypeRegistry.h"
#include "Service/ServiceRegistry.h"
#include "ECS/Utility/EntityHandle.h"

namespace Hi_Engine
{
	std::vector<std::string> GetEnabledSystemTypes(const rapidjson::Document& doc)
	{
		std::vector<std::string> result;

		for (const auto& system : doc["systems"].GetArray())
		{
			const bool isActive = Utils::IsDebugBuild() ? system["debug"].GetBool() : system["release"].GetBool();

			if (isActive)
				result.push_back(system["type"].GetString());
		}

		return result;
	}

	Scene::Scene(ServiceRegistry& registry)
		: m_serviceRegistry{ registry }, m_entityFactory{ m_world, registry.TryGetWeak<PrefabRegistry>(), registry.TryGetWeak<ComponentRegistry>() }
	{
		m_registryContext.SceneRegistry = m_serviceRegistry.TryGetWeak<SceneRegistry>();
		m_registryContext.SystemRegistry = m_serviceRegistry.TryGetWeak<SystemRegistry>();
		m_registryContext.ComponentRegistry = m_serviceRegistry.TryGetWeak<ComponentRegistry>();
	}

	void Scene::Update(float deltaTime)
	{
		m_world.Update(deltaTime);
		OnUpdate(deltaTime);
	}

	void Scene::Enter(SceneID id)
	{
		const auto& [weakSceneRegistry, weakSystemRegistry, weakComponentRegistry] = m_registryContext;

		auto sceneRegistry = weakSceneRegistry.lock();
		if (!sceneRegistry)
		{
			Logger::LogError("[Scene::Enter] - SceneRegistry was invalid!");
			return;
		}

		auto systemRegistry = weakSystemRegistry.lock();
		if (!systemRegistry)
		{
			Logger::LogError("[Scene::Enter] - SystemRegistry was invalid!");
			return;
		}

		auto componentRegistry = weakComponentRegistry.lock();
		if (!componentRegistry)
		{
			Logger::LogError("[Scene::Enter] - ComponentRegistry was invalid!");
			return;
		}

		const auto& sceneEntry = sceneRegistry->Get(id);
		auto document = JsonUtils::LoadJsonDocument(sceneEntry.JsonPath);

		const auto systems = GetEnabledSystemTypes(document);

		for (const auto& name : systems)
		{
			const auto& systemEntry = systemRegistry->Get(name);
			auto system = systemEntry.CreatorFunction(m_world, m_serviceRegistry);

			m_world.InsertSystem(std::move(system));
		}

		
		// get components
		for (const auto& entity : document["entities"].GetArray())
		{
			std::string name = entity["entity_id"].GetString();  // or prefab?? rename in json??

			auto optionalHandle = m_entityFactory.CreateFromPrefab(m_world, name);

			if (!optionalHandle.has_value())
			{
				Logger::LogWarning("Failed to create entity");
				continue;
			}

			auto& entityHandle = optionalHandle.value();

			for (const auto& data : entity["components_data"].GetArray())
			{
				std::string type = data["type"].GetString();

				const auto& componentEntry = componentRegistry->Get(type);

				componentEntry.AddComponentFunc(entityHandle);

				auto componentProperties = GetProperties(data);
				componentEntry.InitFunc(entityHandle, componentProperties);
			}
		}

		OnEnter();
	}

	void Scene::Exit()
	{
		// clear systems..
	}

	bool Scene::IsTransparent() const
	{
		return false;
	}
}