#include "Pch.h"
#include "C_Collider.h"


C_Collider::C_Collider(GameObject* anOwner)
	: Component{ anOwner }
{
}

bool C_Collider::IsActivated() const
{
	return false;
}