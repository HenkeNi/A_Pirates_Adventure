#include "Pch.h"
#include "InputSystem.h"
#include "Components/Core/CoreComponents.h"
#include "ECS.h"

FVector2 ConvertScreenToWorldPosition(const FVector2& mousePos, int windowWidth, int windowHeight, const glm::mat4& viewProjectionMatrix);

InputSystem::InputSystem()
{
	Hi_Engine::Dispatcher::GetInstance().Subscribe(this);
}

InputSystem::~InputSystem()
{
	Hi_Engine::Dispatcher::GetInstance().Unsubscribe(this);
}

void InputSystem::HandleEvent(Hi_Engine::InputEvent& inputEvent)
{
	// auto keyState = anEvent.GetKeyState(Hi_Engine::eKey::Key_W);
}

void InputSystem::Update(float deltaTime)
{
	assert(m_ecs && "[InputSystem - ERROR]: ECS is not initialized!");

	auto camera = m_ecs->FindEntity(m_signatures["Camera"]);
	if (!camera.has_value())
		return;

	using InputHandler = Hi_Engine::InputHandler;

	FVector2 mousePosition = InputHandler::GetMousePosition();
	float mouseScroll = InputHandler::GetScrollOffset();

	auto* cameraComponent = m_ecs->GetComponent<CameraComponent>(camera.value());
	auto projectionMatrix = cameraComponent->Camera.GetViewProjectionMatrix();

	IVector2 windowSize = { 1400, 800 };
	if (auto window = Hi_Engine::ServiceLocator::GetWindow().lock())
	{
		windowSize = window->GetSize();
	}

	auto& inputComponents = m_ecs->GetComponents<InputComponent>();

	for (auto& inputComponent : inputComponents)
	{

		for (auto& [key, state] : inputComponent.InputStates)
		{
			state = InputHandler::IsKeyHeld(key) || InputHandler::IsKeyPressed(key);
		}

		inputComponent.MousePosition = mousePosition;
		inputComponent.MouseScroll = mouseScroll;
		inputComponent.MouseWorldPosition = ConvertScreenToWorldPosition(mousePosition, 1400, 800, projectionMatrix);
	}

	if (InputHandler::IsMouseButtonPressed(Hi_Engine::eMouseBtn::LeftBtn))
	{
		PostMaster::GetInstance().SendMessage({ eMessage::MouseClicked, mousePosition });
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