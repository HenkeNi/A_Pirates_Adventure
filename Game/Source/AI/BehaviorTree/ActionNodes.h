#pragma once
#include "BehaviorTreeNode.h"

#include <functional>  // remove later...
// Maybe add an ActionNode base class??



// Action nodes are divided into checks and tasks?!


// Renmame Tasks or Actions?

// Todo, put in Engine??

class EntityManager;

class MoveToTarget : public BehaviorTreeNode
{
public:
	MoveToTarget(int anOwnerID, int aTargetID = -1);

	eBTNodeStatus	Execute(EntityManager* anEntityManager)		override;
	void			Clear()										override;

	void			SetCallback(const std::function<void()>& aCallback);
	void			SetTargetID(int aTargetID);

private:
	bool			IsValidTarget() const;

	// callback? or use derived classes??
	std::function<void()>	m_callback;
	int						m_targetID;
	float					m_arriveRange;
};



class AttackTarget : public BehaviorTreeNode
{
public:
	AttackTarget(int anOwnerID, int aTargetID = -1);

	eBTNodeStatus	Execute(EntityManager* anEntityManager)	override;
	void			Clear()									override;

	void			SetTargetID(int aTargetID);
private:
	int				m_targetID;
};



class Idle : public BehaviorTreeNode
{
public:
	Idle(int anOwnerID);

	eBTNodeStatus	Execute(EntityManager* anEntityManager)	override;
	void			Clear()									override;
};