#pragma once
#include "../Base/BehaviorTreeNode.h"

// Have nodes derive from ConditionNode??

// Condition nodes should only return success or failure


class HasTaget : public BehaviorTreeNode
{
public:
	eBTNodeStatus	Execute(class Entity* entity)	override;
	void			OnDestroy()						override;
};

class IsTargetReached : public BehaviorTreeNode
{
public:
	eBTNodeStatus	Execute(class Entity* entity)	override;
	void			OnDestroy()						override;
};



class DistanceCheckNode : public BehaviorTreeNode
{
public:
	eBTNodeStatus	Execute(class Entity* entity)	override;
	void			OnDestroy()						override;

private:

};




// IsNearHostileNode, 
class CheckEnemyPresenceNode : public BehaviorTreeNode
{
public:
	eBTNodeStatus	Execute(class Entity* entity)	override;
	void			OnDestroy()						override;

private:
};



//class TargetInViewNode : public BehaviorTreeNode
//{
//public:
//	eBTNodeStatus	Execute(class Entity* entity)	override;
//	void			OnDestroy()						override;
//
//private:
//	//int				m_targetID;
//	float			m_radius;
//};
//
//class TargetInRangeNode : public BehaviorTreeNode
//{
//public:
//	eBTNodeStatus	Execute(class Entity* entity)	override;
//	void			OnDestroy()						override;
//
//private:
//	//int				m_targetID;
//	float			m_radius;
//};