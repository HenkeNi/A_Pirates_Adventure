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
			inputComponent->m_inputStates.insert_or_assign(key::Key_W, true);
		}
		else
		{
			inputComponent->m_inputStates.insert_or_assign(key::Key_W, false);
		}
		
		if (inputHandler::IsKeyHeld(key::Key_S) || inputHandler::IsKeyPressed(key::Key_S))
		{
			inputComponent->m_inputStates.insert_or_assign(key::Key_S, true);
		}
		else
		{
			inputComponent->m_inputStates.insert_or_assign(key::Key_S, false);
		}

		if (inputHandler::IsKeyHeld(key::Key_A) || inputHandler::IsKeyPressed(key::Key_A))
		{
			inputComponent->m_inputStates.insert_or_assign(key::Key_A, true);
		}
		else
		{
			inputComponent->m_inputStates.insert_or_assign(key::Key_A, false);
		}

		if (inputHandler::IsKeyHeld(key::Key_D) || inputHandler::IsKeyPressed(key::Key_D))
		{
			inputComponent->m_inputStates.insert_or_assign(key::Key_D, true);
		}
		else
		{
			inputComponent->m_inputStates.insert_or_assign(key::Key_D, false);
		}
	}
}
