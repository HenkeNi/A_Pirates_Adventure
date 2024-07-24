#pragma once
#include "../Base/BehaviorTreeNode.h"


class SetWanderPosition : public BehaviorTreeNode
{
public:
	eBTNodeStatus	Execute(Entity entity)	override;
};



class SetTargetNode : public BehaviorTreeNode
{
public:
	eBTNodeStatus	Execute(Entity entity)	override;
};

