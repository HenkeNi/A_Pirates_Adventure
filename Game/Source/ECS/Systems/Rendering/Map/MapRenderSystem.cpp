#include "Pch.h"
#include "MapRenderSystem.h"
#include "Components/Map/MapComponents.h"
#include "Components/Core/CoreComponents.h"
#include "Components/Utility/UtilityComponents.h"
#include "Systems/Rendering/Camera/CameraSystem.h"
#include "Systems/Time/TimeSystem.h"
#include "DataTypes/Enumerations.h"
#include "ECS/ECS.h"

MapRenderSystem::MapRenderSystem()
{
}

MapRenderSystem::~MapRenderSystem()
{
}

void MapRenderSystem::Draw()
{
	assert(m_ecs && "ERROR: EntityManager is nullptr!");

	auto camera = m_ecs->FindEntity(m_signatures["Camera"]);
	if (!camera.has_value())
		return;

	auto entities = m_ecs->FindEntities(m_signatures["MapChunks"]);
	if (entities.empty())
		return;

	auto* cameraComponent = m_ecs->GetComponent<CameraComponent>(camera.value());
	if (!cameraComponent)
		return;

	// Todo; only render relevant map chunks (those in view) -> camera systems job?!

	Hi_Engine::SpriteBatch spriteBatch;
	spriteBatch.Sprites.reserve(entities.size());

	for (Entity entity : entities)
	{
		auto* mapChunkComponent = m_ecs->GetComponent<MapChunkComponent>(entity);
		if (!mapChunkComponent)
			continue;

		// TODO; have Camera system set this in some component!!!
		//if (!CameraSystem::IsInView(camera, mapChunkComponent->Bounds))
		//	continue;

		//auto color = TimeSystem::CalculateDaylightColor(m_entityManager->FindFirst<WorldTimeComponent>());
		
		std::copy(mapChunkComponent->Sprites.begin(), mapChunkComponent->Sprites.end(), std::back_inserter(spriteBatch.Sprites));
	}

	spriteBatch.ProjectionMatrix = cameraComponent->Camera.GetViewProjectionMatrix();
	Hi_Engine::Dispatcher::GetInstance().SendEventInstantly<Hi_Engine::SpriteBatchRequest>(spriteBatch); // Static call to Renderer instead??
}

void MapRenderSystem::SetSignature()
{
	m_signatures.insert({ "Camera", m_ecs->GetSignature<CameraComponent>() });
	m_signatures.insert({ "MapChunks", m_ecs->GetSignature<MapChunkComponent>() });
	m_signatures.insert({ "WorldTime", m_ecs->GetSignature<WorldTimeComponent>() });
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

	auto worldTime = m_ecs->FindEntity(m_signatures.at("WorldTime"));

	if (worldTime.has_value())
	{
		const auto* worldTimeComponent = m_ecs->GetComponent<WorldTimeComponent>(worldTime.value());
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