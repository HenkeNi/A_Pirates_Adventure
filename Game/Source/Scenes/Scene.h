#pragma once
#include "../Data/Structs.h"
#include "EntityManager.h"
#include "SystemManager.h"

// Rework to handle Scene transitions...
// set order of systems...

class Scene
{
public:
	Scene(SharedContext aContext);
	virtual ~Scene() = default;

	virtual void Update(float aDeltaTime)			= 0;
	virtual void LateUpdate(float aDeltaTime)		= 0;	
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