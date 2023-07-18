#include "Pch.h"
#include "BehaviorTreeSystem.h"
#include "EntityManager.h"
#include "AI/AIComponents.h"
#include "../AI/BehaviorTree/BehaviorTreeNode.h"


BehaviorTreeSystem::BehaviorTreeSystem()
{

}

BehaviorTreeSystem::~BehaviorTreeSystem()
{
	auto entities = m_entityManager->FindAllWithComponents<BehaviorTreeComponent>();
	
	for (auto& entity : entities)
	{
		auto behaviorComponet = entity->GetComponent<BehaviorTreeComponent>();
		behaviorComponet->m_rootNode->Clear();

		delete behaviorComponet->m_rootNode;
		behaviorComponet->m_rootNode = nullptr;
	}
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
		auto* behaviorComponent = entity->GetComponent<BehaviorTreeComponent>();
		
		behaviorComponent->m_rootNode->Execute(m_entityManager);
	}

}
