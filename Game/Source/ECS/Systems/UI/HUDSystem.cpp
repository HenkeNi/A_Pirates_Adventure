#include "Pch.h"
#include "HUDSystem.h"
#include "Entities/EntityManager.h"
#include "Components/Core/CoreComponents.h"
#include "Components/Gameplay/GameplayComponents.h"
#include "Components/AI/AIComponents.h"
#include "Components/UI/UIComponents.h"


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
		auto* entity = std::any_cast<Entity*>(message.GetData());
		if (entity->HasComponent<PlayerControllerComponent>())
		{
			UpdateHealthDisplay(entity);

		}
	}

	if (message.GetMessageType() == eMessage::ItemCollected)
	{
		auto* inventory = m_entityManager->FindFirst<InventoryComponent>();

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
	assert(m_entityManager && "ERROR: EntityManager is nullptr!");

	// if aiming...  (do with event instead)?
	auto* player = m_entityManager->FindFirst<PlayerControllerComponent>();
	if (!player)
		return;

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

void HUDSystem::SetupHUDElements()
{
	if (!m_entityManager)
		return;

	auto* player = m_entityManager->FindFirst<PlayerControllerComponent>();
	UpdateHealthDisplay(player);
	UpdateInventoryBar();
}

void HUDSystem::UpdateHealthDisplay(Entity* entity)
{
	auto* healthComponent = entity->GetComponent<HealthComponent>(); // OR stats component (check health)

	if (!healthComponent)
		return;

	// TODO; Get entities with Hudcomponent (that are hearts), set if should be rendered based on players health...

	IVector2 windowSize{ 1400, 800 };

	auto window = Hi_Engine::ServiceLocator::GetWindow();
	if (auto win = window.lock())
	{
		windowSize = win->GetSize();
	}

	for (int i = 0; i < healthComponent->CurrentValue; ++i)
	{
		auto* heart = m_entityManager->Create("heart_container");

		auto* transform = heart->GetComponent<TransformComponent>();
		float xOffset = transform->Scale.x;
		float yOffset = windowSize.y - transform->Scale.y;

		transform->CurrentPos = { xOffset + (i * transform->Scale.x), yOffset };		
	}
}

void HUDSystem::UpdateInventoryBar()
{
	auto* inventoryBar = m_entityManager->FindFirst<GridComponent>(); // Fix!

	auto window = Hi_Engine::ServiceLocator::GetWindow();
	if (auto win = window.lock())
	{


		//auto* transformComponent = inventoryBar->GetComponent<TransformComponent>();
		//transformComponent->CurrentPos.x = 0.5f;
		//transformComponent->CurrentPos.x = win->GetSize().x * 0.5f;
		//transformComponent->CurrentPos.y = 50.f;
	}

}
