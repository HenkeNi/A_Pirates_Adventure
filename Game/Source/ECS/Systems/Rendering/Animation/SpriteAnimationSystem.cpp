#include "Pch.h"
#include "SpriteAnimationSystem.h"
#include "Entities/EntityManager.h"
#include "Components/Core/CoreComponents.h"
#include "Components/Gameplay/GameplayComponents.h"

SpriteAnimationSystem::SpriteAnimationSystem()
{
}

SpriteAnimationSystem::~SpriteAnimationSystem()
{
}

void SpriteAnimationSystem::Receive(Message& message)
{
}

void SpriteAnimationSystem::Update(float deltaTime) 
{
	if (!m_entityManager)
		return;

	auto entities = m_entityManager->FindAll<TransformComponent, AnimationComponent, SpriteComponent>();

	for (auto* entity : entities)
	{
		auto* transformComponent	= entity->GetComponent<TransformComponent>();
		auto* spriteComponent		= entity->GetComponent<SpriteComponent>();
		auto* animationComponent	= entity->GetComponent<AnimationComponent>();

		
							
		// won't work with animated trees?? (maybe won't be animated? -> maybe shader instead)?
		const std::string currentState = GetCurrentState(entity);								
		auto& animation = animationComponent->Animations[currentState];
		
		if (auto* velocityComponent = entity->GetComponent<VelocityComponent>())
		{
			UpdateSpriteOrientation(velocityComponent, transformComponent); // pass in entity instead?+
		}


		float& elapsedTime = animation.ElapsedFrameTime;
		elapsedTime += deltaTime;

		if (elapsedTime >= animation.FrameDuration)
		{
			elapsedTime = 0.f;
			++animation.CurrentFrame;

			if (animation.CurrentFrame >= animation.TotalFrames)
			{
				if (!animation.IsLooping)
				{
					// Set default animation... (stack?)

					// Reset animation? Make class?
					animation.CurrentFrame = 0;
					animation.ElapsedFrameTime = 0.f;
					animation.IsPlaying = false;
					

					// each animation has a callback instead?!
					if (currentState == "Attack") // Fix...
					{
						PostMaster::GetInstance().SendMessage({ eMessage::AttackAnimationFinished, entity });
					}
					//else if (characterStateComponent->m_isRunning)
					//{

					//}
					//else if (characterStateComponent->m_isWalking)
					//{
					//	entity->GetComponent<AnimationComponent>()->m_active = "Walk";
					//}
					//else if (characterStateComponent->m_isIdle)
					//{
					//	entity->GetComponent<AnimationComponent>()->m_active = "Idle";
					//}



					// animationComponent->m_active = "Idle";

					return;
				}

				animation.CurrentFrame = 0;
			}

			// TODO; Set correct sprite image...

			spriteComponent->Subtexture = animation.Animations[animation.CurrentFrame];

			//std::string sprite = animation.Sprites[animation.CurrentFrame];
			//spriteComponent->Subtexture = &Hi_Engine::ResourceHolder<Hi_Engine::Subtexture2D>::GetInstance().GetResource(sprite);

			//spriteComponent->m_material.SetTexture(&Hi_Engine::ResourceHolder<Hi_Engine::Texture2D>::GetInstance().GetResource(sprite));
		}
	}
}

// Todo; no need for m_active?
std::string SpriteAnimationSystem::GetCurrentState(Entity* entity) const
{
	auto* characterStateComponent	= entity->GetComponent<CharacterStateComponent>();
	auto* animationComponent		= entity->GetComponent<AnimationComponent>();

	// Todo; create map?

	if (characterStateComponent->IsAttacking)
	{
		//animationComponent->m_active = "Attack";
		return "Attack";
	}
	else if (characterStateComponent->IsRunning)
	{
		return "Run";
	}
	else if (characterStateComponent->IsWalking)
	{
		return "Walk";
	}
	else if (characterStateComponent->IsIdle)
	{
		return "Idle";
	}

	return "Idle";
}

void SpriteAnimationSystem::UpdateSpriteOrientation(struct VelocityComponent* velocityComponent, struct TransformComponent* transformComponent)
{
	if (velocityComponent->Velocity.x >= 1.f)
	{
		if (transformComponent->Scale.x < 0.f)
			transformComponent->Scale.x *= -1.f;

		//if (aTransformComponent->Scale.x == -1.f)
		//	aTransformComponent->Scale.x = 1.f;
	}
	else if (velocityComponent->Velocity.x <= -1.f)
	{
		if (transformComponent->Scale.x > 0.f)
			transformComponent->Scale.x *= -1.f;
		//if (aTransformComponent->Scale.x == 1.f)
		//	aTransformComponent->Scale.x = -1.f;
	}
}