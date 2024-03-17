#include "Pch.h"
#include "BehaviorTreeNode.h"
#include "../../../DataTypes/Enumerations.h"


BehaviorTreeNode::BehaviorTreeNode(int ownerID)
	: m_ownerID{ ownerID } //	: m_status{ eBTNodeStatus::Invalid }
{
}

//eBTNodeStatus BehaviorTreeNode::GetStatus() const
//{
//	return m_status;
//}