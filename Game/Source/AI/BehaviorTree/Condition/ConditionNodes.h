#pragma once
#include "../Base/BehaviorTreeNode.h"

// Have nodes derive from ConditionNode??

class TargetInViewNode : public BehaviorTreeNode
{
public:
	TargetInViewNode(int anOwnerID, int aTargetID = -1);

	eBTNodeStatus	Execute(EntityManager* anEntityManager)	override;
	void			Clear()									override;


private:
	int				m_targetID;
	float			m_radius;
};



class GameObject;

class TargetInRangeNode : public BehaviorTreeNode
{
public:
	TargetInRangeNode(int anOwnerID, int aTargetID = -1);

	eBTNodeStatus	Execute(EntityManager* anEntityManager)	override;
	void			Clear()									override;


private:
	int				m_targetID;
	float			m_radius;
};