#pragma once
#include "../Data/Structs.h"

class GameObject;

class Component
{
public:
	Component(GameObject* anOwner);
	virtual ~Component() = default;

	virtual void		Init(rapidjson::Value& aValue)			= 0;
	virtual void		HandleMessage(CompMessage aMessage)		= 0;
	virtual void		Update(float aDeltaTime)				= 0;
	virtual void		LateUpdate(float aDeltaTime)			 {};	// REMOVE??
	virtual void		Draw()							   const {};	// Maybe remove => instead add draw calls?? (in late update??)

	virtual void		OnActivate()						     {};	 
	virtual void		OnDeactivate()							 {};	

	virtual Component*	Copy()							  const = 0;	
	void				SetOwner(GameObject* anOwner);

protected:
	GameObject*			m_owner;										// [Consider] replacing with GameObjectID... or a Weak_ptr?
};