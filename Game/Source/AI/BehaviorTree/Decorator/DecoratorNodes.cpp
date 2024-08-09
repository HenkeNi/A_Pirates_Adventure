#include "Pch.h"
#include "DecoratorNodes.h"


InverterNode::InverterNode(BehaviorTreeNode* child)
    : m_child{ child }
{
}

eBTNodeStatus InverterNode::Execute(Entity entity, ECS& ecs)
{
    if (entity && m_child)
    {
        auto childState = m_child->Execute(entity, ecs);

        if (childState == eBTNodeStatus::Success)
            return eBTNodeStatus::Failure;
        else if (childState == eBTNodeStatus::Failure)
            return eBTNodeStatus::Success;

        return childState;
    }

    return eBTNodeStatus::Invalid;
}

void InverterNode::OnDestroy()
{
    delete m_child;
}




SucceederNode::SucceederNode(BehaviorTreeNode* child)
    : m_child{ child }
{
}

eBTNodeStatus SucceederNode::Execute(Entity entity, ECS& ecs)
{
    if (entity && m_child)
    {
        m_child->Execute(entity, ecs);
    }

    return eBTNodeStatus::Success;
}

void SucceederNode::OnDestroy()
{
    delete m_child;
}