#include "Pch.h"
#include "HUDSystem.h"
#include "Entities/EntityManager.h"
#include "Components/Core/CoreComponents.h"
#include "Components/Gameplay/GameplayComponents.h"
#include "Components/AI/AIComponents.h"
#include "Components/UI/UIComponents.h"
#include "ECS.h"


HUDSystem::HUDSystem()
{
	PostMaster::GetInstance().Subscribe(eMessage::GameStarted, this);
	PostMaster::GetInstance().Subscribe(eMessage::EntityAttacked, this);
	PostMaster::GetInstance().Subscribe(eMessage::ItemCollected, this);
}

HUDSystem::~HUDSystem()
{
	PostMaster::GetInstance().Unsubscribe(eMessage::GameStarted, this);
	PostMaster::GetInstance().Unsubscribe(eMessage::EntityAttacked, this);
	PostMaster::GetInstance().Unsubscribe(eMessage::ItemCollected, this);
}

void HUDSystem::Receive(Message& message)
{
	if (message.GetMessageType() == eMessage::GameStarted)
	{
		SetupHUDElements();
	}

	if (message.GetMessageType() == eMessage::EntityAttacked)
	{
		auto entity = std::any_cast<Entity>(message.GetData());
		if (m_ecs->GetComponent<PlayerControllerComponent>(entity))
		{
			UpdateHealthDisplay(entity);

		}
	}

	if (message.GetMessageType() == eMessage::ItemCollected)
	{
		// auto* inventory = m_entityManager->FindFirst<InventoryComponent>();

	}

	// Get player's health?

	// player hit event?

	// listen for entity attacked...

	// update size of Healthbar...

	// TODO DO IN SOME OTHER SYSTME?
	// TODO: Send event instead!!!
}

void HUDSystem::Update(float deltaTime)
{
	assert(m_ecs && "ERROR: EntityManager is nullptr!");

	// if aiming...  (do with event instead)?
	auto player = m_ecs->FindEntity(m_signatures["Player"]);
	if (!player.has_value())
		return;

	auto cursor = m_ecs->FindEntity(m_signatures["Cursor"]);
	if (!cursor.has_value())
		return;

	// press 1 to test...
	auto* characterStateComponent = m_ecs->GetComponent<CharacterStateComponent>(player.value());
	auto* spriteComponent = m_ecs->GetComponent<SpriteComponent>(cursor.value());

	std::string texture = characterStateComponent->IsAiming ? "crosshair" : "mouse_icon";

	spriteComponent->Subtexture = &Hi_Engine::ResourceHolder<Hi_Engine::Subtexture2D, Hi_Engine::SubtextureData>::GetInstance().GetResource({ texture, 0, 0 });
}

void HUDSystem::SetSignature()
{
	m_signatures.insert({ "Player", m_ecs->GetSignature<PlayerControllerComponent>() });
	m_signatures.insert({ "Cursor", m_ecs->GetSignature<CursorComponent>() });
}

void HUDSystem::SetupHUDElements()
{
	if (!m_ecs)
		return;

	auto player = m_ecs->FindEntity(m_signatures["Player"]);
	if (!player.has_value())
		return;	
	
	UpdateHealthDisplay(player.value());
	UpdateInventoryBar();
}

void HUDSystem::UpdateHealthDisplay(Entity entity)
{
	auto* healthComponent = m_ecs->GetComponent<HealthComponent>(entity); // OR stats component (check health)

	if (!healthComponent)
		return;

	// TODO; Get entities with Hudcomponent (that are hearts), set if should be rendered based on players health...

	IVector2 windowSize{ 1400, 800 };

	auto window = Hi_Engine::ServiceLocator::GetWindow();
	if (auto win = window.lock())
	{
		windowSize = win->GetSize();
	}

	// Set visibility only? Read from json!?
	for (int i = 0; i < healthComponent->CurrentValue; ++i)
	{
		Entity heart = m_ecs->CreateEntity("HeartContainer");

		auto* transformComponent = m_ecs->GetComponent<TransformComponent>(heart);
		float xOffset = transformComponent->Scale.x;
		float yOffset = windowSize.y - transformComponent->Scale.y;

		transformComponent->CurrentPos = { xOffset + (i * transformComponent->Scale.x), yOffset };
	}
}

void HUDSystem::UpdateInventoryBar()
{
	//auto* inventoryBar = m_entityManager->FindFirst<GridComponent>(); // Fix!

	auto window = Hi_Engine::ServiceLocator::GetWindow();
	if (auto win = window.lock())
	{


		//auto* transformComponent = inventoryBar->GetComponent<TransformComponent>();
		//transformComponent->CurrentPos.x = 0.5f;
		//transformComponent->CurrentPos.x = win->GetSize().x * 0.5f;
		//transformComponent->CurrentPos.y = 50.f;
	}

}
