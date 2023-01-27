#pragma once
#include "../Data/Enumerations.h"

class GameObject;

class Component
{
public:
	Component(GameObject* anOwner);
	virtual ~Component() = default;

	virtual void	HandleMessage(eCompMessage aMessageType, const std::any& someData) = 0;
	virtual void	Update(float aDeltaTime) = 0;
	virtual void	LateUpdate(float aDeltaTime) {};
	virtual void	Draw()													   const {};
	virtual void	OnActivate() {};
	virtual void	OnDeactivate() {};

	bool			IsActive()												   const;
	void			SetIsActive(bool shouldActivate);
	void			SetOwner(GameObject* anOwner);

protected:
	GameObject* m_owner; // [Consider] replacing with GameObjectID... or a Weak_ptr?
	bool			m_isActive;
};

