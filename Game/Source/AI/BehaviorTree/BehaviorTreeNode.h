#pragma once
#include "../../Data/Enumerations.h"

// class BTNode? 
//class GameObject; // Find better way, maybe blackboard?!

class Entity;

class BehaviorTreeNode
{
public:
	BehaviorTreeNode();
	virtual ~BehaviorTreeNode() = default;

	virtual eBTNodeStatus	Execute(Entity* anEntity)	  = 0;			// Init function instead that passes in the Entity?
	virtual void			Clear()						  = 0;
	//eBTNodeStatus			GetStatus()						const;

protected:
	//eBTNodeStatus			m_status;	// change name to state?? an NodeState??
};