#include "Pch.h"
#include "BehaviorTreeSystem.h"
#include "Entities/EntityManager.h"
#include "Components/AI/AIComponents.h"
#include "../AI/BehaviorTree/Base/BehaviorTreeNode.h"


BehaviorTreeSystem::BehaviorTreeSystem()
{
}

BehaviorTreeSystem::~BehaviorTreeSystem()
{
	ClearBehaviorTreeNodes();
}

void BehaviorTreeSystem::Receive(Message& message)
{
}

void BehaviorTreeSystem::Update(float deltaTime)
{
	if (!m_entityManager)
		return;

	auto entities = m_entityManager->FindAll<BehaviorTreeComponent>();

	for (auto& entity : entities)
	{
		if (auto* behaviorComponent = entity->GetComponent<BehaviorTreeComponent>())
		{
			if (auto rootNode = behaviorComponent->RootNode)
				rootNode->Execute(m_entityManager);
		}
	}
}

void BehaviorTreeSystem::ClearBehaviorTreeNodes()
{
	auto entities = m_entityManager->FindAll<BehaviorTreeComponent>();

	for (auto& entity : entities)
	{
		if (auto* behaviorComponet = entity->GetComponent<BehaviorTreeComponent>())
		{
			behaviorComponet->RootNode->Clear();
		
			delete behaviorComponet->RootNode;
			behaviorComponet->RootNode = nullptr;
		}
	}
}
