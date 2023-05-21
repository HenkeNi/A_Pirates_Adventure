#pragma once
#include "../Data/Structs.h"

class GameObject;

class Component
{
public:
	Component(GameObject* anOwner);
	virtual ~Component() = default;

	virtual void		Init(rapidjson::Value& aValue)			= 0;
	virtual void		HandleMessage(const CompMessage& aMsg)	= 0;
	virtual void		Update(float aDeltaTime)				= 0;
	virtual void		LateUpdate(float aDeltaTime)			 {};
	virtual void		Draw()							   const {};

	virtual void		OnActivate()							 {};	 
	virtual void		OnDeactivate()							 {};	

	virtual Component*	Copy()							  const = 0;	
	void				SetOwner(GameObject* anOwner);

protected:
	GameObject*			m_owner;										// TODO; replace with GameObject ID, or a Weak_ptr?
};