#include "Pch.h"
#include "EntityManager.h"


EntityManager::EntityManager()
{
	m_active.reserve(MaxEntities);

	for (std::size_t i = 0; i < MaxEntities; ++i)
	{
		m_available.push(i);
	}
}

Entity EntityManager::Create()
{
	assert(m_available.size() > 0 && "[EntityManager - ERROR]: Maximum entity capacity reached!");

	Entity entity = m_available.front();
	m_available.pop();

	m_active.push_back(entity);
	return entity;
}

void EntityManager::Destroy(Entity entity)
{
	assert(entity < MaxEntities && "[EntityManager - ERROR]: Entity out of range.");

	m_available.push(entity);
	m_signatures[entity].reset();
	
	m_active.erase(std::remove(m_active.begin(), m_active.end(), entity));
}

void EntityManager::DestroyAll()
{
	for (Entity entity : m_active)
	{
		m_available.push(entity);
		m_signatures[entity].reset();
	}

	m_active.clear();
}

std::vector<Entity> EntityManager::GetEntities(const Signature& signature) const
{
	std::vector<Entity> entities;

	std::copy_if(m_active.begin(), m_active.end(), std::back_inserter(entities), [&](Entity entity)
		{ 
			return (m_signatures[entity] & signature) == signature;

			//return m_signatures[entity] == signature;
		});

	return entities;
}

std::optional<Entity> EntityManager::GetEntity(const Signature& signature) const
{
	auto itr = std::find_if(m_active.begin(), m_active.end(), [&](Entity entity) 
		{
			return (m_signatures[entity] & signature) == signature;

		});

	if (itr != m_active.end())
		return *itr;

	return std::nullopt;
}

void EntityManager::SetSignature(Entity entity, const Signature& signature)
{
	assert(entity < MaxEntities && "[EntityManager - ERROR]: Entity out of range.");

	m_signatures[entity] = signature;
}

Signature EntityManager::GetSignature(Entity entity) const
{
	assert(entity < MaxEntities && "[EntityManager - ERROR]: Entity out of range."); // asser active?

	return m_signatures[entity];
}