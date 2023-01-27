#include "Pch.h"
#include "Component.h"


Component::Component(GameObject* anOwner)
	: m_owner{ anOwner }, m_isActive{ true }
{
}

void Component::SetIsActive(bool shouldActivate)
{
	shouldActivate ? OnActivate() : OnDeactivate();
	m_isActive = shouldActivate;
}

void Component::SetOwner(GameObject* anOwner)
{
	m_owner = anOwner;
}

bool Component::IsActive() const
{
	return m_isActive;
}