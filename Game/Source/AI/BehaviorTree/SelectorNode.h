#pragma once
#include "BehaviorTreeNode.h"

class EntityManager;

/* It executes every child until one of them succeeds, otherwise it fails */
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