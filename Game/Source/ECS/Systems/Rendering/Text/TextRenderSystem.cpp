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
	assert(m_entityManager && "ERROR: EntityManager is nullptr!");


	// DO in initilaizcomponent instead
	auto* shader = &Hi_Engine::ResourceHolder<Hi_Engine::GLSLShader>::GetInstance().GetResource("Text"); // FIX!! set in Renderer before...

	auto* camera = m_entityManager->FindFirst<CameraComponent>();
	const auto& projection = camera->GetComponent<CameraComponent>()->Camera.GetProjectionMatrix();

	auto entities = m_entityManager->FindAll<TextComponent, TransformComponent>();
	for (const auto& entity : entities)
	{
		const auto* transformComponent = entity->GetComponent<TransformComponent>();
		const auto* textComponent = entity->GetComponent<TextComponent>();

		const auto& position = FVector2{ transformComponent->CurrentPos.x, transformComponent->CurrentPos.y };

		FVector2 renderPosition;
		renderPosition.x = transformComponent->CurrentPos.x + (transformComponent->Pivot.x * textComponent->Size); // transformComponent->Scale.x);
		renderPosition.y = transformComponent->CurrentPos.y + (transformComponent->Pivot.y * textComponent->Size); // transformComponent->Scale.y); // TODO: add font size??

		Hi_Engine::Dispatcher::GetInstance().SendEventInstantly<Hi_Engine::TextRenderEvent>(Hi_Engine::TextRenderData{ shader, textComponent->Font, (float)1.f, textComponent->Color, renderPosition, textComponent->Text, textComponent->Alignment }, projection);
	}
}