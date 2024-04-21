#pragma once
#include "../Base/BehaviorTreeNode.h"

// Have nodes derive from ConditionNode??




class InRangeNode : public BehaviorTreeNode
{
public:

private:
};



class TargetInViewNode : public BehaviorTreeNode
{
public:
	eBTNodeStatus	Execute(class Entity* entity)	override;
	void			OnDestroy()						override;

private:
	//int				m_targetID;
	float			m_radius;
};



class GameObject;

class TargetInRangeNode : public BehaviorTreeNode
{
public:
	eBTNodeStatus	Execute(class Entity* entity)	override;
	void			OnDestroy()						override;

private:
	//int				m_targetID;
	float			m_radius;
};