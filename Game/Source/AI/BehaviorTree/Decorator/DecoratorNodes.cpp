#include "Pch.h"
#include "DecoratorNodes.h"


InverterNode::InverterNode(BehaviorTreeNode* child)
    : m_child{ child }
{
}

eBTNodeStatus InverterNode::Execute(Entity* entity)
{
    if (entity && m_child)
    {
        auto childState = m_child->Execute(entity);

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