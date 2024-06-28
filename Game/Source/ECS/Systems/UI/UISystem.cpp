#include "Pch.h"
#include "UISystem.h"
#include "Entities/EntityManager.h"


UISystem::UISystem()
{
	//PostMaster::GetInstance().Subscribe(eMessage::EntityCreated, this);
	PostMaster::GetInstance().Subscribe(eMessage::EntitySpawned, this);
}

UISystem::~UISystem()
{
	//PostMaster::GetInstance().Unsubscribe(eMessage::EntityCreated, this);
	PostMaster::GetInstance().Unsubscribe(eMessage::EntitySpawned, this);
}

void UISystem::Receive(Message& message)
{
	if (message.GetMessageType() != eMessage::EntitySpawned) // listen to screen size changed...
		return;

	if (auto* entity = std::any_cast<Entity*>(message.GetData()))
	{
		if (auto* colliderComponent = entity->GetComponent<ColliderComponent>())
		{

			auto* transformComponent = entity->GetComponent<TransformComponent>();

			auto pos =  transformComponent->CurrentPos;
			const auto& pivot = transformComponent->Pivot;
			auto scale = transformComponent->Scale;
			scale.x = Hi_Engine::Math::Rerange<float>(scale.x, { 0.f, 1400.f },  {0.f, 1.f });
			scale.y = Hi_Engine::Math::Rerange<float>(scale.y, { 0.f, 800.f },    { 0.f, 1.f });

			//float newXPos = Hi_Engine::Math::Rerange<float>(pos.x, { 0.f, 1400.f }, { 0.f, 1.f });
			//float newYPos = Hi_Engine::Math::Rerange<float>(pos.y, { 0.f, 800.f }, { 0.f, 1.f });

			//float scaleX = scale.x / 1400.f;
			//float scaleY = scale.y / 800.f;

			FVector2 offset;
			offset.x = scale.x * pivot.x;
			offset.y = scale.y * pivot.y;


			//colliderComponent->Collider.Init({ pos.x - offset.x, pos.y }, { pos.x + offset.x, pos.y + 100.f});
			
			//colliderComponent->Collider.Init({ pos.x - offset.x, pos.y - offset.y }, { pos.x + offset.x, pos.y + offset.y});
			
			
			colliderComponent->Collider.Init({ pos.x - scale.x * 0.5f, pos.y - scale.x * 0.5f }, { pos.x + scale.x * 0.5f, pos.y + scale.y * 0.5f }); // COrrect??
			//colliderComponent->Collider.Init({ pos.x, pos.y }, { pos.x + scale.x, pos.y + scale.y});
			
		}
		if (!entity->HasComponent<ButtonComponent>())
			return;

		// AssignCallback(entity);
	}

	
}

void UISystem::Update(float deltaTime)
{
	assert(m_entityManager && "ERROR: EntityManager is nullptr!");

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

	if (buttonComponent->OnClick) // or just send evnet??
		buttonComponent->OnClick();

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

	FVector2 mousePosition;

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

	

	

	float windowWidth = 1400.f;
	float newXValue = Hi_Engine::Math::Rerange<float>(mousePosition.x, { 0.f, windowWidth }, { 0.f, 1.f });

	float windowHeight = 800.f;
	float newYValue = Hi_Engine::Math::Rerange<float>(mousePosition.y, { 0.f, windowHeight }, { 1.f, 0.f });

	//float new_valueX = ((mousePosition.x - windowMinWidth) / (windowMaxWidth - windowMinWidth)) * (newMaxWidth - newMinWidth) + newMinWidth;
	//float windowMinHeight = 0.f;
	//float windowMaxHeight = 800.f;
	//float old_valueY = mousePosition.y;
	//float old_minY = 800;
	//float old_maxY = 0;
	//float new_minY = 0.f; // Min y position screen?!
	//float new_maxY = 1.f; // max y position screen)!

	//float new_valueY = ((old_valueY - old_minY) / (old_maxY - old_minY)) * (new_maxY - new_minY) + new_minY;


	auto* transformComponent = cursor->GetComponent<TransformComponent>();
	transformComponent->CurrentPos = { newXValue, newYValue };

	//std::cout << "Mouse x: " << newXValue << ", mouse y: " << newYValue << "\n";

	auto entities = m_entityManager->FindAll<ButtonComponent>();

	for (const auto& entity : entities)
	{
		auto* buttonComponent = entity->GetComponent<ButtonComponent>();
		auto* colliderComponent = entity->GetComponent<ColliderComponent>();

		if (!buttonComponent || !colliderComponent)
			continue;

		bool isInside = colliderComponent->Collider.IsInside({ newXValue, newYValue });

		if (isInside)
		{
			if (Hi_Engine::InputHandler::IsMouseButtonPressed(Hi_Engine::eMouseBtn::LeftBtn))
			{
				OnButtonActivated(entity); // Crashes since second button will be destroyed
			}
		}

		if (auto* spriteComponent = entity->GetComponent<SpriteComponent>())
		{
			spriteComponent->CurrentColor = isInside ? buttonComponent->HoverColor : spriteComponent->DefaultColor;
		}
	}
}