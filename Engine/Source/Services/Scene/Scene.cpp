#include "Pch.h"
#include "Scene.h"
#include "Registry/TypeRegistry.h"
#include "Services/ServiceRegistry.h"
#include "ECS/Utility/EntityHandle.h"

namespace Hi_Engine
{
	Scene::Scene(ServiceRegistry& registry)
		: m_serviceRegistry{ registry }, m_entityFactory{ m_world, registry.TryGetWeak<PrefabRegistryService>(), registry.TryGetWeak<ComponentRegistryService>() }
	{
		m_registryContext.SceneRegistry = m_serviceRegistry.TryGetWeak<SceneRegistryService>();
		m_registryContext.SystemRegistry = m_serviceRegistry.TryGetWeak<SystemRegistryService>();
		m_registryContext.ComponentRegistry = m_serviceRegistry.TryGetWeak<ComponentRegistryService>();
	}

	void Scene::Update(float deltaTime)
	{
		m_world.Update(deltaTime);
		OnUpdate(deltaTime);
	}

	bool Scene::IsTransparent() const
	{
		return false;
	}
}