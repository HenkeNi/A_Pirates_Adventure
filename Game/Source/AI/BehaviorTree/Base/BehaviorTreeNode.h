#pragma once

enum class eBTNodeStatus;

// Todo; rename BTNode?
class BehaviorTreeNode
{
public:
	virtual ~BehaviorTreeNode() = default;

	virtual eBTNodeStatus	Execute(Entity entity)	= 0;
	virtual void			OnDestroy()						 {};
};