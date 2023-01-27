#pragma once
#include "../GameObject/GameObject.h"
#include "../Proxy/SceneManagerProxy.h"


class SceneManager;

class Scene
{
public:
	Scene(SceneManagerProxy aProxy);
	virtual ~Scene() = default;

	// process input?? or do it all through events??
	virtual void			Update(float aDeltaTime)		  = 0;
	virtual void			LateUpdate(float aDeltaTime)	  = 0;
	virtual void			Draw()						const = 0;
	virtual bool			IsTransparent()				const;

	virtual void			OnCreated()					   {};
	virtual void			OnDestroyed()				   {};
	virtual void			OnEnter()					   {};
	virtual void			OnExit()					   {};

private:
	friend class			SceneManager;
	
	SceneManagerProxy		m_sceneManager;
	std::vector<GameObject> m_sceneObjects; // Layers??
};