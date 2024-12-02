#include "Pch.h"
#include "AnimationSystem.h"
#include "Components/Core/CoreComponents.h"
#include "Components/Gameplay/GameplayComponents.h"
#include "ECS.h"


AnimationSystem::AnimationSystem()
{
	// TODO; listen for State changes?? StateMachineSystem?
}

AnimationSystem::~AnimationSystem()
{
}

void AnimationSystem::Update(float deltaTime)
{
	assert(m_ecs && "[SpriteAnimationSystem::Update] - ECS is not initialized!");

	for (auto entity : m_ecs->FindEntities(m_signatures["Animations"]))
	{
		SelectAnimation(entity);					// listen to event instead?
		UpdateAnimation(deltaTime, entity);
	}
} 

void AnimationSystem::SetSignature()
{
	m_signatures.insert({ "Animations", m_ecs->GetSignature<AnimationComponent, SpriteComponent>() });
}

void AnimationSystem::SelectAnimation(Entity entity)
{
	if (auto* stateComponent = m_ecs->GetComponent<StateComponent>(entity))
	{
		auto* animationComponent = m_ecs->GetComponent<AnimationComponent>(entity);
		animationComponent->ActiveAnimation = stateComponent->CurrentState;

		// TODO; check if has played?
	}
}

void AnimationSystem::UpdateAnimation(float deltaTime, Entity entity)
{
	auto* spriteComponent = m_ecs->GetComponent<SpriteComponent>(entity);
	auto* animationComponent = m_ecs->GetComponent<AnimationComponent>(entity);

	auto animationEntry = animationComponent->Animations.find(animationComponent->ActiveAnimation);

	if (animationEntry == animationComponent->Animations.end())
	{
		std::cerr << "[AnimationSystem::UpdateAnimation] - animation not found!\n";
		return;
	}

	auto& animation = animationEntry->second;
	auto& frame = animation.Frames[animation.CurrentFrameIndex];

	float& elapsedTime = animationComponent->ElapsedFrameTime;
	elapsedTime += deltaTime;

	if (elapsedTime >= frame.Duration)
	{
		elapsedTime = 0.f;

		spriteComponent->Subtexture = Hi_Engine::ResourceHolder<Hi_Engine::Subtexture2D, Hi_Engine::SubtextureData>::GetInstance().GetResource({ animationComponent->TextureID, frame.Row, frame.Col });

		++animation.CurrentFrameIndex;
		if (animation.CurrentFrameIndex >= animation.Frames.size())
		{
			animation.CurrentFrameIndex = 0;

			if (!animation.IsLooping)
			{
				animationComponent->ActiveAnimation = animationComponent->DefaultAnimation; // move to on animation finihsed?
				OnAnimationFinished();
			}
		}
	}
}

void AnimationSystem::OnAnimationFinished()
{
	// Send event
}
