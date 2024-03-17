#pragma once
//#include "../Data/Structs.h"
#include "ECS/Entities/EntityManager.h"
#include "ECS/Systems/SystemManager.h"

// Rework to handle Scene transitions...
// set order of systems...

class Scene
{
public:
	Scene(SharedContext context);
	virtual ~Scene() = default;

	virtual void Update(float deltaTime)			= 0;
	virtual void LateUpdate(float deltaTime)		= 0;	
	virtual void Draw()						const	= 0;
	virtual bool IsTransparent()			const;

	virtual void OnCreated()				   {};
	virtual void OnDestroyed()				   {};
	virtual void OnEnter()					   {};
	virtual void OnExit()					   {};

protected:	
	SharedContext m_sharedContext;
	EntityManager m_entityManager;
};