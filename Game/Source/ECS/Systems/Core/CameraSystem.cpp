#include "Pch.h"
#include "CameraSystem.h"
#include "Components/Core/CoreComponents.h"
#include "ECSTypes.h"
#include "ECS.h"


CameraSystem::CameraSystem()
	: System{ 1 }
{
	PostMaster::GetInstance().Subscribe(eMessage::GameStarted, this);
}

CameraSystem::~CameraSystem()
{
	PostMaster::GetInstance().Unsubscribe(eMessage::GameStarted, this);
}

void CameraSystem::Receive(Message& message)
{
	assert(m_ecs && "[CameraSystem - ERROR]: ECS is not initialized!");

	if (message.GetMessageType() == eMessage::GameStarted)
	{
		auto camera = m_ecs->FindEntity(m_signatures["Camera"]);
		if (!camera.has_value())
			return;

		auto* cameraComponent = m_ecs->GetComponent<CameraComponent>(camera.value());
		if (!cameraComponent)
			return;

		// do in initalizsr??
		auto zoomRange = cameraComponent->ZoomRange;
		cameraComponent->Camera.SetZoomRange(zoomRange);
		
		auto player = m_ecs->FindEntity(m_signatures.at("Player")); // get blackboard component every frame instead??
		if (player.has_value())
		{
			cameraComponent->Target = player.value();

			auto* playerTransformComponent = m_ecs->GetComponent<TransformComponent>(player.value());
			auto* cameraTransformComponent = m_ecs->GetComponent<TransformComponent>(camera.value());

			cameraTransformComponent->CurrentPos = playerTransformComponent->CurrentPos;
	
			auto windowSize = Hi_Engine::ServiceLocator::GetWindow().lock()->GetSize();
			cameraComponent->TargetOffset = { -windowSize.x * 0.5f, -windowSize.y * 0.5f };
		}
	}
}

void CameraSystem::Update(float deltaTime)
{
	assert(m_ecs && "[CameraSystem - ERROR]: ECS is not initialized!");

	auto entity = m_ecs->FindEntity(m_signatures["Camera"]);
	if (!entity.has_value())
		return;

	Entity camera = entity.value();

	auto* cameraComponent = m_ecs->GetComponent<CameraComponent>(camera);
	if (!cameraComponent)
		return;

	auto* transformComponent = m_ecs->GetComponent<TransformComponent>(camera);
	if (!transformComponent)
		return;

	// loop through all cameras... see if active..?


	// GO OVER ALL ENTIITES WITH SPRITE COMPONENT => Check if in view => set ShouldRender


	// TODO; cull entities (mark is should be rendered or not))?
	if (cameraComponent->ShouldCull)
	{
		const auto& bounds = cameraComponent->Frustum;

		CullEntities(bounds);
		CullMapChunks(bounds);
	}


	
	// THIS IS DONE BY the rendering systems....
	//Hi_Engine::RenderCommand command{};
	//command.Type = Hi_Engine::eRenderCommandType::SetCamera;
	//command.Camera = &cameraComponent->Camera;

	//std::queue<Hi_Engine::RenderCommand> commandQueue;
	// commandQueue.push(command);

	//Hi_Engine::EventDispatcher::GetInstance().SendEventInstantly<Hi_Engine::RenderEvent>(commandQueue);



	//if (auto* inputEntity = m_entityManager->FindFirst<InputComponent>())
	//	cameraComponent->Camera.AdjustZoom(inputEntity->GetComponent<InputComponent>()->MouseScroll * 0.1f); // 0.5f == zoom distance




	// Do in movement system? Follow component
	auto target = cameraComponent->Target;
	if (target)
	{
		auto targetPosition = m_ecs->GetComponent<TransformComponent>(target)->CurrentPos;
		
		static const float windowWidth = 1400.f;
		static const float windowHeight = 800.f;
	//	targetPosition.x -= windowWidth * 0.5f;
	//	targetPosition.y -= windowHeight * 0.5f;
		// targetPosition.x -= 20.f;
		//auto newPosition = targetPosition + cameraComponent->TargetOffset;
		FVector2 newPosition = { targetPosition.x + cameraComponent->TargetOffset.x, targetPosition.y + cameraComponent->TargetOffset.y };

		cameraComponent->Camera.SetPosition(newPosition);
		transformComponent->CurrentPos = { newPosition.x, newPosition.y };
	}



	// Update frustum 	
	auto window = Hi_Engine::ServiceLocator::GetWindow();
	if (auto win = window.lock())
	{
		const auto& winSize = win->GetSize();

		const auto& currentPos = transformComponent->CurrentPos;

		float minX = currentPos.x;
		float minY = currentPos.y;

		float maxX = minX + winSize.x;
		float maxY = minY + winSize.y;
		
		cameraComponent->Frustum.Init({ minX,  minY }, { maxX, maxY });
	}
}

//bool CameraSystem::IsInView(Entity* camera, const Hi_Engine::Physics::AABB2D<float>& bounds)
//{
//	auto* cameraComponent = camera->GetComponent<CameraComponent>();
//
//	bool intersects = Hi_Engine::Physics::Intersects(bounds, cameraComponent->Frustum);
//	return intersects;
//}

void CameraSystem::SetSignature()
{
	assert(m_ecs && "[CameraSystem - ERROR]: ECS is nullptr!");

	m_signatures.insert({ "Camera", m_ecs->GetSignature<CameraComponent>() });
	m_signatures.insert({ "Player", m_ecs->GetSignature<PlayerControllerComponent>() }); // camera controller component instead??? or something.. not all scens camrea should follow 

	m_signatures.insert({ "Sprites", m_ecs->GetSignature<SpriteComponent, TransformComponent>() }); // make sure only in world entities
	m_signatures.insert({ "MapChunks", m_ecs->GetSignature<MapChunkComponent, TransformComponent>() });
	//// do in ECS???
	//auto componentTypes = m_ecs->GetComponentTypes<CameraComponent, TransformComponent>();

	//Signature signature;
	//for (const auto type : componentTypes)
	//{
	//	signature.set(type);
	//}

	//m_signatures.insert({ "Camera", signature });


	//AddSignature<CameraComponent>("Camera");

	//Signature camera;

	//auto cameraType = m_ecs->GetComponentType<CameraComponent>();
	//camera.set(cameraType);

}


void CameraSystem::CullEntities(const CameraBounds& bounds)
{
	auto sprites = m_ecs->FindEntities(m_signatures["Sprites"]);

	for (Entity sprite : sprites)
	{
		auto* transformComponent = m_ecs->GetComponent<TransformComponent>(sprite);
		auto* spriteComponent = m_ecs->GetComponent<SpriteComponent>(sprite);

		// temp
		if (m_ecs->HasComponent<HUDComponent>(sprite) || m_ecs->HasComponent<UIComponent>(sprite))
			continue;

		if (transformComponent && spriteComponent)
		{
			const auto& position = transformComponent->CurrentPos;
			//const auto& size = transformComponent->

			bool isVisible = bounds.IsInside(position); // todo; do for all 4 corners?
			spriteComponent->IsVisible = isVisible;
		}
	}
}

void CameraSystem::CullMapChunks(const CameraBounds& bounds)
{
	auto mapChunks = m_ecs->FindEntities(m_signatures["MapChunks"]);
	
	for (Entity mapChunk : mapChunks)
	{
		auto* transformComponent = m_ecs->GetComponent<TransformComponent>(mapChunk);
		auto* mapChunkComponent = m_ecs->GetComponent<MapChunkComponent>(mapChunk);

		if (transformComponent && mapChunkComponent)
		{
			bool isVisible = Hi_Engine::Intersection::Intersects(mapChunkComponent->Bounds, bounds);
			mapChunkComponent->IsVisible = isVisible;
		}
	}
}