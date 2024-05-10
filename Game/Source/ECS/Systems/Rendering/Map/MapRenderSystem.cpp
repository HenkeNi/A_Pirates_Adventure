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

	std::queue<Hi_Engine::RenderCommand> renderCommands; // commandQueue

	auto* camera = m_entityManager->FindFirst<CameraComponent>();
	Hi_Engine::RenderCommand projectionCommand{};
	projectionCommand.Type = Hi_Engine::eRenderCommandType::SetProjectionMatrix;
	projectionCommand.ProjectionMatrix = camera->GetComponent<CameraComponent>()->Camera.GetViewProjectionMatrix();

	renderCommands.push(projectionCommand);

	
	// Todo; only render relevant map chunks (those in view) -> camera systems job?!

	auto entities = m_entityManager->FindAll<MapChunkComponent>();

	//auto culledEntities = PerformFustrumCulling(entities);

	// TEMP`?

	for (auto entity : entities)
	{
		auto currentPosition = entity->GetComponent<TransformComponent>()->CurrentPos;
		auto* mapChunkComponent = entity->GetComponent<MapChunkComponent>();


		// TODO:: pass in bounds (componetn)?

		Hi_Engine::Physics::AABB2D<float> bounds;
		bounds.Init({ currentPosition.x, currentPosition.y }, { currentPosition.x + (10 * Tile::Size), currentPosition.y + (10 * Tile::Size) });
		//bounds.Init({ currentPosition.x, currentPosition.y }, { currentPosition.x + (mapChunk->Width * Tile::Size), currentPosition.y + (mapChunk->Height * Tile::Size) });

		if (!CameraSystem::IsInView(camera, bounds))
			continue;


		auto color = TimeSystem::CalculateDaylightColor(m_entityManager->FindFirst<WorldTimeComponent>());
		//auto color = CalculateDaylightColor();

		// DrawMapChunk(mapChunk, currentPosition);

		//for (const auto& renderData : mapChunk->RenderData)
		for (const auto renderData : mapChunkComponent->RenderData)
		{
			Hi_Engine::RenderCommand command{};
			command.Type = Hi_Engine::eRenderCommandType::DrawSprite;

			command.SpriteRenderData = renderData;

			command.SpriteRenderData.Color = renderData.Color * glm::vec4{ color.x, color.y, color.z, color.w }; // += glm::vec4{ 0.08f, 0.1f, 0.27f, 1.f };
			renderCommands.push(command);
		}

		//for (const auto& tile : mapChunk->Tiles)
		//{
		//	glm::vec3 position = { currentPosition.x, currentPosition.y, 0.f };
		//	position.x += tile.Coordinates.x * Tile::Size;
		//	position.y += tile.Coordinates.y * Tile::Size;
		//	//position.z += tile.Coordinates.y * size;

		//	Hi_Engine::RenderCommand command{};
		//	command.Type = Hi_Engine::eRenderCommandType::DrawSprite;

		//	glm::vec4 color = { tile.Color.x, tile.Color.y, tile.Color.z, tile.Color.w };
		//	command.SpriteRenderData = { tile.Subtexture, color, Hi_Engine::Transform{ position, { 1.f, 1.f }, 0.f } }; // Store sprite render data in MapChunk?

		//	// command.SpriteRenderData = { tile.Subtexture, color, Hi_Engine::Transform{ position, { 1.f, 1.f }, -90.f } };
		//	//command.m_spriteRenderData = { &tile.m_material, { position.x, position.y, position.z } , glm::vec3{1.f, 1.f, 1.f}, -90.f };

		//	//renderEvent.AddRenderCommand(command);

		//	renderCommands.push(command);
		//}

	}

	Hi_Engine::Dispatcher::GetInstance().SendEventInstantly<Hi_Engine::RenderEvent>(renderCommands); // Static call to Renderer instead??
}

//void MapRenderSystem::DrawMapChunk(MapChunkComponent* mapChunk, const FVector2& position)
//{
//	// static const float size = 1.f; // TODO; FIX!!
//
//	//Hi_Engine::RenderEvent renderEvent;
//	std::queue<Hi_Engine::RenderCommand> commandQueue;
//
//	auto camera = m_entityManager->FindFirst<CameraComponent>();
//	Hi_Engine::RenderCommand projectionCommand{};
//	projectionCommand.Type = Hi_Engine::eRenderCommandType::SetProjectionMatrix;
//	projectionCommand.ProjectionMatrix = camera->GetComponent<CameraComponent>()->Camera.GetProjectionMatrix(); // TODO; Check if already is active?
//	commandQueue.push(projectionCommand);
//
//
//
//	for (const auto& tile : mapChunk->Tiles)
//	{
//		glm::vec3 tilePosition = { position.x, position.y, 0.f };
//		tilePosition.x += tile.Coordinates.x * Tile::Size;
//		tilePosition.y += tile.Coordinates.y * Tile::Size;
//		//position.z += tile.Coordinates.y * size;
//		
//		Hi_Engine::RenderCommand command{};
//		command.Type = Hi_Engine::eRenderCommandType::DrawSprite;
//
//		glm::vec4 color = { tile.Color.x, tile.Color.y, tile.Color.z, tile.Color.w };
//		command.SpriteRenderData = { tile.Subtexture, color, Hi_Engine::Transform{ tilePosition, { 1.f, 1.f }, 0.f } };
//	
//		// command.SpriteRenderData = { tile.Subtexture, color, Hi_Engine::Transform{ position, { 1.f, 1.f }, -90.f } };
//		//command.m_spriteRenderData = { &tile.m_material, { position.x, position.y, position.z } , glm::vec3{1.f, 1.f, 1.f}, -90.f };
//
//		//renderEvent.AddRenderCommand(command);
//
//		commandQueue.push(command);
//
//
//		// auto position = tile.m_position;
//		//Hi_Engine::SpriteRenderer::GetInstance().Render({ &tile.m_material, { position.x, position.y, position.z } , glm::vec3{1.f, 1.f, 1.f}, -90.f});
// 	}
//	
//	Hi_Engine::Dispatcher::GetInstance().SendEventInstantly<Hi_Engine::RenderEvent>(commandQueue); // Static call to Renderer instead??
//}

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
		
		color = Hi_Engine::Lerp(daylights.at(eTimeOfDay::Day), daylights.at(eTimeOfDay::Night), progress);

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