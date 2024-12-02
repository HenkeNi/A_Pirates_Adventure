#include "Pch.h"
#include "SceneTransitionSystem.h"
#include "ECS.h"
#include "Components/Core/CoreComponents.h"


SceneTransitionSystem::SceneTransitionSystem()
{
	// Todo, fix tihs... ?
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
	assert(m_ecs && "[SceneTransitionSystem - ERROR]: ECS is not initialized!");

	auto entity = std::any_cast<Entity>(message.GetData());

	auto* sceneTransitionComponent = m_ecs->GetComponent<SceneTransitionComponent>(entity);
	if (!sceneTransitionComponent)
		return;

	sceneTransitionComponent->ShouldTransition = true;
}

void SceneTransitionSystem::Update(float deltaTime)
{
	assert(m_ecs && "[SceneTransitionSystem - ERROR]: ECS is not initialized!");

	auto entities = m_ecs->FindEntities(m_signatures["SceneTransitioners"]);
	for (const auto& entity : entities)
	{
		auto* sceneTransitionComponent = m_ecs->GetComponent<SceneTransitionComponent>(entity);
		if (sceneTransitionComponent->ShouldTransition)
		{
			PostMaster::GetInstance().SendMessage({ eMessage::TransitionToScene, sceneTransitionComponent->SceneType });
			/*if (sceneTransitionComponent->ShouldPush)
			else
				PostMaster::GetInstance().SendMessage({ eMessage::RemoveScene, sceneTransitionComponent->SceneType });
			*/
			sceneTransitionComponent->ShouldTransition = false; // FIX!! why is this needed??

			break;
		}
	}

}

void SceneTransitionSystem::SetSignature()
{
	m_signatures.insert({ "SceneTransitioners", m_ecs->GetSignature<SceneTransitionComponent>() });
}