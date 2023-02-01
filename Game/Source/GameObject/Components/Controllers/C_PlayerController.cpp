#include "Pch.h"
#include "C_PlayerController.h"

C_PlayerController::C_PlayerController(GameObject* anOwner)
	: Component{ anOwner }
{
}

void C_PlayerController::HandleMessage(eCompMessage aMessageType, const std::any& someData)
{
}

void C_PlayerController::Update(float aDeltaTime)
{
}
