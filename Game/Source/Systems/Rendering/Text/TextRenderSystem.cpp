#include "Pch.h"
#include "TextRenderSystem.h"
#include "EntityManager.h"


TextRenderSystem::TextRenderSystem()
{
}

TextRenderSystem::~TextRenderSystem()
{
}

void TextRenderSystem::Receive(Message& aMsg)
{
}

void TextRenderSystem::Draw()
{
	if (!m_entityManager)
		return;

	auto entities = m_entityManager->FindAllWithComponents<TextComponent, TransformComponent>();

	for (const auto& entity : entities)
	{
		const auto& textComponent		= entity->GetComponent<TextComponent>();
		const auto& transformComponent	= entity->GetComponent<TransformComponent>();

		const auto& position = CU::Vector2<float>{ transformComponent->CurrentPos.x, transformComponent->CurrentPos.y };

		Hi_Engine::TextRenderer::GetInstance().Render({ textComponent->Shader, textComponent->Font, transformComponent->Scale.x, textComponent->Color, position, textComponent->Text });
	}

	// TEST
	auto& shader = Hi_Engine::ResourceHolder<Hi_Engine::Shader>::GetInstance().GetResource("Text");
	auto& font = Hi_Engine::ResourceHolder<Hi_Engine::Font>::GetInstance().GetResource("Basic");
	Hi_Engine::TextRenderer::GetInstance().Render({ &shader, &font, 2.f, { 1.f, 1.f, 1.f }, { 230.f, 338.f}, "GHello world" });
}