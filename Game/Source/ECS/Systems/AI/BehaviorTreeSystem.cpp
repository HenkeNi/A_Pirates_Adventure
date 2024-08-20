#include "Pch.h"
#include "BehaviorTreeSystem.h"
#include "ECS.h"
#include "Components/AI/AIComponents.h"
#include "AI/BehaviorTree/Base/BehaviorTreeNode.h"


BehaviorTreeSystem::BehaviorTreeSystem()
{
}

BehaviorTreeSystem::~BehaviorTreeSystem()
{
	ClearBehaviorTreeNodes();
}

void BehaviorTreeSystem::Update(float deltaTime)
{
	// assert(m_entityManager && "ERROR: EntityManager is nullptr!");

	auto entities = m_ecs->FindEntities(m_signatures["BehaviorTree"]);

	for (auto entity : entities)
	{
		auto* behaviorComponent = m_ecs->GetComponent<BehaviorTreeComponent>(entity);
			
		if (auto* rootNode = behaviorComponent->RootNode)
			rootNode->Execute(entity, *m_ecs);
	}
}

void BehaviorTreeSystem::SetSignature()
{
	m_signatures.insert({ "BehaviorTree", m_ecs->GetSignature<BehaviorTreeComponent>() });
}

void BehaviorTreeSystem::ClearBehaviorTreeNodes()
{
	auto& behaviorTreeComponents = m_ecs->GetComponents<BehaviorTreeComponent>();

	for (auto& component : behaviorTreeComponents)
	{
		if (auto* rootNode = component.RootNode)
		{
			rootNode->OnDestroy();
		
			delete component.RootNode;
			component.RootNode = nullptr;
		}
	}
}
