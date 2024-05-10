#pragma once
#include "../Base/BehaviorTreeNode.h"

// Have nodes derive from ConditionNode??

// Condition nodes should only return success or failure


class IsIdleNode : public BehaviorTreeNode
{
public:
	eBTNodeStatus Execute(class Entity* entity)	override;
};

class IsDestinationSetNode : public BehaviorTreeNode
{
public:
	eBTNodeStatus Execute(class Entity* entity)	override;
};

class IsDestinationReachedNode : public BehaviorTreeNode
{
public:
	eBTNodeStatus Execute(class Entity* entity)	override;
};

class IsTargetSetNode : public BehaviorTreeNode
{
public:
	eBTNodeStatus Execute(class Entity* entity)	override;
};

class IsTargetReachedNode : public BehaviorTreeNode // assure is valid! blackboard system, or some system handles it..
{
public:
	eBTNodeStatus Execute(class Entity* entity)	override;
};


class IsTargetInSightNode : public BehaviorTreeNode
{
public:
	eBTNodeStatus Execute(class Entity* entity)	override;

};



class HasTagetNode : public BehaviorTreeNode
{
public:
	eBTNodeStatus	Execute(class Entity* entity)	override;
};

class DistanceCheckNode : public BehaviorTreeNode
{
public:
	eBTNodeStatus	Execute(class Entity* entity)	override;

private:

};

// IsNearHostileNode, 
class CheckEnemyPresenceNode : public BehaviorTreeNode
{
public:
	eBTNodeStatus	Execute(class Entity* entity)	override;

};
