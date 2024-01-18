#include "Pch.h"
#include "HUDRenderSystem.h"
#include "Entities/EntityManager.h"
#include "Components/UI/UIComponents.h"


HUDRenderSystem::HUDRenderSystem()
{
}

HUDRenderSystem::~HUDRenderSystem()
{
}

void HUDRenderSystem::Receive(Message& aMsg)
{
}

void HUDRenderSystem::Draw()				
{
	if (!m_entityManager)
		return;

	auto* camera = m_entityManager->FindFirst<CameraComponent>();

	if (!camera)
		return;
	
	auto entities = m_entityManager->FindAll<HUDComponent>();

	if (entities.empty())
		return;

	// TODO; use a simpler Shader for HUD?

	std::queue<Hi_Engine::RenderCommand> renderCommands;

	// Add projection command
	Hi_Engine::RenderCommand projectionCommand{};
	projectionCommand.Type = Hi_Engine::eRenderCommandType::SetProjectionMatrix;
	projectionCommand.ProjectionMatrix = camera->GetComponent<CameraComponent>()->Camera.GetProjectionMatrix();
	renderCommands.push(projectionCommand);

	for (auto* entity : entities)
	{
		const auto* sprite = entity->GetComponent<SpriteComponent>();
		const auto* transform = entity->GetComponent<TransformComponent>();

		const auto& position = transform->CurrentPos;
		const auto& scale	 = transform->Scale;
		const auto& rotation = transform->Rotation;

		Hi_Engine::RenderCommand command{};
		command.Type = Hi_Engine::eRenderCommandType::DrawSprite;
		command.SpriteRenderData = { sprite->Subtexture, { 1.f, 1.f, 1.f, 1.f }, Hi_Engine::Transform{{ position.x, position.y, 0.f }, { scale.x, scale.y }, rotation } }; // CHANGE TO Transform

		renderCommands.push(command);
	}
	Hi_Engine::Dispatcher::GetInstance().SendEventInstantly<Hi_Engine::RenderEvent>(renderCommands);
}