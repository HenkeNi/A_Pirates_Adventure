#include "Pch.h"
#include "SceneTransitionSystem.h"
#include "Entities/Entity.h"
#include "Entities/EntityManager.h"
#include "Components/Core/CoreComponents.h"

SceneTransitionSystem::SceneTransitionSystem()
{
	PostMaster::GetInstance().Subscribe(eMessage::TriggerActivated, this); // add ability to subscribe to multiple events!
	PostMaster::GetInstance().Subscribe(eMessage::ButtonActivated, this);
	PostMaster::GetInstance().Subscribe(eMessage::TimerFinished, this);
}

SceneTransitionSystem::~SceneTransitionSystem()
{
	PostMaster::GetInstance().Unsubscribe(eMessage::TriggerActivated, this);
	PostMaster::GetInstance().Unsubscribe(eMessage::ButtonActivated, this);
	PostMaster::GetInstance().Unsubscribe(eMessage::TimerFinished, this);
}

void SceneTransitionSystem::Receive(Message& message) // Psas trigger?? check if have scen transition componennt
{
	auto* entity = std::any_cast<Entity*>(message.GetData());

	if (!entity || !entity->HasComponent<SceneTransitionComponent>())
		return;

	auto* sceneTransitionComponent = entity->GetComponent<SceneTransitionComponent>();

	sceneTransitionComponent->ShouldTransition = true;

	/*if (sceneTransitionComponent->ShouldPush)
		PostMaster::GetInstance().SendMessage({ eMessage::TransitionToScene, sceneTransitionComponent->SceneType });
	else
		PostMaster::GetInstance().SendMessage({ eMessage::RemoveScene, sceneTransitionComponent->SceneType });*/

	// If behind current scene pop, else push/swap?!
}

void SceneTransitionSystem::Update(float deltaTime)
{
	assert(m_entityManager && "ERROR: EntityManager is nullptr!");

	auto entities = m_entityManager->FindAll<SceneTransitionComponent>();
	for (const auto& entity : entities)
	{
		auto* sceneTransitionComponent = entity->GetComponent<SceneTransitionComponent>();
		if (sceneTransitionComponent->ShouldTransition)
		{
			if (sceneTransitionComponent->ShouldPush)
				PostMaster::GetInstance().SendMessage({ eMessage::TransitionToScene, sceneTransitionComponent->SceneType });
			else
				PostMaster::GetInstance().SendMessage({ eMessage::RemoveScene, sceneTransitionComponent->SceneType });
		
			break;
		}
	}

}