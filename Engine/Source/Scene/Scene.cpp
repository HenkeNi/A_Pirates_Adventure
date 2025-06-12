#include "Pch.h"
#include "Scene.h"
#include "Registry/TypeRegistry.h"

namespace Hi_Engine
{
	Scene::Scene(RegistryContext context)
		: m_registryContext{ std::move(context) }, m_entityFactory{ m_world }
	{
	}

	void Scene::Update(float deltaTime)
	{
		m_world.Update(deltaTime);
		OnUpdate(deltaTime);
	}

	void Scene::Enter(SceneID id)
	{
		const auto& [weakSceneRegistry, weakSystemRegistry] = m_registryContext;

		if (auto sceneRegistry = weakSceneRegistry.lock())
		{
			auto& sceneEntry = sceneRegistry->Get(id);
			
			auto document = JsonUtils::LoadJsonDocument(sceneEntry.JsonPath);

			//std::string system = JsonUtils::GetJsonValue<std::string>(document["systems"].GetObject(), "systems");

			std::vector<std::string> systems;
			for (const auto& system : document["systems"].GetArray())
			{
				bool isActive = false;

				if constexpr (Utils::IsDebugBuild())
				{
					isActive = system["debug"].GetBool();
				}
				else
				{
					isActive = system["release"].GetBool();
				}

				if (isActive)
				{
					systems.push_back(system["type"].GetString());
				}
			}

			for (const auto& system : systems)
			{

				if (auto systemRegistry = weakSystemRegistry.lock())
				{
					const auto& systemEntry = systemRegistry->Get(system);

					auto id = systemEntry.ID;

					// TODO;  Load systems...

					//m_world.AddSystem();
				}

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