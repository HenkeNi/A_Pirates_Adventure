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

void SpriteAnimationSystem::Update(float aDeltaTime) 
{
	if (!m_entityManager)
		return;

	auto entities = m_entityManager->FindAllWithComponents<TransformComponent, AnimationComponent, SpriteComponent>();

	for (auto& entity : entities)
	{
		auto* animationComponent = entity->GetComponent<AnimationComponent>();

		float& elapsedTime = animationComponent->m_elapsedFrameTime;

		elapsedTime += aDeltaTime;

		if (elapsedTime >= animationComponent->m_frameDuration)
		{
			elapsedTime = 0.f;
			//++animationComponent->m_currentFrame;
			animationComponent->m_currentFrame += 1;

			if (animationComponent->m_currentFrame >= animationComponent->m_totalFrames)
			{
				animationComponent->m_currentFrame = 0;
			}

			// TODO; Set correct sprite image...
			std::string animation = animationComponent->m_animations[animationComponent->m_currentFrame];

			auto* spriteComponent = entity->GetComponent<SpriteComponent>();
			spriteComponent->m_material.SetTexture(&Hi_Engine::ResourceHolder<Hi_Engine::Texture2D>::GetInstance().GetResource(animation));
		}
	}
}


//void SpriteAnimationSystem::Draw()
//{
//}