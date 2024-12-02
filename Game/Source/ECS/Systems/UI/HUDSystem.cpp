#include "Pch.h"
#include "HUDSystem.h"
#include "Components/Core/CoreComponents.h"
#include "Components/Gameplay/GameplayComponents.h"
#include "Components/AI/AIComponents.h"
#include "Components/UI/UIComponents.h"
#include "ECS.h"


HUDSystem::HUDSystem()
{
	PostMaster::GetInstance().Subscribe(eMessage::GameStarted, this);
	PostMaster::GetInstance().Subscribe(eMessage::ItemCollected, this);
	PostMaster::GetInstance().Subscribe(eMessage::EntityEnteredAim, this);
	PostMaster::GetInstance().Subscribe(eMessage::EntityExitedAim, this);
}

HUDSystem::~HUDSystem()
{
	PostMaster::GetInstance().Unsubscribe(eMessage::GameStarted, this);
	PostMaster::GetInstance().Unsubscribe(eMessage::ItemCollected, this);
	PostMaster::GetInstance().Unsubscribe(eMessage::EntityEnteredAim, this);
	PostMaster::GetInstance().Unsubscribe(eMessage::EntityExitedAim, this);

}

void HUDSystem::Receive(Message& message)
{
	assert(m_ecs && "[HUDSysten - ERROR]: ECS is not initialized!");

	switch (message.GetMessageType())
	{
	case eMessage::GameStarted:
		SetupHUDElements();
		break;
	case eMessage::ItemCollected:
		UpdateInventoryBar();
		break;
	case eMessage::EntityAttacked:
		UpdateHealthDisplay(std::any_cast<Entity>(message.GetData()));
		break;
	case eMessage::EntityEnteredAim:
		UpdateCursorTexture(std::any_cast<Entity>(message.GetData()), true);
		break;
	case eMessage::EntityExitedAim:
		UpdateCursorTexture(std::any_cast<Entity>(message.GetData()), false);
		break;
	}
}

void HUDSystem::SetSignature()
{
	m_signatures.insert({ "Player", m_ecs->GetSignature<PlayerControllerComponent>() });
	m_signatures.insert({ "Cursor", m_ecs->GetSignature<CursorComponent>() });
}

void HUDSystem::SetupHUDElements()
{
	auto player = m_ecs->FindEntity(m_signatures["Player"]);
	if (!player.has_value())
		return;	
	
	UpdateHealthDisplay(player.value());
	UpdateInventoryBar();
}

void HUDSystem::UpdateCursorTexture(Entity entity, bool isAiming)
{
	auto player = m_ecs->FindEntity(m_signatures["Player"]);
	if (!player.has_value())
		return;

	auto cursor = m_ecs->FindEntity(m_signatures["Cursor"]);
	if (!cursor.has_value())
		return;

	std::string resource = isAiming ? "crosshair" : "mouse_icon";
	auto texture = Hi_Engine::ResourceHolder<Hi_Engine::Subtexture2D, Hi_Engine::SubtextureData>::GetInstance().GetResource({ resource, 0, 0 });
	
	auto* spriteComponent = m_ecs->GetComponent<SpriteComponent>(cursor.value());
	spriteComponent->Subtexture = texture;
}

void HUDSystem::UpdateHealthDisplay(Entity entity)
{
	// check tag instead?
	if (!m_ecs->HasComponent<PlayerControllerComponent>(entity))
		return;

	auto* healthComponent = m_ecs->GetComponent<HealthComponent>(entity);
	if (!healthComponent)
		return;

	IVector2 windowSize = Hi_Engine::ServiceLocator::GetWindow().lock()->GetSize();

	// TODO; Store hearts in a grid

	for (int i = 0; i < healthComponent->MaxHealth; ++i)
	{
		Entity heart = m_ecs->CreateEntityFromBlueprint("HeartContainer");

		auto* transformComponent = m_ecs->GetComponent<TransformComponent>(heart);

		static const float offsetSide = 50.f;
		static const float offsetTop = 50.f;

		float offset = transformComponent->Scale.x;
		transformComponent->CurrentPos.x = (offsetSide + (offset * (float)i)) / windowSize.x;

		float yPosition = windowSize.y - offsetTop;
		transformComponent->CurrentPos.y = yPosition / windowSize.y;		
	}
}

void HUDSystem::UpdateInventoryBar()
{
	//auto* inventoryBar = m_entityManager->FindFirst<GridComponent>(); // Fix!

	auto window = Hi_Engine::ServiceLocator::GetWindow();
	if (auto win = window.lock())
	{
	}
}
