#pragma once
#include "../Base/BehaviorTreeNode.h"


class InverterNode : public BehaviorTreeNode
{
public:
	InverterNode(BehaviorTreeNode* child = nullptr);

	eBTNodeStatus	Execute(Entity entity)	override;
	void			OnDestroy()						override;

private:
	BehaviorTreeNode* m_child;
};


class SucceederNode : public BehaviorTreeNode
{
public:
	SucceederNode(BehaviorTreeNode* child = nullptr);

	eBTNodeStatus	Execute(Entity entity)	override;
	void			OnDestroy()						override;

private:
	BehaviorTreeNode* m_child;
};