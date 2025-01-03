#pragma once
#include "../Base/BehaviorTreeNode.h"


class IdleNode : public BehaviorTreeNode
{
public:
	//eBTNodeStatus	Execute(Entity entity, ECS& ecs)	override;
	eBTNodeStatus	Execute()	override;

private:
	void			StopMovement();

	float			Duration = 0;
};

// alerted node
class AlertNode : public BehaviorTreeNode
{
public:
	eBTNodeStatus	Execute()	override;
	void			OnDestroy()						override;
};


class MoveToDestinationNode : public BehaviorTreeNode
{
public:
	eBTNodeStatus	Execute()	override;
};

class ChaseTargetNode : public BehaviorTreeNode
{
public:
	eBTNodeStatus	Execute()	override;
};

class MoveToNode : public BehaviorTreeNode
{
public:
	eBTNodeStatus	Execute()	override;


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
	eBTNodeStatus	Execute(Entity entity, ECS& ecs)	override;

	//void			SetTargetID(int targetID);
private:
	//int				m_targetID;
};



