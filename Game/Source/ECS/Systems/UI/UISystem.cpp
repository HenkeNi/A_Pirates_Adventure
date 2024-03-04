#include "Pch.h"
#include "UISystem.h"
#include "Entities/EntityManager.h"


UISystem::UISystem()
{
}

UISystem::~UISystem()
{
}

void UISystem::Receive(Message& aMsg)
{
}

void UISystem::Update(float aDeltaTime)
{
	if (!m_entityManager)
		return;

	// LISTEN For mouse triggering instead?
		
	auto mousePosition = Hi_Engine::InputHandler::GetMousePosition();
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

glm::vec2 UISystem::ScreenToWorldCoordinates(const glm::vec2& aPosition)
{
	return glm::vec2();
}

void UISystem::OnButtonActivated(Entity* aButton)
{
	auto* buttonComponent = aButton->GetComponent<ButtonComponent>();

	if (buttonComponent->OnClick)
		buttonComponent->OnClick();
}