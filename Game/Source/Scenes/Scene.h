#pragma once

class SceneManager;
class ECS;

class Scene
{
public:
	Scene(ECS& ecs);
	virtual ~Scene() = default;

	virtual void Update(float deltaTime)			= 0;
	virtual void LateUpdate(float deltaTime)		 {};
	virtual void Draw()						const	= 0;
	virtual bool IsTransparent()			const;

	virtual void OnCreated()				   {};
	virtual void OnDestroyed()				   {};
	virtual void OnEnter()					   {};
	virtual void OnExit()					   {};

protected:	
	friend class SceneManager;

	//SharedContext m_sharedContext;
	std::vector<class System*> m_systems;
	ECS& m_ecs;
};