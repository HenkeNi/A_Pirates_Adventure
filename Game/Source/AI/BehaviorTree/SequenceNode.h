#pragma once
#include "BehaviorTreeNode.h"


// Sequence : public Composite?

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