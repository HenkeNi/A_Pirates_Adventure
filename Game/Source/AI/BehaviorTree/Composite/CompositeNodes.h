#pragma once
#include "../Base/BehaviorTreeNode.h"

// ## Composite nodes; contains instructions on how to run its children nodes. ##

/* The selector’s goal is to run just one of its children Successfully */
class SelectorNode : public BehaviorTreeNode
{
public:
	SelectorNode(int ownerID);
	~SelectorNode();

	eBTNodeStatus	Execute(EntityManager* entityManager)		override;
	void			Clear()										override;

	void			AddChild(BehaviorTreeNode* node);

private:
	std::vector<BehaviorTreeNode*> m_children;
};


/* Goal of the sequence node is to run all its children, it will stop running if any child fails */
class SequenceNode : public BehaviorTreeNode
{
public:
	SequenceNode(int ownerID);
	~SequenceNode();

	eBTNodeStatus	Execute(EntityManager* entityManager)		override;
	void			Clear()										override;

	void			AddChild(BehaviorTreeNode* node);

private:
	std::vector<BehaviorTreeNode*> m_children;
};