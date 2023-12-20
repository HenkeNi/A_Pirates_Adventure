#include "Pch.h"
#include "CameraSystem.h"
#include "Entities/EntityManager.h"
#include "Components/Core/CoreComponents.h"


CameraSystem::CameraSystem()
	: System{ 1 }
{
}

CameraSystem::~CameraSystem()
{
}

void CameraSystem::Receive(Message& aMsg)
{
}

void CameraSystem::Update(float aDeltaTime)
{
	if (!m_entityManager)
		return;

	// Do every frame? or just at the beginning of new Scene?

	auto* camera = m_entityManager->FindFirst<CameraComponent>(); // Get first
	//auto camera = m_entityManager->FindAll<CameraComponent>()[0]; // Get first

	if (!camera)
		return;

	// loop through all cameras... see if active..?

	auto cameraComponent = camera->GetComponent<CameraComponent>();
	
	Hi_Engine::RenderCommand command{};
	command.Type = Hi_Engine::eRenderCommandType::SetCamera;
	command.Camera = &cameraComponent->Camera;

	std::queue<Hi_Engine::RenderCommand> commandQueue;
	commandQueue.push(command);

	Hi_Engine::Dispatcher::GetInstance().SendEventInstantly<Hi_Engine::RenderEvent>(commandQueue);


	auto target = m_entityManager->Find(cameraComponent->TargetID);
	//auto target = cameraComponent->m_target;
	if (target)
	{
		auto targetPosition = target->GetComponent<TransformComponent>()->CurrentPos;
		auto newPosition = targetPosition + cameraComponent->TargetOffset;

		cameraComponent->Camera.SetPosition(newPosition);
		camera->GetComponent<TransformComponent>()->CurrentPos = newPosition;
	}
}