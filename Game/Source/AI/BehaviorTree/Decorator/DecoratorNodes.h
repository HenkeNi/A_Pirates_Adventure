#pragma once
#include "../Base/BehaviorTreeNode.h"

class InverterNode : public BehaviorTreeNode
{
public:
	InverterNode(BehaviorTreeNode* child = nullptr);

	eBTNodeStatus	Execute(class Entity* entity)	override;
	void			OnDestroy()						override;

private:
	BehaviorTreeNode* m_child;
};