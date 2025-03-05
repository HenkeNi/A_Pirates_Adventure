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

		Logger::LogWarning("[EntityManager::Create] - Maximum entity capacity reached!");
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
			Logger::LogError("[EntityManager::Destroy] - Invalid Entity " + std::to_string(entity) + " !");
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
		std::vector<Entity> entities(m_active.size());

		auto it = std::copy_if(std::execution::seq, m_active.begin(), m_active.end(), entities.begin(), [&](Entity entity)
			{
				return (m_signatures[entity] & signature) == signature;
			});

	 	entities.resize(std::distance(entities.begin(), it));
		return entities;
	}
	
	std::optional<Entity> EntityManager::GetEntity(const Signature& signature) const
	{
		auto it = std::find_if(m_active.begin(), m_active.end(), [&](Entity entity)
			{
				return (m_signatures[entity] & signature) == signature;

			});

		return (it != m_active.end()) ? std::optional<Entity>{*it } : std::nullopt;

	/*	if (it != m_active.end())
			return *it;

		return std::nullopt;*/
	}

	std::optional<Signature> EntityManager::GetSignature(Entity entity) const
	{
		if (IsValidEntity(entity))
		{
			return m_signatures[entity];
		}
		else
		{
			Logger::LogError("[EntityManager::GetSignature] - Invalid Entity!");
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