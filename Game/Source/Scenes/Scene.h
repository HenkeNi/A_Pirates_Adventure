#pragma once

class SceneManager;

namespace Hi_Engine
{
	class ECSCoordinator;
}

class Scene
{
public:
	//Scene(Hi_Engine::ECSCoordinator& ecs);
	virtual ~Scene() = default;

	virtual void Update(float deltaTime)	  = 0;
	virtual bool IsTransparent()			const;

	virtual void OnCreated()				   {};
	virtual void OnDestroyed()				   {};
	virtual void OnEnter()					   {};
	virtual void OnExit()					   {};

protected:	
	friend class SceneManager;

	//SharedContext m_sharedContext;
	//Hi_Engine::ECSCoordinator& m_ecs; //REMOVE? 
};