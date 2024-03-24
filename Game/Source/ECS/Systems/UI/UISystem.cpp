#include "Pch.h"
#include "UISystem.h"
#include "Entities/EntityManager.h"


UISystem::UISystem()
{
	PostMaster::GetInstance().Subscribe(eMessage::EntityCreated, this);
}

UISystem::~UISystem()
{
	PostMaster::GetInstance().Unsubscribe(eMessage::EntityCreated, this);
}

void UISystem::Receive(Message& message)
{
	if (message.GetMessageType() != eMessage::EntityCreated)
		return;

	if (auto* entity = std::any_cast<Entity*>(message.GetData()))
	{
		if (!entity->HasComponent<ButtonComponent>())
			return;

		// AssignCallback(entity);
	}
}

void UISystem::Update(float deltaTime)
{
	if (!m_entityManager)
		return;

	UpdateCursor();	
}

glm::vec2 UISystem::ScreenToWorldCoordinates(const glm::vec2& position)
{
	return glm::vec2();
}

void UISystem::OnButtonActivated(Entity* button)
{
	auto* buttonComponent = button->GetComponent<ButtonComponent>();

	if (buttonComponent->IsPressed)
		return;

	buttonComponent->IsPressed = true; // TODO; make sure to add timstamp and reset?

	PostMaster::GetInstance().SendMessage({ eMessage::ButtonActivated, button });

	//if (buttonComponent->OnClick)
	//	buttonComponent->OnClick();
}

//void UISystem::AssignCallback(Entity* button)
//{
//	auto* buttonComponent = button->GetComponent<ButtonComponent>();
//}

void UISystem::UpdateCursor()
{
	// LISTEN For mouse triggering instead?

	auto* cursor = m_entityManager->FindFirst<CursorComponent>();

	if (!cursor)
		return;

	auto* input = m_entityManager->FindFirst<InputComponent>(); // if no InputComponent => pull straight from inputhandler

	glm::vec2 mousePosition;

	if (input)
	{

		auto* inputComponent = input->GetComponent<InputComponent>();
		mousePosition = { inputComponent->MousePosition.x, inputComponent->MousePosition.y };
		// mousePosition = inputComponent->MouseWorldPosition;
	}
	else
	{
		mousePosition = Hi_Engine::InputHandler::GetMousePosition();
	}



	float old_valueX = (float)mousePosition.x;
	float old_minX = 0;
	float old_maxX = 1400;
	float new_minX = -4.5f; // Min x position screen?!
	float new_maxX = 4.5f;	// max x position screen)!

	float new_valueX = ((old_valueX - old_minX) / (old_maxX - old_minX)) * (new_maxX - new_minX) + new_minX;

	float old_valueY = (float)mousePosition.y;
	float old_minY = 800;
	float old_maxY = 0;
	float new_minY = -2.5f; // Min y position screen?!
	float new_maxY = 2.5f; // max y position screen)!

	float new_valueY = ((old_valueY - old_minY) / (old_maxY - old_minY)) * (new_maxY - new_minY) + new_minY;


	auto* transformComponent = cursor->GetComponent<TransformComponent>();
	transformComponent->CurrentPos.x = new_valueX; // Hi_Engine::InputHandler::GetMousePosition().x;
	transformComponent->CurrentPos.y = new_valueY;// 0.f; //  Hi_Engine::InputHandler::GetMousePosition().y;

	auto entities = m_entityManager->FindAll<ButtonComponent>();

	for (const auto& entity : entities)
	{
		auto* buttonComponent = entity->GetComponent<ButtonComponent>();
		auto* colliderComponent = entity->GetComponent<ColliderComponent>();

		if (colliderComponent->Collider.IsInside({ new_valueX, new_valueY }))
		{
			if (Hi_Engine::InputHandler::IsMouseButtonPressed(Hi_Engine::eMouseBtn::LeftBtn))
			{
				OnButtonActivated(entity);
			}
		}
	}





}

//void HUDSystem::UpdateCursor()
//{
//
//
//
//	auto mousePosition = inputComponent->MousePosition;
//	//std::cout << "Mouse pos: " << inputComponent->MousePosition.x << ", " << inputComponent->MousePosition.y << "\n";
//
//	float old_valueX = (float)mousePosition.x;
//	float old_minX = 0;
//	float old_maxX = 1400;
//	float new_minX = -4.5f; // Min x position screen?!
//	float new_maxX = 4.5f;	// max x position screen)!
//
//	float new_valueX = ((old_valueX - old_minX) / (old_maxX - old_minX)) * (new_maxX - new_minX) + new_minX;
//
//
//	float old_valueY = (float)mousePosition.y;
//	float old_minY = 800;
//	float old_maxY = 0;
//	float new_minY = -2.5f; // Min y position screen?!
//	float new_maxY = 2.5f; // max y position screen)!
//
//	float new_valueY = ((old_valueY - old_minY) / (old_maxY - old_minY)) * (new_maxY - new_minY) + new_minY;
//
//	//float x = mousePosition.x / 1400.f;
//
//	// Update the position of the cursor
//	auto* transformComponent = cursor->GetComponent<TransformComponent>();
//	transformComponent->CurrentPos.x = new_valueX; // Hi_Engine::InputHandler::GetMousePosition().x;
//	transformComponent->CurrentPos.y = new_valueY;// 0.f; //  Hi_Engine::InputHandler::GetMousePosition().y;
//
//	//transformComponent->CurrentPos.x = (float)inputComponent->MousePosition.x;
//	//transformComponent->CurrentPos.y = (float)inputComponent->MousePosition.y;
//	/*transformComponent->CurrentPos.x = 1400.f / (float)inputComponent->MousePosition.x;
//	transformComponent->CurrentPos.y = 800.f / (float)inputComponent->MousePosition.y;*/
//
//
//
//	// TODO: Send event instead!!!
//	auto* player = m_entityManager->FindFirst<PlayerControllerComponent>();
//
//	// press 1 to test...
//	auto* characterStateComponent = player->GetComponent<CharacterStateComponent>();
//	if (characterStateComponent->IsAiming)
//	{
//		cursor->GetComponent<SpriteComponent>()->Subtexture = &Hi_Engine::ResourceHolder<Hi_Engine::Subtexture2D>::GetInstance().GetResource("crosshair_00");
//	}
//	else
//		cursor->GetComponent<SpriteComponent>()->Subtexture = &Hi_Engine::ResourceHolder<Hi_Engine::Subtexture2D>::GetInstance().GetResource("mouse_icon_00");
//
//}