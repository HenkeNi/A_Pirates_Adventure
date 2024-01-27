#include "Pch.h"
#include "InputSystem.h"
#include "Entities/EntityManager.h"
#include "Components/Core/CoreComponents.h"


InputSystem::InputSystem()
{
	Hi_Engine::Dispatcher::GetInstance().Subscribe(this);
}

InputSystem::~InputSystem()
{
	Hi_Engine::Dispatcher::GetInstance().Unsubscribe(this);
}

void InputSystem::HandleEvent(Hi_Engine::InputEvent& anEvent)
{
	// auto keyState = anEvent.GetKeyState(Hi_Engine::eKey::Key_W);
}

void InputSystem::Receive(Message& aMsg)
{
}

void InputSystem::Update(float aDeltaTime)
{
	if (!m_entityManager)
		return;

	using InputHandler = Hi_Engine::InputHandler;

	auto entities = m_entityManager->FindAll<InputComponent>();
	
	auto mousePos	  = InputHandler::GetMousePosition();
	float mouseScroll = InputHandler::GetScrollOffset();

	for (auto entity : entities)
	{
		auto* inputComponent = entity->GetComponent<InputComponent>();

		for (auto& [key, state] : inputComponent->InputStates)
		{
			state = InputHandler::IsKeyHeld(key) || InputHandler::IsKeyPressed(key);
		}

		inputComponent->MousePosition = { mousePos.x, mousePos.y };
		inputComponent->MouseScroll = mouseScroll;
	}
}