#pragma once


 //class GameObject; // Find better way, maybe blackboard?!

class Entity;
class EntityManager;

enum class eBTNodeStatus;

// Todo; rename BTNode?
class BehaviorTreeNode
{
public:
	BehaviorTreeNode(int ownerID);
	virtual ~BehaviorTreeNode() = default;

	virtual eBTNodeStatus	Execute(EntityManager* entityManager)	= 0;
	virtual void			Clear()									= 0;
	//eBTNodeStatus			GetStatus()						const;

protected:
	const int				m_ownerID;
	//eBTNodeStatus			m_status;	// change name to state?? an NodeState??
};