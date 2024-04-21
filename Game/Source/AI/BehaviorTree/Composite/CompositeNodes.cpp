#include "Pch.h"
#include "CompositeNodes.h"


#pragma region SelectorNode

eBTNodeStatus SelectorNode::Execute(Entity* entity)
{
	for (auto* child : m_children)
	{
		eBTNodeStatus status = child->Execute(entity);

		if (status == eBTNodeStatus::Running || status == eBTNodeStatus::Success)
			return status;
	}

	return eBTNodeStatus::Failure;
}

void SelectorNode::OnDestroy()
{
	for (auto* child : m_children)
	{
		if (child)
			child->OnDestroy();
	}
}

void SelectorNode::AddChild(BehaviorTreeNode* node)
{
	assert(node && "ERROR; trying to add a nullptr");
	m_children.push_back(node);
}

#pragma endregion SelectorNode

#pragma region SequenceNode

eBTNodeStatus SequenceNode::Execute(Entity* entity)
{
	for (auto* child : m_children)
	{
		auto status = child->Execute(entity);

		if (status == eBTNodeStatus::Running || status == eBTNodeStatus::Failure)
			return status;
	}

	return eBTNodeStatus::Success;
}

void SequenceNode::OnDestroy()
{
	for (auto* child : m_children)
	{
		if (child)
			child->OnDestroy();
	}
}

void SequenceNode::AddChild(BehaviorTreeNode* node)
{
	assert(node && "ERROR; trying to add a nullptr");
	m_children.push_back(node);
}

#pragma endregion SequenceNode