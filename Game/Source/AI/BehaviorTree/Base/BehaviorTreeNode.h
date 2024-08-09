#pragma once

enum class eBTNodeStatus;
class ECS;

// Todo; rename BTNode?
class BehaviorTreeNode
{
public:
	virtual ~BehaviorTreeNode() = default;

	virtual eBTNodeStatus	Execute(Entity entity, ECS& ecs) = 0;
	virtual void			OnDestroy()						  {};
};