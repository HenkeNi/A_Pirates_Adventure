#include "Pch.h"
#include "InputSystem.h"
#include "ECS/ECS.h"
#include "Core/Input/InputHandler.h"
#include "Platform/Window/Window.h"
#include "../Components/CoreComponents.h"

namespace Hi_Engine
{
	FVector2 ConvertScreenToWorldPosition(const FVector2& mousePos, int windowWidth, int windowHeight, const glm::mat4& viewProjectionMatrix);

	InputSystem::InputSystem(ECSCoordinator& ecs, InputHandler& inputHandler, Window& window)
		: System{ ecs }, m_inputHandler{ inputHandler }, m_window{ window }
	{
	}

	void InputSystem::Update(float deltaTime)
	{
		m_inputHandler.ProcessInput();

		const auto& cameraComponents = m_ecs.GetComponents<CameraComponent>();
		auto cameraIterator = std::find_if(cameraComponents.begin(), cameraComponents.end(), [](const CameraComponent& component) { return component.IsActive; });

		if (cameraIterator == cameraComponents.end())
			return;

		IVector2 windowSize = m_window.GetSize();
	
		auto projectionMatrix = cameraIterator->Camera.GetViewProjectionMatrix();

		FVector2 mousePosition = InputHandler::GetMousePosition();
		FVector2 mouseWorldPosition = ConvertScreenToWorldPosition(mousePosition, windowSize.x, windowSize.y, projectionMatrix);
		float mouseScroll = InputHandler::GetScrollOffset();

		for (auto& inputComponent : m_ecs.GetComponents<InputComponent>())
		{
			for (auto& [key, state] : inputComponent.InputStates)
			{
				state = InputHandler::IsKeyHeld(key) || InputHandler::IsKeyPressed(key);
			}

			inputComponent.MousePosition = mousePosition;
			inputComponent.MouseWorldPosition = mouseWorldPosition;
			inputComponent.MouseScroll = mouseScroll;
		}

		//if (InputHandler::IsMouseButtonPressed(Hi_Engine::eMouseBtn::LeftBtn))
		//{
			//PostMaster::GetInstance().SendMessage({ eMessage::MouseClicked, mousePosition }); // dont send event?
		//}

		m_inputHandler.Reset();
	}

	eUpdatePhase InputSystem::GetUpdatePhase() const
	{
		return eUpdatePhase::PreUpdate;
	}

	FVector2 ConvertScreenToWorldPosition(const FVector2& mousePos, int windowWidth, int windowHeight, const glm::mat4& viewProjectionMatrix)
	{
		// Convert mouse coordinates to NDC
		float ndcX = (2.0f * mousePos.x) / windowWidth - 1.0f;
		float ndcY = 1.0f - (2.0f * mousePos.y) / windowHeight;

		// Create viewport matrix
		//glm::vec4 viewport = glm::vec4(0.0f, 0.0f, windowWidth, windowHeight);

		// Create inverse projection-view matrix
		glm::mat4 invPVMatrix = glm::inverse(viewProjectionMatrix);

		// Perform unprojection
		glm::vec4 mouseCoords = glm::vec4(ndcX, ndcY, 0.0f, 1.0f);
		glm::vec4 worldCoordsHomogeneous = invPVMatrix * mouseCoords;
		worldCoordsHomogeneous /= worldCoordsHomogeneous.w; // Convert to Euclidean space

		// Extract world coordinates
		return { worldCoordsHomogeneous.x, worldCoordsHomogeneous.y };
	}
}