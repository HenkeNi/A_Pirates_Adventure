#pragma once
#include "../ComponentBase.h"


struct BehaviorTreeComponent : public ComponentBase
{
	class BehaviorTreeNode* m_rootNode;				// Call Execute in Update
	// current node?
};

struct SteeringBehaviorComponent : public ComponentBase
{
	class SteeringBehavior* m_activeBehavior = nullptr;
};

