#include "Pch.h"
#include "Entity.h"
#include "Components/Base/Component.h"

unsigned GenerateID();

Entity::Entity()
	: m_ID{ GenerateID() }
{
	m_components.reserve(16);
}

Entity::Entity(Entity&& anEntity) noexcept
	: m_components{ std::move(anEntity.m_components) }, m_ID{ anEntity.m_ID }
{
	anEntity.m_components.clear();
}

Entity::~Entity()
{
	OnDestroy();
}

Entity& Entity::operator=(Entity&& entity) noexcept
{
	m_components = entity.m_components;
	m_ID = entity.m_ID;

	entity.m_components.clear();

	return *this;
}

unsigned Entity::GetID() const
{
	return m_ID;
}

bool Entity::AddComponent(Component* component)
{
	if (component)
	{
		auto key = std::type_index(typeid(*component));
		if (m_components.find(key) == m_components.end())
		{
			m_components.insert({ key, component });
			return true;
		}
	}
	return false;
}

void Entity::OnDestroy()
{
	// TODO: remove components...
}

unsigned GenerateID()
{
	static unsigned id = 0;
	return ++id;
}