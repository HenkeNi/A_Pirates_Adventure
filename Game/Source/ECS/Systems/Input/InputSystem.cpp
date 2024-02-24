#include "Pch.h"
#include "InputSystem.h"
#include "Entities/EntityManager.h"
#include "Components/Core/CoreComponents.h"

CU::Vector2<double> ConvertMousePositionToWorldPosition(const glm::vec2& mousePos, int windowWidth, int windowHeight, const glm::mat4& aViewProjectionMatrix);

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

		auto* camera = m_entityManager->FindFirst<CameraComponent>();
		auto* cameraComponent = camera->GetComponent<CameraComponent>();
		inputComponent->MouseWorldPosition = ConvertMousePositionToWorldPosition(mousePos, 1400, 800, cameraComponent->Camera.GetViewProjectionMatrix());
	}
}

CU::Vector2<double> ConvertMousePositionToWorldPosition(const glm::vec2& mousePos, int windowWidth, int windowHeight, const glm::mat4& aViewProjectionMatrix)
{
	// Convert mouse coordinates to NDC
	float ndcX = (2.0f * mousePos.x) / windowWidth - 1.0f;
	float ndcY = 1.0f - (2.0f * mousePos.y) / windowHeight;

	// Create viewport matrix
	//glm::vec4 viewport = glm::vec4(0.0f, 0.0f, windowWidth, windowHeight);

	// Create inverse projection-view matrix
	glm::mat4 invPVMatrix = glm::inverse(aViewProjectionMatrix);

	// Perform unprojection
	glm::vec4 mouseCoords = glm::vec4(ndcX, ndcY, 0.0f, 1.0f);
	glm::vec4 worldCoordsHomogeneous = invPVMatrix * mouseCoords;
	worldCoordsHomogeneous /= worldCoordsHomogeneous.w; // Convert to Euclidean space

	// Extract world coordinates
	return { worldCoordsHomogeneous.x, worldCoordsHomogeneous.y };
}

//// TODO; put elsewhere?!
//inline static void MousePosToWorldCoords(const glm::vec2& mousePos, int windowWidth, int windowHeight, const glm::mat4& aViewProjectionMatrix, glm::vec3& worldCoords) {
//
//	// Convert mouse coordinates to NDC
//	float ndcX = (2.0f * mousePos.x) / windowWidth - 1.0f;
//	float ndcY = 1.0f - (2.0f * mousePos.y) / windowHeight;
//
//	// Create viewport matrix
//	//glm::vec4 viewport = glm::vec4(0.0f, 0.0f, windowWidth, windowHeight);
//
//	// Create inverse projection-view matrix
//	glm::mat4 invPVMatrix = glm::inverse(aViewProjectionMatrix);
//
//	// Perform unprojection
//	glm::vec4 mouseCoords = glm::vec4(ndcX, ndcY, 0.0f, 1.0f);
//	glm::vec4 worldCoordsHomogeneous = invPVMatrix * mouseCoords;
//	worldCoordsHomogeneous /= worldCoordsHomogeneous.w; // Convert to Euclidean space
//
//	// Extract world coordinates
//	worldCoords = glm::vec3(worldCoordsHomogeneous);
//}