#pragma once
#include "../Base/BehaviorTreeNode.h"

#include <functional>  // remove later...
// Maybe add an ActionNode base class??



// Action nodes are divided into checks and tasks?!


// Renmame Tasks or Actions?

// Todo, put in Engine??

class EntityManager;




class IdleNode : public BehaviorTreeNode
{
public:
	IdleNode(int ownerID);

	eBTNodeStatus	Execute(EntityManager* entityManager)	override;
	void			Clear()									override;
};






//class Wander : public BehaviorTreeNode
//{
//public:
//
//private:
//
//};












class MoveToTargetNode : public BehaviorTreeNode
{
public:
	MoveToTargetNode(int ownerID, int targetID = -1);

	eBTNodeStatus	Execute(EntityManager* entityManager)		override;
	void			Clear()										override;

	void			SetCallback(const std::function<void()>& callback);
	void			SetTargetID(int targetID);

private:
	bool			IsValidTarget() const;

	// callback? or use derived classes??
	std::function<void()>	m_callback;
	int						m_targetID;
	float					m_arriveRange;
};



class AttackTargetNode : public BehaviorTreeNode
{
public:
	AttackTargetNode(int ownerID, int targetID = -1);

	eBTNodeStatus	Execute(EntityManager* entityManager)	override;
	void			Clear()									override;

	void			SetTargetID(int targetID);
private:
	int				m_targetID;
};



