#pragma once
#include "BehaviorTreeNode.h"

/* It executes every child until one of them succeeds, otherwise it fails */
class SelectorNode : public BehaviorTreeNode
{
public:
	SelectorNode();
	~SelectorNode();

	eBTNodeStatus	Execute(GameObject* anOwner)			override;
	void			Clear()									override;

	void			AddChild(BehaviorTreeNode* aNode);

private:
	std::vector<BehaviorTreeNode*> m_children;
};