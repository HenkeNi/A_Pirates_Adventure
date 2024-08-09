#pragma once
#include "../Base/BehaviorTreeNode.h"

// Have nodes derive from ConditionNode??

// Condition nodes should only return success or failure


class IsIdleNode : public BehaviorTreeNode
{
public:
	eBTNodeStatus Execute(Entity entity, ECS& ecs)	override;
};

class IsDestinationSetNode : public BehaviorTreeNode
{
public:
	eBTNodeStatus Execute(Entity entity, ECS& ecs)	override;
};

class IsDestinationReachedNode : public BehaviorTreeNode
{
public:
	eBTNodeStatus Execute(Entity entity, ECS& ecs)	override;
};

class IsTargetSetNode : public BehaviorTreeNode
{
public:
	eBTNodeStatus Execute(Entity entity, ECS& ecs)	override;
};

class IsTargetReachedNode : public BehaviorTreeNode // assure is valid! blackboard system, or some system handles it..
{
public:
	eBTNodeStatus Execute(Entity entity, ECS& ecs)	override;
};

class IsTargetInSightNode : public BehaviorTreeNode
{
public:
	eBTNodeStatus Execute(Entity entity, ECS& ecs)	override;

};
