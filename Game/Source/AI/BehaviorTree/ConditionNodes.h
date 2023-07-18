#pragma once
#include "BehaviorTreeNode.h"

// Have nodes derive from ConditionNode??

class TargetInView : public BehaviorTreeNode
{
public:
	TargetInView(int anOwnerID, int aTargetID = -1);

	eBTNodeStatus	Execute(EntityManager* anEntityManager)	override;
	void			Clear()									override;


private:
	int				m_targetID;
	float			m_radius;
};



class GameObject;

class TargetInRange : public BehaviorTreeNode
{
public:
	TargetInRange(int anOwnerID, int aTargetID = -1);

	eBTNodeStatus	Execute(EntityManager* anEntityManager)	override;
	void			Clear()									override;


private:
	int				m_targetID;
	float			m_radius;
};