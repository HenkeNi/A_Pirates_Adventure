#include "Pch.h"
#include "SpriteAnimationSystem.h"
#include "Components/Core/CoreComponents.h"
#include "Components/Gameplay/GameplayComponents.h"
#include "ECS.h"


SpriteAnimationSystem::SpriteAnimationSystem()
{
}

SpriteAnimationSystem::~SpriteAnimationSystem()
{
}

void SpriteAnimationSystem::Update(float deltaTime) 
{
	// assert(m_entityManager && "ERROR: EntityManager is nullptr!");

	auto entities = m_ecs->FindEntities(m_signatures["Animations"]);

	for (auto entity : entities)
	{
		auto* transformComponent	= m_ecs->GetComponent<TransformComponent>(entity);
		auto* spriteComponent		= m_ecs->GetComponent<SpriteComponent>(entity);
		auto* animationComponent	= m_ecs->GetComponent<AnimationComponent>(entity);

		
							
		// won't work with animated trees?? (maybe won't be animated? -> maybe shader instead)?
		const std::string currentState = GetCurrentState(entity);								
		auto& animation = animationComponent->Animations[currentState];
		
		if (auto* velocityComponent = m_ecs->GetComponent<VelocityComponent>(entity))
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
					if (currentState == "attack") // Fix...
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

void SpriteAnimationSystem::SetSignature()
{
	m_signatures.insert({ "Animations", m_ecs->GetSignature<AnimationComponent, TransformComponent, SpriteComponent>() });
}

// Todo; no need for m_active?
std::string SpriteAnimationSystem::GetCurrentState(Entity entity) const
{
	auto* characterStateComponent	= m_ecs->GetComponent<CharacterStateComponent>(entity);
	auto* animationComponent		= m_ecs->GetComponent<AnimationComponent>(entity);

	// Todo; create map?

	if (characterStateComponent->IsAttacking)
	{
		//animationComponent->m_active = "Attack";
		return "attack";
	}
	else if (characterStateComponent->IsRunning)
	{
		return "run";
	}
	else if (characterStateComponent->IsWalking)
	{
		return "walk";
	}
	else if (characterStateComponent->IsIdle)
	{
		return "idle";
	}

	return "idle";
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