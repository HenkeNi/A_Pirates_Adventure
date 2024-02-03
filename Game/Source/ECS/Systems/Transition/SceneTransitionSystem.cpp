#include "Pch.h"
#include "SceneTransitionSystem.h"
#include "Entities/Entity.h"
#include "Components/Core/CoreComponents.h"

SceneTransitionSystem::SceneTransitionSystem()
{
	PostMaster::GetInstance().Subscribe(eMessage::TriggerActivated, this);
}

SceneTransitionSystem::~SceneTransitionSystem()
{
	PostMaster::GetInstance().Unsubscribe(eMessage::TriggerActivated, this);
}

void SceneTransitionSystem::Receive(Message& aMsg) // Psas trigger?? check if have scen transition componennt
{
	if (auto* entity = std::any_cast<Entity*>(aMsg.GetData()))
	{
		if (auto* sceneTransition = entity->GetComponent<SceneTransitionComponent>())
		{
			//PostMaster::GetInstance().SendMessage({ eMessage::TransitionToScene, sceneTransition->SceneType }); // Maybe pass in json (or blueprint to scene)??
		}
	}

	//std::cout << "Change scene...\n";
}

void SceneTransitionSystem::Update(float aDeltaTime)
{
}