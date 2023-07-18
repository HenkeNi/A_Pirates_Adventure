#include "Pch.h"
#include "SelectorNode.h"


SelectorNode::SelectorNode(int anOwnerID)
	: BehaviorTreeNode{ anOwnerID }
{
}

SelectorNode::~SelectorNode()
{
}

eBTNodeStatus SelectorNode::Execute(EntityManager* anEntityManager)
{
	for (auto* child : m_children)
	{
		auto status = child->Execute(anEntityManager);

		if (status == eBTNodeStatus::Running || status == eBTNodeStatus::Success)
			return status;
	}

	return eBTNodeStatus::Failure;
}

void SelectorNode::Clear()
{

}

void SelectorNode::AddChild(BehaviorTreeNode* aNode)
{
	assert(aNode && "ERROR; trying to add a nullptr");
	m_children.push_back(aNode);
}