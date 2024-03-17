#include "Pch.h"
#include "CompositeNodes.h"


SelectorNode::SelectorNode(int ownerID)
	: BehaviorTreeNode{ ownerID }
{
}

SelectorNode::~SelectorNode()
{
}

eBTNodeStatus SelectorNode::Execute(EntityManager* entityManager)
{
	for (auto* child : m_children)
	{
		eBTNodeStatus status = child->Execute(entityManager);

		if (status == eBTNodeStatus::Running || status == eBTNodeStatus::Success)
			return status;
	}

	return eBTNodeStatus::Failure;
}

void SelectorNode::Clear()
{
}

void SelectorNode::AddChild(BehaviorTreeNode* node)
{
	assert(node && "ERROR; trying to add a nullptr");
	m_children.push_back(node);
}


// ---------------------------------------------------------------------------------------------------- //


SequenceNode::SequenceNode(int ownerID)
	: BehaviorTreeNode{ ownerID }
{
}

SequenceNode::~SequenceNode()
{
}

eBTNodeStatus SequenceNode::Execute(EntityManager* entityManager)
{
	for (auto* child : m_children)
	{
		auto status = child->Execute(entityManager);

		if (status == eBTNodeStatus::Running || status == eBTNodeStatus::Failure)
			return status;
	}

	return eBTNodeStatus::Success;
}

void SequenceNode::Clear()
{
}

void SequenceNode::AddChild(BehaviorTreeNode* node)
{
	assert(node && "ERROR; trying to add a nullptr");
	m_children.push_back(node);
}
