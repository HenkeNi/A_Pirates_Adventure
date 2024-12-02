#include "Pch.h"
#include "StateTransitionSystem.h"
#include "Components/AI/AIComponents.h"
#include "Components/Gameplay/GameplayComponents.h"
#include "Components/Core/CoreComponents.h"


class TransitionManager
{
public:

private:
	// static... typeid Component => 
};


StateTransitionSystem::StateTransitionSystem()
{
}

StateTransitionSystem::~StateTransitionSystem()
{
}

void StateTransitionSystem::Update(float deltaTime)
{
	assert(m_entityManager && "ERROR: EntityManager is nullptr!");

	auto idleEntities = m_entityManager->FindAll<IdleComponent>();
	for (auto* entity : idleEntities)
	{
		// if (entity->HasComponent<DeathComponent>())
		if (ShouldTransitionToAlert(entity))
		{
			entity->RemoveComponent<IdleComponent>();

			//auto* alertComponent = m_entityManager->GetFactory().GetCompFactory().Build("alert");
			//entity->AddComponent(alertComponent); // maybe component factory should be its own class?

			std::cout << "Alerted\n";
 		}
		else if (ShouldTransitionToPatrol(entity))
		{
			std::cout << "Patrol\n";
		}
	}

	auto alertEntities = m_entityManager->FindAll<AlertComponent>();
	for (const auto* entity : alertEntities)
	{
		if (ShouldTransitionToChase(entity))
		{
			std::cout << "Alert\n";
		}
		else if (ShouldTransitionToFlee(entity))
		{

		}
		else if (ShouldTransitionToPatrol(entity))
		{

		}
	}

	auto patrolEntities = m_entityManager->FindAll<PatrolComponent>();
	for (const auto* entity : patrolEntities)
	{
		if (ShouldTransitionToAlert(entity))
		{
			std::cout << "Alert\n";
		}
		else if (ShouldTransitionToIdle(entity))
		{

		}
	}

	/*auto chasingEntities = m_entityManager->FindAll<ChaseComponent>();
	for (const auto* entity : chasingEntities)
	{
		if (ShouldTransitionToAttack(entity))
		{
			std::cout << "Alert\n";
		}
		else if (ShouldTransitionToAlert(entity))
		{

		}
	}

	auto fleeingEntities = m_entityManager->FindAll<FleeComponent>();
	for (const auto* entity : fleeingEntities)
	{
		if (ShouldTransitionToIdle(entity))
		{
			std::cout << "Alert\n";
		}
		else if (ShouldTransitionToAlert(entity))
		{

		}
	}
	
	auto attackingEntities = m_entityManager->FindAll<AttackComponent>();
	for (const auto* entity : attackingEntities)
	{
		if (ShouldTransitionToIdle(entity))
		{
			std::cout << "Alert\n";
		}
		else if (ShouldTransitionToChase(entity))
		{

		}
		else if (ShouldTransitionToAlert(entity))
		{

		}
	}*/

}

//bool StateTransitionSystem::IsSuspicious(const Entity* entity) const
//{
//	// TODO; check for explosions, or loud noises??
//
//	if (auto* blackboardComponent = entity->GetComponent<BlackboardComponent>())
//	{
//		auto* transformComponent = entity->GetComponent<TransformComponent>();
//		auto* attributeComponent = entity->GetComponent<AttributesComponent>();
//
//		auto currentPosition = transformComponent->CurrentPos;
//		auto targetPosition = blackboardComponent->PlayerPosition; // Todo; store "target" instead of player? position might cause issues since defaults to 0
//
//		return currentPosition.DistanceTo(targetPosition) < Tile::Size * attributeComponent->Perception; // have some base range as well?
//	}
//
//	return false;
//}

bool StateTransitionSystem::ShouldTransitionToIdle(const Entity* entity) const
{
	return true;
}

bool StateTransitionSystem::ShouldTransitionToAlert(const Entity* entity) const
{
	if (auto* blackboardComponent = entity->GetComponent<BlackboardComponent>())
	{
		auto* transformComponent = entity->GetComponent<TransformComponent>();
		auto* attributeComponent = entity->GetComponent<AttributesComponent>();

		auto currentPosition = transformComponent->CurrentPos;
		auto targetPosition = blackboardComponent->PlayerPosition; // Todo; store "target" instead of player? position might cause issues since defaults to 0

		return currentPosition.DistanceTo(targetPosition) < Tile::Size * attributeComponent->Perception; // have some base range as well?
	}

	return false;
}

bool StateTransitionSystem::ShouldTransitionToPatrol(const Entity* entity) const
{
	// if current state is idle
	if (auto* idleComponent = entity->GetComponent<IdleComponent>())
	{
		return idleComponent->Timestamp + idleComponent->Duration > Hi_Engine::Engine::GetTimer().GetTotalTime();
	}

	return true;
}

bool StateTransitionSystem::ShouldTransitionToChase(const Entity* entity) const
{
	return false;
}

bool StateTransitionSystem::ShouldTransitionToFlee(const Entity* entity) const
{
	return false;
}

bool StateTransitionSystem::ShouldTransitionToAttack(const Entity* entity) const
{
	auto* personalityComponent = entity->GetComponent<PersonalityComponent>();

	if (!personalityComponent || !personalityComponent->IsAggressive)
		return false;

	if (auto* blackboardComponent = entity->GetComponent<BlackboardComponent>())
	{
		auto* transformComponent = entity->GetComponent<TransformComponent>();
		auto* attributeComponent = entity->GetComponent<AttributesComponent>();

		auto currentPosition = transformComponent->CurrentPos;
		auto targetPosition = blackboardComponent->PlayerPosition;

		return currentPosition.DistanceTo(targetPosition) < Tile::Size * attributeComponent->Perception; // have some base range as well?
	}

	return false;
}
