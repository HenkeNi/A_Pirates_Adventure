#pragma once
#include "../World/World.h"
#include "../ECS/Factory/EntityFactory.h"

#include "Registry/RegistryAliases.h"

namespace Hi_Engine
{
	class ServiceRegistry;

	struct RegistryContext
	{
		std::weak_ptr<SceneRegistry> SceneRegistry;
		std::weak_ptr<SystemRegistry> SystemRegistry;
		std::weak_ptr<ComponentRegistry> ComponentRegistry;
	};

	class Scene
	{
	public:
		Scene(ServiceRegistry& registry);
		virtual ~Scene() = default;	

		void Update(float deltaTime);
		void Enter(SceneID id); //  -> update ECSRegitry with new world?
		void Exit();

		virtual bool IsTransparent() const;

		virtual void OnCreated() {};
		virtual void OnDestroyed() {};

	protected:
		virtual void OnUpdate(float deltaTime) {};
		virtual void OnEnter() {}; // handle loading of systems in engine?
		virtual void OnExit() {};

		World m_world; // or inverse relationship??

		RegistryContext m_registryContext; // private?
		ServiceRegistry& m_serviceRegistry;

		// Put in factory struct?
		EntityFactory m_entityFactory;
		//SystemFactory m_systemFactory; // private?
	};
}