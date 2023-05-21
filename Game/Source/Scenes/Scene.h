#pragma once
#include "../Managers/ObjectManager.h"
#include "../Proxy/SceneManagerProxy.h"

class SceneManager;

class Scene
{
public:
	Scene(SceneManagerProxy aProxy);
	virtual ~Scene() = default;

	virtual void		Init(rapidjson::Value& aValue)	  = 0;	// remove init? make a builder that can generate needed data...
	virtual void		Update(float aDeltaTime)		  = 0;
	virtual void		LateUpdate(float aDeltaTime)	  = 0;
	virtual void		Draw()						const = 0;
	virtual bool		IsTransparent()				const;

	virtual void		OnCreated()					   {};
	virtual void		OnDestroyed()				   {};
	virtual void		OnEnter()					   {};
	virtual void		OnExit()					   {};

protected:
	friend class		SceneManager;
	
	SceneManagerProxy	m_sceneManager;
	ObjectManager		m_objectManager;
};