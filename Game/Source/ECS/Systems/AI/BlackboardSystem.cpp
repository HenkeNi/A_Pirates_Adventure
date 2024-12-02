#include "Pch.h"
#include "BlackboardSystem.h"
#include "Components/AI/AIComponents.h"
#include "Components/Core/CoreComponents.h"
#include "Components/Gameplay/GameplayComponents.h"
#include "ECS.h"

BlackboardSystem::BlackboardSystem()
{
}

BlackboardSystem::~BlackboardSystem()
{
}

void BlackboardSystem::Update(float deltaTime)
{
	assert(m_ecs && "[BlackboardSystem - ERROR]: ECS is not initialized!");
	
	SetPlayerPosition();
	
	BlackboardComponent::Friendly = m_ecs->FindEntities(m_signatures["Friendly"]);
	BlackboardComponent::Hostile = m_ecs->FindEntities(m_signatures["Hostile"]);
}

void BlackboardSystem::SetSignature()
{
	m_signatures.insert({ "Player", m_ecs->GetSignature<PlayerControllerComponent>() });
	//m_signatures.insert({ "Friendly", m_ecs->GetSignature<FriendlyComponent>() });
	//m_signatures.insert({ "Hostile", m_ecs->GetSignature<HostileComponent>() });
}

void BlackboardSystem::SetPlayerPosition()
{
	auto player = m_ecs->FindEntity(m_signatures["Player"]);

	if (player.has_value())
	{
		auto* transformComponent = m_ecs->GetComponent<TransformComponent>(player.value());
		BlackboardComponent::PlayerPosition = transformComponent->CurrentPos;
	}
}