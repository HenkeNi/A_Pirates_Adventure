#pragma once
#include "../Base/BehaviorTreeNode.h"


class IdleNode : public BehaviorTreeNode
{
public:
	eBTNodeStatus	Execute(Entity entity)	override;

private:
	void			StopMovement(Entity entity);

	float			Duration = 0;
};

// alerted node
class AlertNode : public BehaviorTreeNode
{
public:
	eBTNodeStatus	Execute(Entity entity)	override;
	void			OnDestroy()						override;
};


class MoveToDestinationNode : public BehaviorTreeNode
{
public:
	eBTNodeStatus	Execute(Entity entity)	override;
};

class ChaseTargetNode : public BehaviorTreeNode
{
public:
	eBTNodeStatus	Execute(Entity entity)	override;
};

class MoveToNode : public BehaviorTreeNode
{
public:
	eBTNodeStatus	Execute(Entity entity)	override;


	//void			SetCallback(const std::function<void()>& callback);
	//void			SetTargetID(int targetID);

private:
	//bool			IsValidTarget() const;

	// callback? or use derived classes??
	//std::function<void()>	m_callback;
	//int						m_targetID;
	float					m_arriveRange;
};



class AttackTargetNode : public BehaviorTreeNode
{
public:
	eBTNodeStatus	Execute(Entity entity)	override;

	//void			SetTargetID(int targetID);
private:
	//int				m_targetID;
};



