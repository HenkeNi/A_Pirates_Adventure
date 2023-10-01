#include "Pch.h"
#include "SpriteAnimationSystem.h"
#include "EntityManager.h"
#include "Rendering/RenderComponents.h"
#include "Core/CoreComponents.h"


SpriteAnimationSystem::SpriteAnimationSystem()
{
	//PostMaster::GetInstance().Subscribe(eMessage::EntityAttacking, this);
	//PostMaster::GetInstance().Subscribe(eMessage::EntityWalking, this);
	//PostMaster::GetInstance().Subscribe(eMessage::EntityIdle, this);
}

SpriteAnimationSystem::~SpriteAnimationSystem()
{
	/*PostMaster::GetInstance().Unsubscribe(eMessage::EntityAttacking, this);
	PostMaster::GetInstance().Unsubscribe(eMessage::EntityWalking, this);
	PostMaster::GetInstance().Unsubscribe(eMessage::EntityIdle, this);*/
}

// TODO; pass animation state? or player state?
void SpriteAnimationSystem::Receive(Message& aMsg)
{
	//auto entity = std::any_cast<Entity*>(aMsg.GetData());

	//switch (aMsg.GetMessageType())
	//{
	//case eMessage::EntityAttacking:
	//	entity->GetComponent<AnimationComponent>()->m_active = "Attack";
	//	break;
	//case eMessage::EntityWalking:
	//	entity->GetComponent<AnimationComponent>()->m_active = "Walk";
	//	break;
	//case eMessage::EntityIdle:
	//	entity->GetComponent<AnimationComponent>()->m_active = "Idle";
	//	break;
	//}


	// listens for events?? AttackStarted, AttackFinished? AnimationCOmpinnet contains cuurent animation	 state??
}

void SpriteAnimationSystem::Update(float aDeltaTime) 
{
	if (!m_entityManager)
		return;

	auto entities = m_entityManager->FindAllWithComponents<TransformComponent, AnimationComponent, SpriteComponent>();

	for (auto* entity : entities)
	{
		auto* animationComponent = entity->GetComponent<AnimationComponent>();
	
		const std::string currentState = GetCurrentState(entity);								// won't work with animated trees?? (maybe won't be animated? -> maybe shader instead)?
		auto& animation = animationComponent->Animations[currentState];
		
		if (auto* velocityComponent = entity->GetComponent<VelocityComponent>())
		{
			SetSpriteOrientation(animationComponent, velocityComponent); // pass in entity instead?+
		}




		// TODO; get direction of entity (movemeent => if any)

		float& elapsedTime = animation.ElapsedFrameTime;

		elapsedTime += aDeltaTime;

		if (elapsedTime >= animation.FrameDuration)
		{
			elapsedTime = 0.f;
			//++animationComponent->m_currentFrame;
			animation.CurrentFrame += 1;

			if (animation.CurrentFrame >= animation.TotalFrames)
			{
				if (!animation.IsLooping)
				{
					// Set default animation...


					// Reset animation? Make class?
					animation.CurrentFrame = 0;
					animation.ElapsedFrameTime = 0.f;
					animation.IsPlaying = false;
					


					// PostMaster::GetInstance().SendMessage({ eMessage::AnimationComplete, entity });

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
			std::string sprite = animation.Sprites[animation.CurrentFrame];

			auto* spriteComponent = entity->GetComponent<SpriteComponent>();
			spriteComponent->Subtexture = &Hi_Engine::ResourceHolder<Hi_Engine::Subtexture2D>::GetInstance().GetResource(sprite);
			//spriteComponent->m_material.SetTexture(&Hi_Engine::ResourceHolder<Hi_Engine::Texture2D>::GetInstance().GetResource(sprite));
		}
	}
}


//void SpriteAnimationSystem::Draw()
//{
//}

// Todo; no need for m_active?
std::string SpriteAnimationSystem::GetCurrentState(Entity* anEntity) const
{
	auto* characterStateComponent	= anEntity->GetComponent<CharacterStateComponent>();
	auto* animationComponent		= anEntity->GetComponent<AnimationComponent>();

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

void SpriteAnimationSystem::SetSpriteOrientation(struct AnimationComponent* anAnimationComponent, struct VelocityComponent* aVelocityComponent)
{

}