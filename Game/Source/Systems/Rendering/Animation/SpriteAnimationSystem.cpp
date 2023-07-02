#include "Pch.h"
#include "SpriteAnimationSystem.h"
#include "EntityManager.h"
#include "Rendering/RenderComponents.h"
#include "Core/CoreComponents.h"


SpriteAnimationSystem::SpriteAnimationSystem()
{
}
SpriteAnimationSystem::~SpriteAnimationSystem()
{
}

void SpriteAnimationSystem::Receive(Message& aMsg)
{
}

void SpriteAnimationSystem::Draw()
{
	if (!m_entityManager)
		return;

	auto entities = m_entityManager->FindAllWithComponents<TransformComponent, AnimationComponent, SpriteComponent>();


	// update the current sprite?!
}