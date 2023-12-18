#include "Pch.h"
#include "TextRenderSystem.h"
#include "Entities/EntityManager.h"
#include "Components/Core/CoreComponents.h"
#include "Components/Rendering/RenderComponents.h"


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

	auto entities = m_entityManager->FindAll<TextComponent, TransformComponent>();

	auto* shader = &Hi_Engine::ResourceHolder<Hi_Engine::Shader>::GetInstance().GetResource("Text"); // FIX!! set in Renderer before...

	for (const auto& entity : entities)
	{
		const auto& textComponent		= entity->GetComponent<TextComponent>();
		const auto& transformComponent	= entity->GetComponent<TransformComponent>();

		const auto& position = CU::Vector2<float>{ transformComponent->CurrentPos.x, transformComponent->CurrentPos.y };


		auto color = textComponent->Color; // FIX!

		Hi_Engine::TextRenderer::GetInstance().Render({ shader, textComponent->Font, transformComponent->Scale.x, { color.x, color.y, color.z }, position, textComponent->Text});
	}

	// TEST
	//auto& shader = Hi_Engine::ResourceHolder<Hi_Engine::Shader>::GetInstance().GetResource("Text");
	//auto& font = Hi_Engine::ResourceHolder<Hi_Engine::Font>::GetInstance().GetResource("Basic");
	// Hi_Engine::TextRenderer::GetInstance().Render({ shader, &font, 2.f, { 1.f, 1.f, 1.f }, { 230.f, 338.f}, "GHello world" });
}