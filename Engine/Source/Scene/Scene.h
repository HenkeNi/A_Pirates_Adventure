#pragma once
#include "ECS/ECSCore.h"
#include "ECS/Core/SystemManager.h"

namespace Hi_Engine
{
	// class SceneManager;
	
	class Scene
	{
	public:
		virtual ~Scene() = default;

		void Update(float deltaTime);
		virtual bool IsTransparent()			const;

		virtual void OnCreated()				   {};
		virtual void OnDestroyed()				   {};
		virtual void OnEnter()					   {}; // handle loading of systems in engine?
		virtual void OnExit()					   {};

		//void Update(float deltaTime)
		//{
		//	//m_systemManager.ForEachSystem([&](System& system) { system.Update(deltaTime); }); // measure execution here?? or in systme manager? i.e how long each system takes..
		//}

	protected:	
		virtual void OnUpdate(float deltaTime)		{};
		//friend class SceneManager; // remove?

		//SharedContext m_sharedContext;

		ECSCore m_ecs;
		SystemManager m_systemManager; // private?
	};
}