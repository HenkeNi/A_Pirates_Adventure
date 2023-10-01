#include "Pch.h"
#include "SpriteRenderSystem.h"
#include "EntityManager.h"
#include "Rendering/RenderComponents.h"
#include "Core/CoreComponents.h"

namespace CU = CommonUtilities;


SpriteRenderSystem::SpriteRenderSystem()
	: System{ 0 }
{
}

SpriteRenderSystem::~SpriteRenderSystem()
{
}

void SpriteRenderSystem::Receive(Message& aMsg)
{
}

void SpriteRenderSystem::Draw()
{
	if (!m_entityManager)
		return;

	std::queue<Hi_Engine::RenderCommand> commandQueue;

	auto entities = m_entityManager->FindAllWithComponents<SpriteComponent, TransformComponent>();

	for (const Entity* entity : entities)
	{
		//auto& material = entity->GetComponent<SpriteComponent>()->m_material;
		const auto& subtexture = entity->GetComponent<SpriteComponent>()->m_subtexture;

		const auto* transform	 = entity->GetComponent<TransformComponent>();
		const auto& position	 = transform->m_currentPos;
		const auto& scale		 = transform->m_scale;
		const auto& rotation	 = transform->m_rotation;

		Hi_Engine::RenderCommand command;
		command.m_type = Hi_Engine::eRenderCommandType::DrawSprite;
		command.m_spriteRenderData = { subtexture, { 1.f, 1.f, 1.f, 1.f }, { position.x, position.y, position.z }, { scale.x, scale.y }, rotation };
	
		commandQueue.push(command);
		// Hi_Engine::SpriteRenderer::GetInstance().Render(Hi_Engine::SpriteRenderData{ &material, { position.x, position.y, position.z }, { scale.x, scale.y }, rotation });
	}

	Hi_Engine::Dispatcher::GetInstance().SendEventInstantly<Hi_Engine::RenderEvent>(commandQueue);
}