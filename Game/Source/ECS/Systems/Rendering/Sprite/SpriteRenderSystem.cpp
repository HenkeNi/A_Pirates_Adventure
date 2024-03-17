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

void SpriteRenderSystem::Receive(Message& message)
{
}

void SpriteRenderSystem::Draw() // TODO; should pass along if bash should be flushed in render command?
{
	if (!m_entityManager)
		return;

	std::queue<Hi_Engine::RenderCommand> commandQueue;

	auto entities = m_entityManager->FindAll<SpriteComponent, TransformComponent>();
	auto* camera = m_entityManager->FindFirst<CameraComponent>();
	Hi_Engine::RenderCommand projectionCommand{};
	projectionCommand.Type = Hi_Engine::eRenderCommandType::SetProjectionMatrix;
	projectionCommand.ProjectionMatrix = camera->GetComponent<CameraComponent>()->Camera.GetViewProjectionMatrix();

	commandQueue.push(projectionCommand);

	std::sort(entities.begin(), entities.end(), [](const Entity* e1, const Entity* e2) {

		auto transform1 = e1->GetComponent<TransformComponent>();
		auto sprite1 = e1->GetComponent<SpriteComponent>();

		auto transform2 = e2->GetComponent<TransformComponent>();
		auto sprite2 = e2->GetComponent<SpriteComponent>();

		// auto pos1 = transform1->CurrentPos.y -

		//float yPos = transform1->CurrentPos.y;
		//float textureSize = sprite1->Subtexture->GetSize().y;
		//float pivot = sprite1->Pivot.y;
		//yPos += sprite1->Subtexture->GetSize().y * sprite1->Pivot.y;


		//return (transform1->CurrentPos.y + (sprite1->Subtexture->GetSize().y * (1.0f - sprite1->Pivot.y))) < (transform2->CurrentPos.y + (sprite2->Subtexture->GetSize().y * sprite2->Pivot.y));

		//return (transform1->CurrentPos.y - sprite1->Subtexture->GetSize().y) < (transform2->CurrentPos.y - sprite2->Subtexture->GetSize().y);
		//return (transform1->CurrentPos.y - (sprite1->Subtexture->GetSize().y * sprite1->Pivot.y)) < (transform2->CurrentPos.y - (sprite2->Subtexture->GetSize().y * sprite2->Pivot.y));

		// TODO: FIX Scale....

		return e1->GetComponent<TransformComponent>()->CurrentPos.y < e2->GetComponent<TransformComponent>()->CurrentPos.y;
		});


	for (const Entity* entity : entities)
	{
		if (entity->HasComponent<HUDComponent>() || entity->HasComponent<UIComponent>()) // TODO: Fix by having better filtering... (look into bitset)
			continue;

		//auto& material = entity->GetComponent<SpriteComponent>()->m_material;

		auto* spriteComponent = entity->GetComponent<SpriteComponent>();

		if (!spriteComponent->ShouldRender)
		{
			//std::cout << "Not rendering sprite!\n";
			continue;
		}

		const auto& subtexture = spriteComponent->Subtexture;

		const auto* transform = entity->GetComponent<TransformComponent>();
		const auto& position = transform->CurrentPos;
		const auto& scale = transform->Scale;
		const auto& rotation = transform->Rotation;

		glm::vec3 renderPosition;
		renderPosition.x = transform->CurrentPos.x + (transform->Pivot.x * transform->Scale.x);
		renderPosition.y = transform->CurrentPos.y + (transform->Pivot.y * transform->Scale.y);

		Hi_Engine::RenderCommand command{};
		command.Type = Hi_Engine::eRenderCommandType::DrawSprite;
		command.SpriteRenderData = { subtexture, { 1.f, 1.f, 1.f, 1.f }, Hi_Engine::Transform{{ renderPosition.x, renderPosition.y, 0.f }, { scale.x, scale.y }, rotation } }; // CHANGE TO Transform
		//command.SpriteRenderData = { subtexture, { 1.f, 1.f, 1.f, 1.f }, Hi_Engine::Transform{{ position.x, position.y, 0.f }, { scale.x, scale.y }, rotation } }; // CHANGE TO Transform

		commandQueue.push(command);
		// Hi_Engine::SpriteRenderer::GetInstance().Render(Hi_Engine::SpriteRenderData{ &material, { position.x, position.y, position.z }, { scale.x, scale.y }, rotation });
	}

	Hi_Engine::Dispatcher::GetInstance().SendEventInstantly<Hi_Engine::RenderEvent>(commandQueue);
}