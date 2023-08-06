#include "Pch.h"
#include "CameraSystem.h"
#include "EntityManager.h"
#include "Rendering/RenderComponents.h"
#include "Core/CoreComponents.h"


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

	auto camera = m_entityManager->FindAllWithComponents<CameraComponent>()[0]; // Get first

	if (!camera)
		return;

	auto cameraComponent = camera->GetComponent<CameraComponent>();
	
	Hi_Engine::SpriteRenderer::GetInstance().SetCamera(&cameraComponent->m_camera);
	Hi_Engine::PrimitiveRenderer::GetInstance().SetCamera(&cameraComponent->m_camera);

	auto target = m_entityManager->Find(cameraComponent->m_targetID);
	//auto target = cameraComponent->m_target;
	if (target)
	{
		auto targetPosition = target->GetComponent<TransformComponent>()->m_currentPos;
		auto newPosition = targetPosition + cameraComponent->m_targetOffset;

		cameraComponent->m_camera.SetPosition(newPosition);
		camera->GetComponent<TransformComponent>()->m_currentPos = newPosition;
	}
}