#include "Pch.h"
#include "InputSystem.h"
#include "Entities/EntityManager.h"
#include "Components/Core/CoreComponents.h"
//#include "../Entity/Components/Controllers/ControllerComponents.h"



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
	auto keyState = anEvent.GetKeyState(Hi_Engine::eKey::Key_W);

	//if (keyState == Hi_Engine::eInputState::Press)
	//	;
		// std::cout << "PRESS W";
}

void InputSystem::Receive(Message& aMsg)
{
	// listen for input.. (update entities=
}

// TODO; update InputComponent with pressed keys...
void InputSystem::Update(float aDeltaTime)
{
	if (!m_entityManager)
		return;

	auto entities = m_entityManager->FindAll<InputComponent>();

	using InputHandler = Hi_Engine::InputHandler;
	using key = Hi_Engine::eKey;

	auto mousePos = InputHandler::GetMousePosition();
	float mouseScroll = InputHandler::GetScrollOffset();

	for (auto entity : entities) // TEMP...
	{
		auto* inputComponent = entity->GetComponent<InputComponent>();

		/*for (const auto& input : inputComponent->InputStates)
		{

		}*/

		// TODO; init active keys (read from json)...   Set in iNputComponent???
		if (InputHandler::IsKeyHeld(key::Key_W) || InputHandler::IsKeyPressed(key::Key_W))
		{
			inputComponent->InputStates.insert_or_assign(key::Key_W, true);
		}
		else
		{
			inputComponent->InputStates.insert_or_assign(key::Key_W, false);
		}
		
		if (InputHandler::IsKeyHeld(key::Key_S) || InputHandler::IsKeyPressed(key::Key_S))
		{
			inputComponent->InputStates.insert_or_assign(key::Key_S, true);
		}
		else
		{
			inputComponent->InputStates.insert_or_assign(key::Key_S, false);
		}

		if (InputHandler::IsKeyHeld(key::Key_A) || InputHandler::IsKeyPressed(key::Key_A))
		{
			inputComponent->InputStates.insert_or_assign(key::Key_A, true);
		}
		else
		{
			inputComponent->InputStates.insert_or_assign(key::Key_A, false);
		}

		if (InputHandler::IsKeyHeld(key::Key_D) || InputHandler::IsKeyPressed(key::Key_D))
		{
			inputComponent->InputStates.insert_or_assign(key::Key_D, true);
		}
		else
		{
			inputComponent->InputStates.insert_or_assign(key::Key_D, false);
		}

		if (InputHandler::IsKeyHeld(key::Key_Space) || InputHandler::IsKeyPressed(key::Key_Space))
		{
			inputComponent->InputStates.insert_or_assign(key::Key_Space, true);
		}
		else
		{
			inputComponent->InputStates.insert_or_assign(key::Key_Space, false);
		}

		if (InputHandler::IsKeyHeld(key::Key_Escape) || InputHandler::IsKeyPressed(key::Key_Escape))
		{
			inputComponent->InputStates.insert_or_assign(key::Key_Escape, true);
		}
		else
		{
			inputComponent->InputStates.insert_or_assign(key::Key_Escape, false);
		}


		if (InputHandler::IsKeyHeld(key::Key_LShift) || InputHandler::IsKeyPressed(key::Key_LShift))
		{
			inputComponent->InputStates.insert_or_assign(key::Key_LShift, true);
		}
		else
		{
			inputComponent->InputStates.insert_or_assign(key::Key_LShift, false);
		}


		inputComponent->MousePosition = { mousePos.x, mousePos.y };
		inputComponent->MouseScroll = mouseScroll;


		// inputComponent->MousePosition = inputHandler::GetN
	}
}
