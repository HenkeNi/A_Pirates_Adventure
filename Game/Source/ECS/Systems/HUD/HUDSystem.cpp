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
	UpdateCursor();
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



		auto* e1 = m_entityManager->Create("HeartContainer");
		auto* e2 = m_entityManager->Create("HeartContainer");
		auto* e3 = m_entityManager->Create("HeartContainer");
		auto* e4 = m_entityManager->Create("HeartContainer");
		
		auto* transform1 = e1->GetComponent<TransformComponent>();
		transform1->CurrentPos = { -4.5f, 2.5f };

		auto* transform2 = e2->GetComponent<TransformComponent>();
		transform2->CurrentPos = { 4.5f, 2.5f };

		auto* transform3 = e3->GetComponent<TransformComponent>();
		transform3->CurrentPos = { -4.5f, -2.5f };

		auto* transform4 = e4->GetComponent<TransformComponent>();
		transform4->CurrentPos = { 4.5f, -2.5f };

}

void HUDSystem::UpdateCursor()
{
	auto* cursor = m_entityManager->FindFirst<CursorComponent>();
	auto* input = m_entityManager->FindFirst<InputComponent>();

	if (!cursor || !input)
		return;

	auto* inputComponent = input->GetComponent<InputComponent>();

	auto mousePosition = inputComponent->MousePosition;
	//std::cout << "Mouse pos: " << inputComponent->MousePosition.x << ", " << inputComponent->MousePosition.y << "\n";

	float old_valueX = (float)mousePosition.x;
	float old_minX = 0;
	float old_maxX = 1400;
	float new_minX = -4.5f;
	float new_maxX = 4.5f;

	float new_valueX = ((old_valueX - old_minX) / (old_maxX - old_minX)) * (new_maxX - new_minX) + new_minX;


	float old_valueY = (float)mousePosition.y;
	float old_minY = 800;
	float old_maxY = 0;
	float new_minY = -2.5f;
	float new_maxY = 2.5f;

	float new_valueY = ((old_valueY - old_minY) / (old_maxY - old_minY)) * (new_maxY - new_minY) + new_minY;

	//float x = mousePosition.x / 1400.f;

	// Update the position of the cursor
	auto* transformComponent = cursor->GetComponent<TransformComponent>();
	transformComponent->CurrentPos.x = new_valueX; // Hi_Engine::InputHandler::GetMousePosition().x;
	transformComponent->CurrentPos.y = new_valueY;// 0.f; //  Hi_Engine::InputHandler::GetMousePosition().y;
	
	//transformComponent->CurrentPos.x = (float)inputComponent->MousePosition.x;
	//transformComponent->CurrentPos.y = (float)inputComponent->MousePosition.y;
	/*transformComponent->CurrentPos.x = 1400.f / (float)inputComponent->MousePosition.x;
	transformComponent->CurrentPos.y = 800.f / (float)inputComponent->MousePosition.y;*/



	// TODO: Send event instead!!!
	auto* player = m_entityManager->FindFirst<PlayerControllerComponent>();

	// press 1 to test...
	auto* characterStateComponent = player->GetComponent<CharacterStateComponent>();
	if (characterStateComponent->IsAiming)
	{
		cursor->GetComponent<SpriteComponent>()->Subtexture = &Hi_Engine::ResourceHolder<Hi_Engine::Subtexture2D>::GetInstance().GetResource("crosshair_00");
	}
	else
		cursor->GetComponent<SpriteComponent>()->Subtexture = &Hi_Engine::ResourceHolder<Hi_Engine::Subtexture2D>::GetInstance().GetResource("raft_00");

}