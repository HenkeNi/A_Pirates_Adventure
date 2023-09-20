#include "Pch.h"
#include "BehaviorTreeNode.h"


BehaviorTreeNode::BehaviorTreeNode(int anOwnerID)
	: m_ownerID{ anOwnerID } //	: m_status{ eBTNodeStatus::Invalid }
{
}

//eBTNodeStatus BehaviorTreeNode::GetStatus() const
//{
//	return m_status;
//}