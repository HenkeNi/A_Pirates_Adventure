#pragma once
#include "../Entity/EntityManager.h"
#include "../Systems/SystemManager.h"
#include "../Managers/ObjectManager.h"

class SceneManager;

// Rework to handle Scene transitions...
// set order of systems...

class Scene
{
public:
	Scene(SharedContext aContext);
	virtual ~Scene() = default;

	virtual void Update(float aDeltaTime)		  = 0;
	virtual void LateUpdate(float aDeltaTime)	  = 0;	
	virtual void Draw()						const = 0;
	virtual bool IsTransparent()			const;

	virtual void OnCreated()				   {};
	virtual void OnDestroyed()				   {};
	virtual void OnEnter()					   {};
	virtual void OnExit()					   {};

protected:	
	static SystemManager	s_systemManager; // Put in Game instead? Pass in to SharedContext?!

	SharedContext			m_sharedContext;
	EntityManager			m_entityManager;
};