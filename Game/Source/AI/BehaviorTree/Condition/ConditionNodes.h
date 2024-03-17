#pragma once
#include "../Base/BehaviorTreeNode.h"

// Have nodes derive from ConditionNode??

class TargetInViewNode : public BehaviorTreeNode
{
public:
	TargetInViewNode(int ownerID, int targetID = -1);

	eBTNodeStatus	Execute(EntityManager* entityManager)	override;
	void			Clear()									override;


private:
	int				m_targetID;
	float			m_radius;
};



class GameObject;

class TargetInRangeNode : public BehaviorTreeNode
{
public:
	TargetInRangeNode(int ownerID, int targetID = -1);

	eBTNodeStatus	Execute(EntityManager* entityManager)	override;
	void			Clear()									override;


private:
	int				m_targetID;
	float			m_radius;
};