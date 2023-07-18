#include "Pch.h"
#include "SequenceNode.h"


SequenceNode::SequenceNode(int anOwnerID)
	: BehaviorTreeNode{ anOwnerID }
{
}

SequenceNode::~SequenceNode()
{
}

eBTNodeStatus SequenceNode::Execute(EntityManager* anEntityManager)
{
	for (auto* child : m_children)
	{
		auto status = child->Execute(anEntityManager);

		if (status == eBTNodeStatus::Running || status == eBTNodeStatus::Failure)
			return status;
	}

	return eBTNodeStatus::Success;
}

void SequenceNode::Clear()
{
}

void SequenceNode::AddChild(BehaviorTreeNode* aNode)
{
	assert(aNode && "ERROR; trying to add a nullptr");
	m_children.push_back(aNode);
}
