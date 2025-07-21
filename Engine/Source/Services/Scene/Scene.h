#pragma once
#include "../ECS/World/World.h"
#include "../ECS/Factory/EntityFactory.h"

#include "Registry/RegistryAliases.h"

namespace Hi_Engine
{
	class ServiceRegistry;
	class SceneLoader;

	struct RegistryContext
	{
		std::weak_ptr<SceneRegistryService> SceneRegistry;
		std::weak_ptr<SystemRegistryService> SystemRegistry;
		std::weak_ptr<ComponentRegistryService> ComponentRegistry;
	};

	class Scene
	{
	public:
		Scene(ServiceRegistry& registry);
		virtual ~Scene() = default;	

		void Update(float deltaTime);
		virtual void OnEnter() {};
		virtual void OnExit() {};

		virtual void OnCreated() {};
		virtual void OnDestroyed() {};

		virtual bool IsTransparent() const;
		
	protected:
		friend class SceneLoader;

		virtual void OnUpdate(float deltaTime) {};

		World m_world; // or inverse relationship??

		RegistryContext m_registryContext; // private?
		ServiceRegistry& m_serviceRegistry;

		EntityFactory m_entityFactory;
	};
}