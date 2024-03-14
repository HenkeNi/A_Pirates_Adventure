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

	auto* transformComponent = camera->GetComponent<TransformComponent>();
	auto* cameraComponent = camera->GetComponent<CameraComponent>();
	

	// TODO; cull entities (mark is should be rendered or not))?

	// GO OVER ALL ENTIITES WITH SPRITE COMPONENT => Check if in view => set ShouldRender


	if (cameraComponent->ShouldCull)
	{
		CullEntities();
	}


	
	// THIS IS DONE BY the rendering systems....
	//Hi_Engine::RenderCommand command{};
	//command.Type = Hi_Engine::eRenderCommandType::SetCamera;
	//command.Camera = &cameraComponent->Camera;

	std::queue<Hi_Engine::RenderCommand> commandQueue;
	// commandQueue.push(command);

	Hi_Engine::Dispatcher::GetInstance().SendEventInstantly<Hi_Engine::RenderEvent>(commandQueue);

	if (auto* inputEntity = m_entityManager->FindFirst<InputComponent>())
		cameraComponent->Camera.AdjustZoom(inputEntity->GetComponent<InputComponent>()->MouseScroll * 0.1f); // 0.5f == zoom distance

	// Do in movement system? Follow component
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



	// TODO: update frustum 
	float halfWidth = 3.f; // 1400.f * 0.5f;
	float halfHeight = 2.f; //  800.f * 0.5f;

	float minX = transformComponent->CurrentPos.x - halfWidth;
	float maxX = transformComponent->CurrentPos.x + halfWidth;
	
	float minY = transformComponent->CurrentPos.y - halfHeight;
	float maxY = transformComponent->CurrentPos.y + halfHeight;

	cameraComponent->Frustum.Init({ minX,  minY }, { maxX, maxY });
}

bool CameraSystem::IsInView(Entity* aCamera, const Hi_Engine::Physics::AABB2D<float>& someBounds)
{
	auto* cameraComponent = aCamera->GetComponent<CameraComponent>();

	return Hi_Engine::Physics::Intersects(someBounds, cameraComponent->Frustum);
}

void CameraSystem::CullEntities()
{
	auto* camera = m_entityManager->FindFirst<CameraComponent>();
	auto entities = m_entityManager->FindAll<SpriteComponent>();

	for (auto* entity : entities)
	{
		// If in view (function)
		auto* transformComponent = entity->GetComponent<TransformComponent>();
		auto currentPosition = transformComponent->CurrentPos;

		auto* spriteComponent = entity->GetComponent<SpriteComponent>();
		spriteComponent->ShouldRender = camera->GetComponent<CameraComponent>()->Frustum.IsInside(currentPosition);
	}
}

bool CameraSystem::IsVisible(Entity* anEntity) const
{
	// Check if bounding volume is inside fustrum...


	return false;
}