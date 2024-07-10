#include "Pch.h"
#include "UIRenderSystem.h"
#include "Entities/EntityManager.h"
#include "Components/UI/UIComponents.h"
#include "Components/Core/CoreComponents.h"
#include "Components/Gameplay/GameplayComponents.h"
#include "../../../../../../ThirdParty/glm/ext/matrix_clip_space.hpp"


UIRenderSystem::UIRenderSystem()
{
}

UIRenderSystem::~UIRenderSystem()
{
}

void UIRenderSystem::Draw()
{
	assert(m_entityManager && "ERROR: EntityManager is nullptr!");


	// TODO Create a single sprite batch?
	RenderGrid();

	// TODO; Don't have HUDComponent?? Just UIComponent?
	RenderHUD();
	//RenderGrid();
	RenderUI();
	
	//RenderInventory();
}

void UIRenderSystem::RenderHUD()
{
	auto* camera = m_entityManager->FindFirst<CameraComponent>();
	if (!camera)
		return;

	auto entities = m_entityManager->FindAll<HUDComponent>();
	if (entities.empty())
		return;
	
	auto* cameraComponent = camera->GetComponent<CameraComponent>();
	if (!cameraComponent)
		return;

	// TODO; use a simpler GLSLShader for HUD?
	
	Hi_Engine::SpriteBatch spriteBatch;
	spriteBatch.Sprites.reserve(entities.size());

	for (auto* entity : entities)
	{
		const auto* spriteComponent = entity->GetComponent<SpriteComponent>();
		const auto* transformComponent = entity->GetComponent<TransformComponent>();

		if (!spriteComponent || !transformComponent)
			continue;

		const auto& position = transformComponent->CurrentPos;
		const auto& scale = transformComponent->Scale;
		const auto& rotation = transformComponent->Rotation;

		glm::vec4 color = { spriteComponent->CurrentColor.x, spriteComponent->CurrentColor.y, spriteComponent->CurrentColor.z, spriteComponent->CurrentColor.w };

		spriteBatch.Sprites.emplace_back(Hi_Engine::Transform{ { position.x, position.y, 0.f }, { scale.x, scale.y }, rotation }, color, spriteComponent->Subtexture);
	}
	
	spriteBatch.ProjectionMatrix = cameraComponent->Camera.GetProjectionMatrix();

	Hi_Engine::Dispatcher::GetInstance().SendEventInstantly<Hi_Engine::SpriteBatchRequest>(spriteBatch);
}

// Render cursor, buttons, images
// TODO; use a simpler GLSLShader for HUD?
void UIRenderSystem::RenderUI()
{
	auto* camera = m_entityManager->FindFirst<CameraComponent>();
	if (!camera)
		return;

	auto entities = m_entityManager->FindAll<UIComponent, SpriteComponent>();
	if (entities.empty())
		return;

	auto* cameraComponent = camera->GetComponent<CameraComponent>();
	if (!cameraComponent)
		return;

	std::sort(entities.begin(), entities.end(), [](const Entity* e1, const Entity* e2)
		{
			auto e1UIComponent = e1->GetComponent<UIComponent>();
			auto e2UIComponent = e2->GetComponent<UIComponent>();

			return e1UIComponent->RenderDepth > e2UIComponent->RenderDepth;
		});

	Hi_Engine::SpriteBatch spriteBatch;
	spriteBatch.Sprites.reserve(entities.size());

	static float windowWidth = 1400.f; // Todo; Pull from window
	static float windowHeight = 800.f;

	for (auto* entity : entities)
	{
		const auto* spriteComponent = entity->GetComponent<SpriteComponent>();
		const auto* transformComponent = entity->GetComponent<TransformComponent>();

		if (!spriteComponent || !transformComponent)
			continue;

		const auto& [currPos, prevPos, scale, pivot, rotation] = *transformComponent;
		const auto& [r, g, b, a] = spriteComponent->CurrentColor;

		float xPosition = currPos.x * windowWidth;
		xPosition += (scale.x * pivot.x);

		float yPosition = currPos.y * windowHeight;
		yPosition += (scale.y * pivot.y);

		spriteBatch.Sprites.emplace_back(Hi_Engine::Transform{ { xPosition, yPosition, 0.f }, { scale.x, scale.y }, rotation }, glm::vec4{ r, g, b, a }, spriteComponent->Subtexture);
	}

	spriteBatch.ProjectionMatrix = cameraComponent->Camera.GetProjectionMatrix();

	Hi_Engine::Dispatcher::GetInstance().SendEventInstantly<Hi_Engine::SpriteBatchRequest>(spriteBatch);
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

	//std::queue<Hi_Engine::RenderCommand> renderCommands;
	//Hi_Engine::RenderCommand projectionCommand{};
	//projectionCommand.Type = Hi_Engine::eRenderCommandType::SetProjectionMatrix;
	////projectionCommand.ProjectionMatrix = glm::ortho(0.f, 1400.f, 0.f, 800.f, 0.f, 100.f);
	//projectionCommand.ProjectionMatrix = camera->GetComponent<CameraComponent>()->Camera.GetProjectionMatrix();
	//renderCommands.push(projectionCommand);

	//glm::vec2 position = { 0.f, 0.f }; // TODO; increment position each frame...
	//glm::vec2 scale = { 1.f, 1.f };

	//for (int i = 0; i < inventoryComponent->MaxSlots; ++i)
	//{
	//	position.x += 1.f * scale.x;

	//	if (i >= 12) // "new row"
	//		position.y += 1.f * scale.y;

	//	Hi_Engine::RenderCommand command{};

	//	//glm::vec2 scale;
	//	auto& texture = Hi_Engine::ResourceHolder<Hi_Engine::Subtexture2D, Hi_Engine::SubtextureData>::GetInstance().GetResource({ "debug", 0, 0 });
	//	command.SpriteRenderData = { &texture, { 0.5f, 0.2f, 0.7f, 1.f }, Hi_Engine::Transform{{ position.x, position.y, 0.f }, { scale.x, scale.y }, 0.f } }; // CHANGE TO Transform

	//	renderCommands.push(command);
	//}
	//Hi_Engine::Dispatcher::GetInstance().SendEventInstantly<Hi_Engine::RenderEvent>(renderCommands);

}

void UIRenderSystem::RenderGrid() // Do in debug system?
{
	if (auto* grid = m_entityManager->FindFirst<GridComponent>())
	{
		auto* texture = &Hi_Engine::ResourceHolder<Hi_Engine::Subtexture2D, Hi_Engine::SubtextureData>::GetInstance().GetResource({ "debug", 0, 0 });

		auto* gridComponent = grid->GetComponent<GridComponent>();
		auto* transformComponent = grid->GetComponent<TransformComponent>();
	
		const auto& position = transformComponent->CurrentPos;

		auto window = Hi_Engine::ServiceLocator::GetWindow();
		auto win = window.lock();


		auto scale = transformComponent->Scale;
		scale.x /= win->GetSize().x;
		scale.y /= win->GetSize().y;

		const auto& dimensions = gridComponent->Dimensions;

		float spaceBetweenCells = gridComponent->SpaceBetweenCells;
		spaceBetweenCells = 0.55f;

		float width = dimensions.y / scale.x;
		width /= win->GetSize().x;
		//width *= 0.25f;

		float height = scale.y * 0.5f;

		width = 0.1f;
		height = 0.1f;

		Hi_Engine::SpriteBatch spriteBatch;

		float xStartPosition = position.x - scale.x;

		for (int row = 0; row < dimensions.x; ++row)
		{
			for (int col = 0; col < dimensions.y; ++col)
			{
				//float xPosition = position.x + (col * width);
				float xPosition = xStartPosition * 0.5f + (col * (width + col > 0 ? spaceBetweenCells : 0));

				spriteBatch.Sprites.emplace_back(Hi_Engine::Transform{ { xPosition, position.y, 0.f }, { width, height }, 0.f }, glm::vec4{ 1.f, 1.f, 1.f, 1.f }, texture);
			}
		}

		auto* camera = m_entityManager->FindFirst<CameraComponent>();
		auto* cameraComponent = camera->GetComponent<CameraComponent>();
		spriteBatch.ProjectionMatrix = cameraComponent->Camera.GetProjectionMatrix();

		Hi_Engine::Dispatcher::GetInstance().SendEventInstantly<Hi_Engine::SpriteBatchRequest>(spriteBatch);
	}
}

FVector2 UIRenderSystem::ConvertToScreenCoordinates(const FVector2& normalizedPosition, const FVector2& screenSize) const
{
	FVector2 coordinates = { normalizedPosition.x * screenSize.x, normalizedPosition.y * screenSize.y };
	return coordinates;
}
