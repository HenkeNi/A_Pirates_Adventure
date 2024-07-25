#include "Pch.h"
#include "TextRenderSystem.h"
#include "Components/Core/CoreComponents.h"
#include "ECS.h"

//#include "Entities/EntityManager.h"
TextRenderSystem::TextRenderSystem()
{
}

TextRenderSystem::~TextRenderSystem()
{
}

void TextRenderSystem::Draw()
{
	assert(m_ecs && "[TextRenderSystem - ERROR]: ECS is nullptr!");


	// DO in initilaizcomponent instead
	auto* shader = &Hi_Engine::ResourceHolder<Hi_Engine::GLSLShader>::GetInstance().GetResource("Text"); // FIX!! set in Renderer before...


	auto camera = m_ecs->FindEntity(m_signatures["Camera"]);
	if (!camera)
		return;

	const auto* cameraComponent = m_ecs->GetComponent<CameraComponent>(camera.value());
	auto projectionMatrix = cameraComponent->Camera.GetProjectionMatrix();

	auto entities = m_ecs->FindEntities(m_signatures["Text"]);	
	for (Entity entity : entities)
	{
		const auto* transformComponent = m_ecs->GetComponent<TransformComponent>(entity);
		const auto* textComponent = m_ecs->GetComponent<TextComponent>(entity);

		const auto& [currentPos, previousPos, scale, pivot, rotation] = *transformComponent;
		const auto& [text, color, size, alignment, font] = *textComponent;
	
		FVector2 position;
		position.x = currentPos.x + (pivot.x * size);
		position.y = currentPos.y + (pivot.y * size);

		Hi_Engine::Dispatcher::GetInstance().SendEventInstantly<Hi_Engine::TextRenderEvent>(Hi_Engine::TextRenderData{ shader, font, (float)1.f, color, position, text, alignment }, projectionMatrix);
	}
}

void TextRenderSystem::SetSignature()
{
	assert(m_ecs && "[TextRenderSystem - ERROR]: ECS is nullptr!");

	m_signatures.insert({ "Camera", m_ecs->GetSignature<CameraComponent>() });
	m_signatures.insert({ "Text", m_ecs->GetSignature<TextComponent, TransformComponent>() });
}
