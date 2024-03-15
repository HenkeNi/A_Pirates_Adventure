#include "Pch.h"
#include "UIRenderSystem.h"
#include "Entities/EntityManager.h"
#include "Components/UI/UIComponents.h"
#include "../../../../../../ThirdParty/glm/ext/matrix_clip_space.hpp"


UIRenderSystem::UIRenderSystem()
{
}

UIRenderSystem::~UIRenderSystem()
{
}

void UIRenderSystem::Receive(Message& aMsg)
{
}

void UIRenderSystem::Draw()
{
	if (!m_entityManager)
		return;

	// TODO; Don't have HUDComponent?? Just UIComponent?
	RenderHUD();
	RenderUI();
	RenderInventory();
}

void UIRenderSystem::RenderHUD()
{
	auto* camera = m_entityManager->FindFirst<CameraComponent>();

	if (!camera)
		return;

	auto entities = m_entityManager->FindAll<HUDComponent>();

	if (entities.empty())
		return;

	// TODO; use a simpler Shader for HUD?

	std::queue<Hi_Engine::RenderCommand> renderCommands;

	// Add projection command (NOT NEEDED?? Use old projection matrix
	Hi_Engine::RenderCommand projectionCommand{};
	projectionCommand.Type = Hi_Engine::eRenderCommandType::SetProjectionMatrix;
	projectionCommand.ProjectionMatrix = camera->GetComponent<CameraComponent>()->Camera.GetProjectionMatrix();
	// projectionCommand.ProjectionMatrix =
	renderCommands.push(projectionCommand);

	for (auto* entity : entities)
	{
		const auto* sprite = entity->GetComponent<SpriteComponent>();
		const auto* transform = entity->GetComponent<TransformComponent>();

		const auto& position = transform->CurrentPos;
		const auto& scale = transform->Scale;
		const auto& rotation = transform->Rotation;

		Hi_Engine::RenderCommand command{};
		command.Type = Hi_Engine::eRenderCommandType::DrawSprite;
		command.SpriteRenderData = { sprite->Subtexture, { 1.f, 1.f, 1.f, 1.f }, Hi_Engine::Transform{{ position.x, position.y, 0.f }, { scale.x, scale.y }, rotation } }; // CHANGE TO Transform

		renderCommands.push(command);
	}
	Hi_Engine::Dispatcher::GetInstance().SendEventInstantly<Hi_Engine::RenderEvent>(renderCommands);
}

void UIRenderSystem::RenderUI()
{
	auto* camera = m_entityManager->FindFirst<CameraComponent>();

	if (!camera)
		return;

	auto entities = m_entityManager->FindAll<UIComponent, SpriteComponent>();

	if (entities.empty())
		return;


	// TODO; use a simpler Shader for HUD?

	std::queue<Hi_Engine::RenderCommand> renderCommands;

	// Add projection command (NOT NEEDED?? Use old projection matrix
	Hi_Engine::RenderCommand projectionCommand{};
	projectionCommand.Type = Hi_Engine::eRenderCommandType::SetProjectionMatrix;
	//projectionCommand.ProjectionMatrix = glm::ortho(0.f, 1400.f, 0.f, 800.f, 0.f, 100.f);
	projectionCommand.ProjectionMatrix = camera->GetComponent<CameraComponent>()->Camera.GetProjectionMatrix();
	renderCommands.push(projectionCommand);

	for (auto* entity : entities)
	{
		const auto* sprite = entity->GetComponent<SpriteComponent>();
		const auto* transform = entity->GetComponent<TransformComponent>();

		const auto& position = transform->CurrentPos;
		const auto& scale = transform->Scale;
		const auto& rotation = transform->Rotation;

		Hi_Engine::RenderCommand command{};
		command.Type = Hi_Engine::eRenderCommandType::DrawSprite;
		command.SpriteRenderData = { sprite->Subtexture, { 1.f, 1.f, 1.f, 1.f }, Hi_Engine::Transform{{ position.x, position.y, 0.f }, { scale.x, scale.y }, rotation } }; // CHANGE TO Transform

		renderCommands.push(command);
	}
	Hi_Engine::Dispatcher::GetInstance().SendEventInstantly<Hi_Engine::RenderEvent>(renderCommands);
}

void UIRenderSystem::RenderInventory()
{
	// get inventory... get slots...

	// TODO: dont push camera every time?!

	auto* inventory = m_entityManager->FindFirst<InventoryComponent>(); // not inventory component? use something else...
	if (!inventory)
		return;

	auto* camera = m_entityManager->FindFirst<CameraComponent>();


	auto* inventoryComponent = inventory->GetComponent<InventoryComponent>();

	//if (inventory && !inventoryComponent->IsOpen)
	//	return;

	std::queue<Hi_Engine::RenderCommand> renderCommands;
	Hi_Engine::RenderCommand projectionCommand{};
	projectionCommand.Type = Hi_Engine::eRenderCommandType::SetProjectionMatrix;
	//projectionCommand.ProjectionMatrix = glm::ortho(0.f, 1400.f, 0.f, 800.f, 0.f, 100.f);
	projectionCommand.ProjectionMatrix = camera->GetComponent<CameraComponent>()->Camera.GetProjectionMatrix();
	renderCommands.push(projectionCommand);

	glm::vec2 position = { 0.f, 0.f }; // TODO; increment position each frame...
	glm::vec2 scale = { 1.f, 1.f };

	for (int i = 0; i < inventoryComponent->MaxSlots; ++i)
	{
		position.x += 1.f * scale.x;

		if (i >= 12) // "new row"
			position.y += 1.f * scale.y;

		Hi_Engine::RenderCommand command{};

		//glm::vec2 scale;
		auto& texture = Hi_Engine::ResourceHolder<Hi_Engine::Subtexture2D>::GetInstance().GetResource("debug_00");
		command.SpriteRenderData = { &texture, { 0.5f, 0.2f, 0.7f, 1.f }, Hi_Engine::Transform{{ position.x, position.y, 0.f }, { scale.x, scale.y }, 0.f } }; // CHANGE TO Transform

		renderCommands.push(command);
	}
	Hi_Engine::Dispatcher::GetInstance().SendEventInstantly<Hi_Engine::RenderEvent>(renderCommands);

}
