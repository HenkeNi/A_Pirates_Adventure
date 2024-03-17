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

void HUDSystem::Receive(Message& message)
{
	if (message.GetMessageType() == eMessage::GameStarted)
	{
		SetupHUDElements();
	}


	// Get player's health?

	// player hit event?


	// listen for entity attacked...

	// update size of Healthbar...


		// TODO DO IN SOME OTHER SYSTME?
	// TODO: Send event instead!!!
	auto* player = m_entityManager->FindFirst<PlayerControllerComponent>();
	auto* cursor = m_entityManager->FindFirst<CursorComponent>();

	// press 1 to test...
	auto* characterStateComponent = player->GetComponent<CharacterStateComponent>();
	if (characterStateComponent->IsAiming)
	{
		cursor->GetComponent<SpriteComponent>()->Subtexture = &Hi_Engine::ResourceHolder<Hi_Engine::Subtexture2D, Hi_Engine::SubtextureData>::GetInstance().GetResource({ "crosshair", 0, 0 });
	}
	else
		cursor->GetComponent<SpriteComponent>()->Subtexture = &Hi_Engine::ResourceHolder<Hi_Engine::Subtexture2D, Hi_Engine::SubtextureData>::GetInstance().GetResource({ "mouse_icon", 0, 0 });

}

void HUDSystem::Update(float deltaTime)
{
}

void HUDSystem::SetupHUDElements()
{
	if (!m_entityManager)
		return;

	auto* player = m_entityManager->FindFirst<PlayerControllerComponent>();
	auto* healthComponent = player->GetComponent<HealthComponent>(); // OR stats component (check health)

	// TODO; Get entities with Hudcomponent (that are hearts), set if should be rendered based on players health...

	float heartScale = 0.5f; // FIX!
	float windSize = 800.f;

	for (int i = 0; i < 5; ++i)
	{
		auto* heart = m_entityManager->Create("HeartContainer");

		auto* transform = heart->GetComponent<TransformComponent>();
		transform->CurrentPos = { -4.f + heartScale * i, 2.f }; // TODO; FIX! probably generates them backwards...
		//transform->CurrentPos = { -2.f + -1.f * heartScale * i, 2.f }; // TODO; FIX! probably generates them backwards...
	}
}

