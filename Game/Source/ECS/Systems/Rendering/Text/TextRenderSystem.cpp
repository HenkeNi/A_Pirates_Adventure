#include "Pch.h"
#include "TextRenderSystem.h"
#include "Entities/EntityManager.h"
#include "Components/Core/CoreComponents.h"


TextRenderSystem::TextRenderSystem()
{
}

TextRenderSystem::~TextRenderSystem()
{
}

void TextRenderSystem::Receive(Message& message)
{
}

void TextRenderSystem::Draw()
{
	if (!m_entityManager)
		return;

	auto entities = m_entityManager->FindAll<TextComponent, TransformComponent>();

	// DO in initilaizcomponent instead
	auto* shader = &Hi_Engine::ResourceHolder<Hi_Engine::Shader>::GetInstance().GetResource("Text"); // FIX!! set in Renderer before...

	auto* camera = m_entityManager->FindFirst<CameraComponent>();
	const auto& projection = camera->GetComponent<CameraComponent>()->Camera.GetProjectionMatrix();

	for (const auto& entity : entities)
	{
		const auto& textComponent = entity->GetComponent<TextComponent>();
		const auto& transformComponent = entity->GetComponent<TransformComponent>();

		const auto& position = CU::Vector2<float>{ transformComponent->CurrentPos.x, transformComponent->CurrentPos.y };

		CU::Vector2<float> renderPosition;
		renderPosition.x = transformComponent->CurrentPos.x + (transformComponent->Pivot.x * textComponent->Size); // transformComponent->Scale.x);
		renderPosition.y = transformComponent->CurrentPos.y + (transformComponent->Pivot.y * textComponent->Size); // transformComponent->Scale.y); // TODO: add font size??


		auto color = textComponent->Color; // FIX!

		Hi_Engine::TextRenderer::GetInstance().Render({ shader, textComponent->Font, transformComponent->Scale.x, color, renderPosition, textComponent->Text }, projection);
	}

	// TEST
	//auto& shader = Hi_Engine::ResourceHolder<Hi_Engine::Shader>::GetInstance().GetResource("Text");
	//auto& font = Hi_Engine::ResourceHolder<Hi_Engine::Font>::GetInstance().GetResource("Basic");
	// Hi_Engine::TextRenderer::GetInstance().Render({ shader, &font, 2.f, { 1.f, 1.f, 1.f }, { 230.f, 338.f}, "GHello world" });
}