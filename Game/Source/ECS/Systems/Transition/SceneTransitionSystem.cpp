#include "Pch.h"
#include "SceneTransitionSystem.h"

SceneTransitionSystem::SceneTransitionSystem()
{
}

SceneTransitionSystem::~SceneTransitionSystem()
{
}

void SceneTransitionSystem::Receive(Message& aMsg) // Psas trigger?? check if have scen transition componennt
{
	if (aMsg.GetMessageType() == eMessage::TriggerActivated)
	{

		std::cout << "Change scene...\n";
	}
}

void SceneTransitionSystem::Update(float aDeltaTime)
{
}
