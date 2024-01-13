#include "Pch.h"
#include "CameraSystem.h"
#include "Entities/EntityManager.h"
#include "Components/Core/CoreComponents.h"


CameraSystem::CameraSystem()
	: System{ 1 }
{
	PostMaster::GetInstance().Subscribe(eMessage::GameStarted, this);
}

CameraSystem::~CameraSystem()
{
	PostMaster::GetInstance().Unsubscribe(eMessage::GameStarted, this);
}

void CameraSystem::Receive(Message& aMsg)
{
	if (aMsg.GetMessageType() == eMessage::GameStarted)
	{
		auto* entity = m_entityManager->FindFirst<CameraComponent>();
		auto* camera = entity->GetComponent<CameraComponent>();

		auto range = camera->ZoomRange;
		camera->Camera.SetZoomRange(camera->ZoomRange);
	}
}

void CameraSystem::Update(float aDeltaTime)
{
	if (!m_entityManager)
		return;

	// Do every frame? or just at the beginning of new Scene?

	auto* camera = m_entityManager->FindFirst<CameraComponent>();

	if (!camera)
		return;

	// loop through all cameras... see if active..?

	auto* cameraComponent = camera->GetComponent<CameraComponent>();
	
	Hi_Engine::RenderCommand command{};
	command.Type = Hi_Engine::eRenderCommandType::SetCamera;
	command.Camera = &cameraComponent->Camera;

	std::queue<Hi_Engine::RenderCommand> commandQueue;
	commandQueue.push(command);

	Hi_Engine::Dispatcher::GetInstance().SendEventInstantly<Hi_Engine::RenderEvent>(commandQueue);

	if (auto* inputEntity = m_entityManager->FindFirst<InputComponent>())
		cameraComponent->Camera.AdjustZoom(inputEntity->GetComponent<InputComponent>()->MouseScroll); // 0.5f == zoom distance


	auto* target = m_entityManager->Find(cameraComponent->TargetID);
	//auto target = cameraComponent->m_target;
	if (target)
	{
		auto targetPosition = target->GetComponent<TransformComponent>()->CurrentPos;
		//auto newPosition = targetPosition + cameraComponent->TargetOffset;
		CU::Vector3<float> newPosition = { targetPosition.x + cameraComponent->TargetOffset.x, targetPosition.y + cameraComponent->TargetOffset.y, cameraComponent->TargetOffset.z };

		cameraComponent->Camera.SetPosition(newPosition);
		camera->GetComponent<TransformComponent>()->CurrentPos = { newPosition.x, newPosition.y };
	}
}