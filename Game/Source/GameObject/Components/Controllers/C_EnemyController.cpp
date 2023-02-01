#include "Pch.h"
#include "C_EnemyController.h"



C_EnemyController::C_EnemyController(GameObject* anOwner)
	: Component{ anOwner }
{
}

void C_EnemyController::HandleMessage(eCompMessage aMessageType, const std::any& someData)
{
}

void C_EnemyController::Update(float aDeltaTime)
{
}
