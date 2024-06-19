#include "Pch.h"
#include "BlackboardSystem.h"
#include "Entities/EntityManager.h"
#include "Components/AI/AIComponents.h"

BlackboardSystem::BlackboardSystem()
{
}

BlackboardSystem::~BlackboardSystem()
{
}

void BlackboardSystem::Receive(Message& message)
{
}

void BlackboardSystem::Update(float deltaTime)
{
	assert(m_entityManager && "ERROR: EntityManager is nullptr!");

	SetPlayerPosition();
	
	BlackboardComponent::Friendly = m_entityManager->FindAll<FriendlyComponent>();
	BlackboardComponent::Hostile = m_entityManager->FindAll<HostileComponent>();
}

void BlackboardSystem::SetPlayerPosition()
{
	if (auto* player = m_entityManager->FindFirst<PlayerControllerComponent>())
	{
		auto* transformComponent = player->GetComponent<TransformComponent>();
		BlackboardComponent::PlayerPosition = transformComponent->CurrentPos;
	}
}