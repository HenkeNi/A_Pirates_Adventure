#include "Pch.h"
#include "InputSystem.h"
#include "ECS/World/World.h"
#include "Services/Input/InputService.h"
#include "Services/Window/WindowService.h"
#include "../Components/CoreComponents.h"

namespace Hi_Engine
{
	FVector2 ConvertScreenToWorldPosition(const FVector2& mousePos, int windowWidth, int windowHeight, const glm::mat4& viewProjectionMatrix);

	InputSystem::InputSystem(World& world, InputService& input, WindowService& window)
		: System{ world }, m_inputService{ input }, m_windowService{ window }
	{
	}

	void InputSystem::Update(float deltaTime)
	{
		m_inputService.ProcessInput();

		auto cameraView = m_world.GetComponentView<CameraComponent>(); // TODO; use FindIf fnc later...
		CameraComponent* cameraComponent = nullptr;

		cameraView.ForEach([&](CameraComponent& component)
			{
				if (component.IsActive)
				{
					cameraComponent = &component;
					return;
				}
				// will break / return work?
			});

		if (!cameraComponent)
			return;

		// maybe store view projection matrix elsewhere??
		//const auto& cameraComponents = m_ecs.GetComponentView<CameraComponent>();
		//auto cameraIterator = std::find_if(cameraComponents.begin(), cameraComponents.end(), [](const CameraComponent& component) { return component.IsActive; });

		//if (cameraIterator == cameraComponents.end())
			//return;

		IVector2 windowSize = m_windowService.GetSize();
	
		auto projectionMatrix = cameraComponent->Camera.GetViewProjectionMatrix();

		FVector2 mousePosition = m_inputService.GetMousePosition(); //InputHandler::GetMousePosition();
		FVector2 mouseWorldPosition = ConvertScreenToWorldPosition(mousePosition, windowSize.x, windowSize.y, projectionMatrix);
		float mouseScroll = m_inputService.GetScrollOffset(); // InputHandler::GetScrollOffset();

		auto inputView = m_world.GetComponentView<InputComponent>();
		inputView.ForEach([&](InputComponent& component) 
			{
				for (auto& [key, state] : component.InputStates)
				{
					state = m_inputService.IsKeyHeld(key) || m_inputService.IsKeyPressed(key); // Get key state instead?
					// state = InputHandler::IsKeyHeld(key) || InputHandler::IsKeyPressed(key);
				}

				component.MousePosition = mousePosition;
				component.MouseWorldPosition = mouseWorldPosition;
				component.MouseScroll = mouseScroll;

			});

	/*	for (auto& inputComponent : m_ecs.GetComponentView<InputComponent>())
		{
			for (auto& [key, state] : inputComponent.InputStates)
			{
				state = InputHandler::IsKeyHeld(key) || InputHandler::IsKeyPressed(key);
			}

			inputComponent.MousePosition = mousePosition;
			inputComponent.MouseWorldPosition = mouseWorldPosition;
			inputComponent.MouseScroll = mouseScroll;
		}*/

		//if (InputHandler::IsMouseButtonPressed(Hi_Engine::eMouseBtn::LeftBtn))
		//{
			//PostMaster::GetInstance().SendMessage({ eMessage::MouseClicked, mousePosition }); // dont send event?
		//}

		m_inputService.Reset();
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