#include "Pch.h"
#include "HUDSystem.h"
#include "Entities/EntityManager.h"
#include "Components/Gameplay/GameplayComponents.h"
#include "Components/AI/AIComponents.h"
#include "Components/Core/CoreComponents.h"


HUDSystem::HUDSystem()
{
	PostMaster::GetInstance().Subscribe(eMessage::GameStarted, this);
}

HUDSystem::~HUDSystem()
{
	PostMaster::GetInstance().Unsubscribe(eMessage::GameStarted, this);
}

void HUDSystem::Receive(Message& aMsg)
{
	if (aMsg.GetMessageType() == eMessage::GameStarted)
	{
		SetupHUDElements();
	}


	// Get player's health?


	// listen for entity attacked...

	// update size of Healthbar...
}

void HUDSystem::Update(float aDeltaTime)
{

}

void HUDSystem::SetupHUDElements()
{
	if (!m_entityManager)
		return;

	auto* player = m_entityManager->FindFirst<PlayerControllerComponent>();
	
	auto healthComponent = player->GetComponent<HealthComponent>();
	for (int i = 0; i < 5; ++i)
	{
		auto heart = m_entityManager->Create("HeartContainer");

		auto transformComponent = heart->GetComponent<TransformComponent>();
		transformComponent->CurrentPos = { 0.1f * i, 0.2f, 0.f };
	}




	int xx = 10;
	xx += 10;

}