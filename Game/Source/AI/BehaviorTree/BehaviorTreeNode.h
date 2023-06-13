#pragma once
#include "../../Data/Enumerations.h"


// class BTNode? 

class GameObject; // Find better way, maybe blackboard?!

class BehaviorTreeNode
{
public:
	BehaviorTreeNode();
	virtual ~BehaviorTreeNode() = default;

	virtual eBTNodeStatus	Execute(GameObject* anOwner)	  = 0;
	virtual void			Clear()							  = 0;
	//eBTNodeStatus			GetStatus()						const;

protected:
	//eBTNodeStatus			m_status;	// change name to state?? an NodeState??
};