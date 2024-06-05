#include "Pch.h"
#include "MapRenderSystem.h"
#include "Entities/EntityManager.h"
#include "Components/Map/MapComponents.h"
#include "Components/Core/CoreComponents.h"
#include "Systems/Rendering/Camera/CameraSystem.h"
#include "Systems/Time/TimeSystem.h"
#include "DataTypes/Enumerations.h"


MapRenderSystem::MapRenderSystem()
{
}

MapRenderSystem::~MapRenderSystem()
{
}

void MapRenderSystem::Receive(Message& message)
{
}

void MapRenderSystem::Draw()
{
	if (!m_entityManager)
		return;

	auto* camera = m_entityManager->FindFirst<CameraComponent>();

	if (!camera)
		return;

	auto entities = m_entityManager->FindAll<MapChunkComponent>();

	if (entities.empty())
		return;

	auto* cameraComponent = camera->GetComponent<CameraComponent>();

	if (!cameraComponent)
		return;


	// Todo; only render relevant map chunks (those in view) -> camera systems job?!

	std::vector<Hi_Engine::Sprite> sprites;

	for (auto entity : entities)
	{
		auto* transformComponent = entity->GetComponent<TransformComponent>();
		auto* mapChunkComponent = entity->GetComponent<MapChunkComponent>();

		if (!transformComponent || !mapChunkComponent)
			continue;

		const auto& currentPosition = transformComponent->CurrentPos;
	
		// TODO:: pass in bounds (componetn)?

		Hi_Engine::Physics::AABB2D<float> bounds;
		bounds.Init({ currentPosition.x, currentPosition.y }, { currentPosition.x + (10 * Tile::Size), currentPosition.y + (10 * Tile::Size) });
		//bounds.Init({ currentPosition.x, currentPosition.y }, { currentPosition.x + (mapChunk->Width * Tile::Size), currentPosition.y + (mapChunk->Height * Tile::Size) });

		if (!CameraSystem::IsInView(camera, bounds))
			continue;

		auto color = TimeSystem::CalculateDaylightColor(m_entityManager->FindFirst<WorldTimeComponent>());

		std::copy(mapChunkComponent->Sprites.begin(), mapChunkComponent->Sprites.end(), std::back_inserter(sprites));
	}

	auto viewProjectionMatrix = cameraComponent->Camera.GetViewProjectionMatrix();

	Hi_Engine::Dispatcher::GetInstance().SendEventInstantly<Hi_Engine::SpriteBatchRequest>(Hi_Engine::SpriteBatch{ sprites, viewProjectionMatrix }); // Static call to Renderer instead??
}

FVector4 MapRenderSystem::CalculateDaylightColor() const
{
	static std::unordered_map<eTimeOfDay, FVector4> daylights;
	daylights.insert(std::make_pair(eTimeOfDay::Dawn, FVector4{ 0.9804f,	0.7725f,	0.5529f,	1.f }));
	daylights.insert(std::make_pair(eTimeOfDay::Day, FVector4{ 1.f,	1.f,	1.f,	1.f }));
	//daylights.insert(std::make_pair(eTimeOfDay::Day, FVector4{ 0.9569f,	0.8471f,	0.6706f,	1.f }));
	daylights.insert(std::make_pair(eTimeOfDay::Dusk, FVector4{ 0.89f,		0.68f,		0.42f,		1.f }));
	daylights.insert(std::make_pair(eTimeOfDay::Night, FVector4{ 0.1f,	0.1f,		0.1f,		1.f }));
	
	
	FVector4 color{};

	if (auto* worldTime = m_entityManager->FindFirst<WorldTimeComponent>())
	{
		auto* worldTimeComponent = worldTime->GetComponent<WorldTimeComponent>();
		float progress = worldTimeComponent->CurrentDayProgress;
		
		//color = Hi_Engine::Lerp(daylights.at(eTimeOfDay::Day), daylights.at(eTimeOfDay::Night), progress);
		color = { 1.f,  1.f ,  1.f ,  1.f };

		//if (progress < 0.25f)
		//{
		//}
		//else if (progress < 0.5f)
		//{
		//	color = { 0.9569f, 0.8471f, 0.6706f, 1.f };
		//}
		//else if (progress < 0.75f)
		//{
		//	color = { 0.89f, 0.68f, 0.42f, 1.f };
		//}
		//else
		//{
		//	color = { 0.302f, 0.302f, 0.302f, 1.f };
		//}
	}

	return color;
}

//void MapRenderSystem::PerformFustrumCulling(std::vector<Entity*>& someEntities)
//std::vector<Entity*> MapRenderSystem::PerformFrustumCulling(std::vector<Entity*>& someEntities)
//{
//	// get camera position...
//	return {};
//}