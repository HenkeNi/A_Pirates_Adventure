#include "Pch.h"
#include "SceneTransitionSystem.h"


SceneTransitionSystem::SceneTransitionSystem(Hi_Engine::ECSCoordinator& ecs, SceneManager& manager)
	: System{ ecs }, m_sceneManager{ manager }
{
}

void SceneTransitionSystem::Update(float deltaTime)
{
}

Hi_Engine::eUpdatePhase SceneTransitionSystem::GetUpdatePhase() const
{
	return Hi_Engine::eUpdatePhase::Update;
}
