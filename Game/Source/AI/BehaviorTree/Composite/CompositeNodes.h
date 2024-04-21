#pragma once
#include "../Base/BehaviorTreeNode.h"


/* The selector’s goal is to run just one of its children Successfully */
class SelectorNode : public BehaviorTreeNode
{
public:
	eBTNodeStatus	Execute(class Entity* entity)	override;
	void			OnDestroy()						override;

	void			AddChild(BehaviorTreeNode* node);

private:
	std::vector<BehaviorTreeNode*> m_children;
};


/* Goal of the sequence node is to run all its children, it will stop running if any child fails */
class SequenceNode : public BehaviorTreeNode
{
public:
	eBTNodeStatus	Execute(class Entity* entity)	override;
	void			OnDestroy()						override;

	void			AddChild(BehaviorTreeNode* node);

private:
	std::vector<BehaviorTreeNode*> m_children;
};