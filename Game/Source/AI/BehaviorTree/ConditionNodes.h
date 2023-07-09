#pragma once
#include "BehaviorTreeNode.h"

// Have nodes derive from ConditionNode??

class TargetInView : public BehaviorTreeNode
{
public:
	TargetInView(const Entity* aTarget = nullptr);

	eBTNodeStatus	Execute(Entity* anEntity) override;
	void			Clear()						 override;


private:
	const Entity* m_target;
	float			  m_radius;
};



class GameObject;

class TargetInRange : public BehaviorTreeNode
{
public:
	TargetInRange(const Entity* aTarget = nullptr);

	eBTNodeStatus	Execute(Entity* anEntity) override;
	void			Clear()						 override;


private:
	const Entity*	m_target;
	float				m_radius;
};