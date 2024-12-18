#include "Pch.h"
#include "InputSystem.h"
#include "Components/Core/CoreComponents.h"
#include "ECS.h"

FVector2 ConvertScreenToWorldPosition(const FVector2& mousePos, int windowWidth, int windowHeight, const glm::mat4& viewProjectionMatrix);

InputSystem::InputSystem()
{
	Hi_Engine::EventDispatcher::GetInstance().Subscribe(this);
}

InputSystem::~InputSystem()
{
	Hi_Engine::EventDispatcher::GetInstance().Unsubscribe(this);
}

void InputSystem::HandleEvent(Hi_Engine::InputEvent& inputEvent)
{
	// auto keyState = anEvent.GetKeyState(Hi_Engine::eKey::Key_W);
}

void InputSystem::Update(float deltaTime)
{
	assert(m_ecs && "[InputSystem::Update] - ECS is not initialized!");

	auto camera = m_ecs->FindEntity(m_signatures["Camera"]);
	if (!camera.has_value())
		return;

	IVector2 windowSize;
	if (auto window = Hi_Engine::ServiceLocator::GetWindow().lock())
	{
		windowSize = window->GetSize();
	}

	auto* cameraComponent = m_ecs->GetComponent<CameraComponent>(camera.value());
	auto projectionMatrix = cameraComponent->Camera.GetViewProjectionMatrix();

	using InputHandler = Hi_Engine::InputHandler;

	FVector2 mousePosition = InputHandler::GetMousePosition();
	FVector2 mouseWorldPosition = ConvertScreenToWorldPosition(mousePosition, windowSize.x, windowSize.y, projectionMatrix);
	float mouseScroll = InputHandler::GetScrollOffset();
	
	for (auto& inputComponent : m_ecs->GetComponents<InputComponent>())
	{
		for (auto& [key, state] : inputComponent.InputStates)
		{
			state = InputHandler::IsKeyHeld(key) || InputHandler::IsKeyPressed(key);
		}

		inputComponent.MousePosition = mousePosition;
		inputComponent.MouseWorldPosition = mouseWorldPosition;
		inputComponent.MouseScroll = mouseScroll;
	}

	if (InputHandler::IsMouseButtonPressed(Hi_Engine::eMouseBtn::LeftBtn))
	{
		PostMaster::GetInstance().SendMessage({ eMessage::MouseClicked, mousePosition }); // dont send event?
	}
}

void InputSystem::SetSignature()
{
	m_signatures.insert({ "Camera", m_ecs->GetSignature<CameraComponent>() });
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