#pragma once
#include "../World/World.h"
#include "../ECS/Factory/EntityFactory.h"
#include "../ECS/Factory/SystemFactory.h"

//#include "Registry/RegistryEntries.h" // causes circular dependencies?s
#include "Registry/RegistryAliases.h"

namespace Hi_Engine
{
	//class SystemRegistry;

	struct RegistryContext
	{
		std::weak_ptr<SceneRegistry> SceneRegistry;
		std::weak_ptr<SystemRegistry> SystemRegistry;
	};

	class Scene
	{
	public:
		Scene(RegistryContext context);
		virtual ~Scene() = default;	

		//Scene(const RegistryContext& context);

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

		RegistryContext m_registryContext;

		//std::weak_ptr<SceneRegistry> m_sceneRegistry; // need both Scene and System Registry?

		// Put in factory struct?
		EntityFactory m_entityFactory;
		SystemFactory m_systemFactory; // private?
	};
}