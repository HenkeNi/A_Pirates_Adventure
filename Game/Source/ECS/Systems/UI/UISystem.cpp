#include "Pch.h"
#include "UISystem.h"
#include "Components/UI/UIComponents.h"
#include "Components/Core/CoreComponents.h"
#include "ECS/ECS.h"


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
	// TODO; listen to screen size changed...
	// TODO; change mouse icon instead

	if (message.GetMessageType() == eMessage::EntityCreated)
	{
		UpdateCollider(std::any_cast<Entity>(message.GetData()));
	}
}

void UISystem::Update(float deltaTime)
{
	assert(m_ecs && "[UISystem - ERROR]: ECS is not initialized!");

	UpdateCursor();	
}

void UISystem::SetSignature()
{
	m_signatures.insert({ "Cursor", m_ecs->GetSignature<CursorComponent>() });
	m_signatures.insert({ "Input", m_ecs->GetSignature<InputComponent>() });
	m_signatures.insert({ "Buttons", m_ecs->GetSignature<ButtonComponent>() });
}

void UISystem::OnButtonActivated(Entity button)
{
	if (auto* buttonComponent = m_ecs->GetComponent<ButtonComponent>(button))
	{
		if (buttonComponent->IsPressed)
			return;

		buttonComponent->IsPressed = true; // TODO; make sure to add timstamp and reset?

		if (buttonComponent->OnClick) // or just send evnet??
			buttonComponent->OnClick();

		PostMaster::GetInstance().SendMessage({ eMessage::ButtonActivated, button });
	}
}

void UISystem::UpdateCollider(Entity entity)
{
	if (!m_ecs->HasComponent<UIComponent>(entity) && !m_ecs->HasComponent<HUDComponent>(entity))
		return;

	if (auto* colliderComponent = m_ecs->GetComponent<ColliderComponent>(entity))
	{
		const IVector2 windowSize = Hi_Engine::ServiceLocator::GetWindow().lock()->GetSize();
			
		const auto& [currentPos, previousPos, scale, pivot, rotation] = *m_ecs->GetComponent<TransformComponent>(entity);

		FVector2 size;
		size.x = Hi_Engine::Math::Rerange<float>(scale.x, { 0.f, (float)windowSize.x }, { 0.f, 1.f });
		size.y = Hi_Engine::Math::Rerange<float>(scale.y, { 0.f, (float)windowSize.y }, { 0.f, 1.f });


		FVector2 offset;
		offset.x = scale.x * pivot.x;
		offset.y = scale.y * pivot.y;

		colliderComponent->Collider.Init({ currentPos.x - size.x * 0.5f, currentPos.y - size.x * 0.5f }, { currentPos.x + size.x * 0.5f, currentPos.y + size.y * 0.5f }); // COrrect??
	}
}

//void UISystem::AssignCallback(Entity* button)
//{
//	auto* buttonComponent = button->GetComponent<ButtonComponent>();
//}

void UISystem::UpdateCursor()
{
	// LISTEN For mouse triggering instead?

	auto cursor = m_ecs->FindEntity(m_signatures["Cursor"]);
	if (!cursor.has_value())
		return;

	auto input = m_ecs->FindEntity(m_signatures["Input"]); // if no InputComponent => pull straight from inputhandler

	FVector2 mousePosition = { 0.f, 0.f };

	if (input.has_value())
	{
		auto* inputComponent = m_ecs->GetComponent<InputComponent>(input.value());
		mousePosition = inputComponent->MousePosition;
	}
	else
	{
		mousePosition = Hi_Engine::InputHandler::GetMousePosition();
	}

	
	const IVector2 windowSize = Hi_Engine::ServiceLocator::GetWindow().lock()->GetSize();

	float newXValue = Hi_Engine::Math::Rerange<float>(mousePosition.x, { 0.f, (float)windowSize.x }, { 0.f, 1.f });
	float newYValue = Hi_Engine::Math::Rerange<float>(mousePosition.y, { 0.f, (float)windowSize.y }, { 1.f, 0.f });

	auto* transformComponent = m_ecs->GetComponent<TransformComponent>(cursor.value());
	transformComponent->CurrentPos = { newXValue, newYValue };

	//std::cout << "Mouse x: " << newXValue << ", mouse y: " << newYValue << "\n";

	auto entities = m_ecs->FindEntities(m_signatures["Buttons"]);

	for (const auto& entity : entities)
	{
		auto* buttonComponent = m_ecs->GetComponent<ButtonComponent>(entity);
		auto* colliderComponent = m_ecs->GetComponent<ColliderComponent>(entity);

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

		if (auto* spriteComponent = m_ecs->GetComponent<SpriteComponent>(entity))
		{
			spriteComponent->CurrentColor = isInside ? buttonComponent->HoverColor : spriteComponent->DefaultColor;
		}
	}
}