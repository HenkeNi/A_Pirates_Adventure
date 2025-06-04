#pragma once
#include "../World/World.h"

namespace Hi_Engine
{	
	class Scene
	{
	public:
		virtual ~Scene() = default;	

		void Update(float deltaTime);
		//void Enter(); -> update ECSRegitry with new world?

		virtual bool IsTransparent() const;

		virtual void OnCreated() {};
		virtual void OnDestroyed() {};
		virtual void OnEnter() {}; // handle loading of systems in engine?
		virtual void OnExit() {};

	protected:
		virtual void OnUpdate(float deltaTime) {};
	
		// Store SystemManager here?? static?
		// static ECSRegistry??	
		World m_world; // or inverse relationship??
		std::string m_filePath;
	};
}