#include "Pch.h"
#include "BehaviorTreeSystem.h"
#include "EntityManager.h"
#include "AI/AIComponents.h"
#include "../AI/BehaviorTree/Base/BehaviorTreeNode.h"


BehaviorTreeSystem::BehaviorTreeSystem()
{
}

BehaviorTreeSystem::~BehaviorTreeSystem()
{
	ClearBehaviorTreeNodes();
}

void BehaviorTreeSystem::Receive(Message& aMsg)
{
}

void BehaviorTreeSystem::Update(float aDeltaTime)
{
	if (!m_entityManager)
		return;

	auto entities = m_entityManager->FindAllWithComponents<BehaviorTreeComponent>();

	for (auto& entity : entities)
	{
		if (auto* behaviorComponent = entity->GetComponent<BehaviorTreeComponent>())
		{
			if (auto rootNode = behaviorComponent->m_rootNode)
				rootNode->Execute(m_entityManager);
		}
	}
}

void BehaviorTreeSystem::ClearBehaviorTreeNodes()
{
	auto entities = m_entityManager->FindAllWithComponents<BehaviorTreeComponent>();

	for (auto& entity : entities)
	{
		if (auto* behaviorComponet = entity->GetComponent<BehaviorTreeComponent>())
		{
			behaviorComponet->m_rootNode->Clear();
		
			delete behaviorComponet->m_rootNode;
			behaviorComponet->m_rootNode = nullptr;
		}
	}
}
