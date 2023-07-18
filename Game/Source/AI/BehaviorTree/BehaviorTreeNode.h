#pragma once
#include "../../Data/Enumerations.h"

// class BTNode? 
//class GameObject; // Find better way, maybe blackboard?!

class Entity;
class EntityManager;

class BehaviorTreeNode
{
public:
	BehaviorTreeNode(int anOwnerID);
	virtual ~BehaviorTreeNode() = default;

	virtual eBTNodeStatus	Execute(EntityManager* anEntityManager)	= 0;
	virtual void			Clear()									= 0;
	//eBTNodeStatus			GetStatus()						const;

protected:
	const int				m_ownerID;
	//eBTNodeStatus			m_status;	// change name to state?? an NodeState??
};