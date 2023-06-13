#pragma once
#include "BehaviorTreeNode.h"


// Have nodes derive from ConditionNode??

class TargetInView : public BehaviorTreeNode
{
public:
	TargetInView(const GameObject* aTarget = nullptr);

	eBTNodeStatus	Execute(GameObject* anOwner) override;
	void			Clear()						 override;


private:
	const GameObject* m_target;
	float			  m_radius;
};



class GameObject;

class TargetInRange : public BehaviorTreeNode
{
public:
	TargetInRange(const GameObject* aTarget = nullptr);

	eBTNodeStatus	Execute(GameObject* anOwner) override;
	void			Clear()						 override;


private:
	const GameObject*	m_target;
	float				m_radius;
};