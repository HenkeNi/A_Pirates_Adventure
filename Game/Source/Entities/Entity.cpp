#include "Pch.h"
#include "Entity.h"
#include "Base/ComponentBase.h"


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

Entity& Entity::operator=(Entity&& anEntity) noexcept
{
	m_components = anEntity.m_components;
	m_ID = anEntity.m_ID;

	anEntity.m_components.clear();

	return *this;
}

unsigned Entity::GetID() const
{
	return m_ID;
}

void Entity::AddComponent(ComponentBase* aComponent)
{
	assert(aComponent && "Error: trying to add a nullptr!");

	auto key = std::type_index(typeid(*aComponent));
	
	if (m_components.find(key) == m_components.end())
	{
		m_components.insert({ key, aComponent });
	}
}

unsigned Entity::GenerateID() const
{
	static unsigned id = 0;
	return ++id;
}

void Entity::OnDestroy()
{
	// remove components...
}