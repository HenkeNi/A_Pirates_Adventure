#include "Pch.h"
#include "Component.h"


Component::Component(GameObject* anOwner)
	: m_owner{ anOwner }
{
}

void Component::SetOwner(GameObject* anOwner)
{
	m_owner = anOwner;
}