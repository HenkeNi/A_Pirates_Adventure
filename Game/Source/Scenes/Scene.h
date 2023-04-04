#pragma once
#include "../GameObject/GameObject.h"
#include "../Proxy/SceneManagerProxy.h"


class SceneManager;
class SceneParser;

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

protected:
	friend class			SceneManager;
	friend class			SceneParser;
	
	SceneManagerProxy		m_sceneManager;
	std::vector<GameObject> m_sceneObjects; // Layers?? 
};