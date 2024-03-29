#include "Pch.h"
#include "AttackState.h"
#include "Entities/Entity.h"
#include "Components/Gameplay/GameplayComponents.h"


void AttackState::Init()
{
}

void AttackState::Update(Entity* entity)
{
	/*if (auto* characterStateComponent = entity->GetComponent<CharacterStateComponent>())
	{
		if (characterStateComponent->IsAttacking)
			return;

		characterStateComponent->IsAttacking = true;
		PostMaster::GetInstance().SendMessage({ eMessage::EnemyAttacked, entity });
	}*/
}

void AttackState::OnEnter()
{
}

void AttackState::OnExit()
{
}
