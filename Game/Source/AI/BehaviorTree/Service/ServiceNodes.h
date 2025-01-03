#pragma once
#include "../Base/BehaviorTreeNode.h"


class SetWanderPosition : public BehaviorTreeNode
{
public:
	eBTNodeStatus	Execute()	override;
	//eBTNodeStatus	Execute(Entity entity, ECS& ecs)	override;
};



class SetTargetNode : public BehaviorTreeNode
{
public:
	eBTNodeStatus	Execute()	override;
	//eBTNodeStatus	Execute(Entity entity, ECS& ecs)	override;
};

