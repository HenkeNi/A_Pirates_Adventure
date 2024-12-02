#include "Pch.h"
#include "StateSystem.h"
#include "Components/Gameplay/GameplayComponents.h"
#include "ECS.h"


// Listen to "attack event"? and finsihed attack event?

void StateSystem::Update(float deltaTime)
{
	for (Entity entity : m_ecs->FindEntities(m_signatures["State"]))
	{

		// check velocity => update idle state. etc

	}
}

void StateSystem::SetSignature()
{
	m_signatures.insert({ "State", m_ecs->GetSignature<StateComponent>() });
}