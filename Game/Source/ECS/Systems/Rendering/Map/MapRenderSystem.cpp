#include "Pch.h"
#include "MapRenderSystem.h"
#include "Entities/EntityManager.h"
#include "Components/Map/MapComponents.h"
#include "Components/Core/CoreComponents.h"


MapRenderSystem::MapRenderSystem()
{
}

MapRenderSystem::~MapRenderSystem()
{
}

void MapRenderSystem::Receive(Message& aMsg)
{
}

void MapRenderSystem::Draw()
{
	if (!m_entityManager)
		return;

	auto entities = m_entityManager->FindAll<MapChunkComponent>();

	// Todo; only render relevant map chunks (those in view)

	for (auto entity : entities)
	{
		auto* mapChunk		 = entity->GetComponent<MapChunkComponent>();
		auto currentPosition = entity->GetComponent<TransformComponent>()->CurrentPos;

		DrawMapChunk(mapChunk, currentPosition);
	}
}

void MapRenderSystem::DrawMapChunk(MapChunkComponent* aMapChunk, const CU::Vector3<float>& aPosition)
{
	static const float size = 1.f; // TODO; FIX!!

	//Hi_Engine::RenderEvent renderEvent;
	std::queue<Hi_Engine::RenderCommand> commandQueue;
	
	for (const auto& tile : aMapChunk->Tiles)
	{
		glm::vec3 position = { aPosition.x, aPosition.y, aPosition.z };
		position.x += tile.Coordinates.x * size;
		position.z += tile.Coordinates.y * size;
		
		Hi_Engine::RenderCommand command{};
		command.Type = Hi_Engine::eRenderCommandType::DrawSprite;

		glm::vec4 color = { tile.Color.x, tile.Color.y, tile.Color.z, tile.Color.w };
		command.SpriteRenderData = { tile.Subtexture, color, Hi_Engine::Transform{ position, {1.f, 1.f}, -90.f } };
		//command.m_spriteRenderData = { &tile.m_material, { position.x, position.y, position.z } , glm::vec3{1.f, 1.f, 1.f}, -90.f };

		//renderEvent.AddRenderCommand(command);

		commandQueue.push(command);


		// auto position = tile.m_position;
		//Hi_Engine::SpriteRenderer::GetInstance().Render({ &tile.m_material, { position.x, position.y, position.z } , glm::vec3{1.f, 1.f, 1.f}, -90.f});
 	}
	
	Hi_Engine::Dispatcher::GetInstance().SendEventInstantly<Hi_Engine::RenderEvent>(commandQueue); // Static call to Renderer instead??
}