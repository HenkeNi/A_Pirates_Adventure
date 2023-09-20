#include "Pch.h"
#include "CompositeNodes.h"


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
		eBTNodeStatus status = child->Execute(anEntityManager);

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


// ---------------------------------------------------------------------------------------------------- //


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
