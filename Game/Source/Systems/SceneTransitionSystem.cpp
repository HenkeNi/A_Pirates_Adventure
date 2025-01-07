#include "Pch.h"
#include "SceneTransitionSystem.h"


SceneTransitionSystem::SceneTransitionSystem(Hi_Engine::ECSCoordinator& ecs, SceneManager& manager)
	: System{ ecs }, m_sceneManager{ manager }
{
	PostMaster::GetInstance().Subscribe(eMessage::TransitionToScene, this);
}

SceneTransitionSystem::~SceneTransitionSystem()
{
	PostMaster::GetInstance().Unsubscribe(eMessage::TransitionToScene, this);
}

void SceneTransitionSystem::Update(float deltaTime)
{
}

void SceneTransitionSystem::Receive(Message& message)
{
	if (message.GetMessageType() == eMessage::TransitionToScene)
	{
		int xx = 20;
		xx += 20;
	}
}

Hi_Engine::eUpdatePhase SceneTransitionSystem::GetUpdatePhase() const
{
	return Hi_Engine::eUpdatePhase::Update;
}
