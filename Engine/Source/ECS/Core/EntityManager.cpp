#include "Pch.h"
#include "EntityManager.h"

namespace Hi_Engine
{
	void EntityManager::Initialize()
	{
		m_active.reserve(MaxEntities);

		for (std::size_t i = 0; i < MaxEntities; ++i)
		{
			m_available.push(i);
		}
	}

	std::optional<Entity> EntityManager::Create()
	{
		if (!m_available.empty())
		{
			Entity entity = m_available.front();
			m_available.pop();

			m_active.push_back(entity);
			return entity;
		}

		std::cerr << "[EntityManager::Create] - Maximum entity capacity reached!\n";
		return std::nullopt;
	}
	
	void EntityManager::Destroy(Entity entity)
	{
		if (IsValidEntity(entity))
		{
			m_available.push(entity);
			m_signatures[entity].reset();

			m_active.erase(std::remove(m_active.begin(), m_active.end(), entity));
		}
		else
		{
			std::cerr << "[EntityManager::Destroy] - Invalid Entity!\n";
		}
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

	std::optional<Signature> EntityManager::GetSignature(Entity entity) const
	{
		if (IsValidEntity(entity))
		{
			return m_signatures[entity];
		}
		else
		{
			std::cerr << "[EntityManager::GetSignature] - Invalid Entity!\n";
			return std::nullopt;
		}
	}

	void EntityManager::SetSignature(Entity entity, const Signature& signature)
	{
		assert(entity < MaxEntities && "[EntityManager - ERROR]: Entity out of range.");

		m_signatures[entity] = signature;
	}

	bool EntityManager::IsValidEntity(Entity entity) const
	{
		return entity < MaxEntities && entity >= 0;
	}
}