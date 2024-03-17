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
	if (!m_entityManager)
		return;

	auto* entity = m_entityManager->FindFirst<BlackboardComponent>();
	auto* player = m_entityManager->FindFirst<PlayerControllerComponent>();

	if (entity && player)
	{
		auto* blackboard = entity->GetComponent<BlackboardComponent>();
		auto* transform = player->GetComponent<TransformComponent>();
	
		blackboard->PlayerPosition = transform->CurrentPos;
	}
}
