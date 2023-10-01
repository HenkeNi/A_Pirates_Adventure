#include "Pch.h"
#include "InputSystem.h"
#include "EntityManager.h"
#include "Core/CoreComponents.h"
//#include "../Entity/Components/Controllers/ControllerComponents.h"



InputSystem::InputSystem()
{
}

InputSystem::~InputSystem()
{
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

	auto entities = m_entityManager->FindAllWithComponents<InputComponent>();

	using inputHandler = Hi_Engine::InputHandler;
	using key = Hi_Engine::eInputType;

	for (auto entity : entities) // TEMP...
	{
		auto inputComponent = entity->GetComponent<InputComponent>();

		if (inputHandler::IsKeyHeld(key::Key_W) || inputHandler::IsKeyPressed(key::Key_W))
		{
			inputComponent->InputStates.insert_or_assign(key::Key_W, true);
		}
		else
		{
			inputComponent->InputStates.insert_or_assign(key::Key_W, false);
		}
		
		if (inputHandler::IsKeyHeld(key::Key_S) || inputHandler::IsKeyPressed(key::Key_S))
		{
			inputComponent->InputStates.insert_or_assign(key::Key_S, true);
		}
		else
		{
			inputComponent->InputStates.insert_or_assign(key::Key_S, false);
		}

		if (inputHandler::IsKeyHeld(key::Key_A) || inputHandler::IsKeyPressed(key::Key_A))
		{
			inputComponent->InputStates.insert_or_assign(key::Key_A, true);
		}
		else
		{
			inputComponent->InputStates.insert_or_assign(key::Key_A, false);
		}

		if (inputHandler::IsKeyHeld(key::Key_D) || inputHandler::IsKeyPressed(key::Key_D))
		{
			inputComponent->InputStates.insert_or_assign(key::Key_D, true);
		}
		else
		{
			inputComponent->InputStates.insert_or_assign(key::Key_D, false);
		}

		if (inputHandler::IsKeyHeld(key::Key_Space) || inputHandler::IsKeyPressed(key::Key_Space))
		{
			inputComponent->InputStates.insert_or_assign(key::Key_Space, true);
		}
		else
		{
			inputComponent->InputStates.insert_or_assign(key::Key_Space, false);
		}

		if (inputHandler::IsKeyHeld(key::Key_Shift) || inputHandler::IsKeyPressed(key::Key_Shift))
		{
			inputComponent->InputStates.insert_or_assign(key::Key_Shift, true);
		}
		else
		{
			inputComponent->InputStates.insert_or_assign(key::Key_Shift, false);
		}
	}
}
