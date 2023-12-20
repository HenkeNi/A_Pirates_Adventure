#include "Pch.h"
#include "SpriteRenderSystem.h"
#include "Entities/EntityManager.h"
#include "Components/Core/CoreComponents.h"

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

	auto entities = m_entityManager->FindAll<SpriteComponent, TransformComponent>();

	for (const Entity* entity : entities)
	{
		//auto& material = entity->GetComponent<SpriteComponent>()->m_material;
		const auto& subtexture = entity->GetComponent<SpriteComponent>()->Subtexture;

		const auto* transform	 = entity->GetComponent<TransformComponent>();
		const auto& position	 = transform->CurrentPos;
		const auto& scale		 = transform->Scale;
		const auto& rotation	 = transform->Rotation;

		Hi_Engine::RenderCommand command{};
		command.Type = Hi_Engine::eRenderCommandType::DrawSprite;
		command.SpriteRenderData = { subtexture, { 1.f, 1.f, 1.f, 1.f }, Hi_Engine::Transform{{ position.x, position.y, position.z }, { scale.x, scale.y }, rotation } }; // CHANGE TO Transform
	
		commandQueue.push(command);
		// Hi_Engine::SpriteRenderer::GetInstance().Render(Hi_Engine::SpriteRenderData{ &material, { position.x, position.y, position.z }, { scale.x, scale.y }, rotation });
	}

	Hi_Engine::Dispatcher::GetInstance().SendEventInstantly<Hi_Engine::RenderEvent>(commandQueue);
}