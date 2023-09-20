#pragma once
#include "../Base/BehaviorTreeNode.h"

// ## Composite nodes; contains instructions on how to run its children nodes. ##

/* The selector’s goal is to run just one of its children Successfully */
class SelectorNode : public BehaviorTreeNode
{
public:
	SelectorNode(int anOwnerID);
	~SelectorNode();

	eBTNodeStatus	Execute(EntityManager* anEntityManager)		override;
	void			Clear()										override;

	void			AddChild(BehaviorTreeNode* aNode);

private:
	std::vector<BehaviorTreeNode*> m_children;
};


/* Goal of the sequence node is to run all its children, it will stop running if any child fails */
class SequenceNode : public BehaviorTreeNode
{
public:
	SequenceNode(int anOwnerID);
	~SequenceNode();

	eBTNodeStatus	Execute(EntityManager* anEntityManager)		override;
	void			Clear()										override;

	void			AddChild(BehaviorTreeNode* aNode);

private:
	std::vector<BehaviorTreeNode*> m_children;
};