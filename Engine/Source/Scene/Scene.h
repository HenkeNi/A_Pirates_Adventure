#pragma once
#include "../ECS/ECSCore.h"
#include "../ECS/Core/SystemManager.h"

namespace Hi_Engine
{	
	class Scene
	{
	public:
		virtual ~Scene() = default;

		void Update(float deltaTime);
		virtual bool IsTransparent() const;

		virtual void OnCreated() {};
		virtual void OnDestroyed() {};
		virtual void OnEnter() {}; // handle loading of systems in engine?
		virtual void OnExit() {};

	protected:	
		virtual void OnUpdate(float deltaTime) {};
	
		ECSCore m_ecs;
		std::string m_filePath;

	private:
		SystemManager m_systemManager;
	};
}