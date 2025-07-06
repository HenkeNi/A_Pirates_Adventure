#include "Pch.h"
#include "EntityManager.h"

namespace Hi_Engine
{
	EntityManager::EntityManager()
		: m_signatures{}, m_versions{}
	{
		InitializeEntityIDs();
	}

	std::optional<Entity> EntityManager::Create() noexcept
	{
		if (!m_available.empty())
		{
			const EntityID id = m_available.front();
			m_available.pop();
			
			m_alive.Emplace(id, id, m_versions[id]);
			return Entity{ id, m_versions[id] };
		}

		Logger::LogWarning("[EntityManager] Maximum entity capacity reached!");
		return std::nullopt;
	}
	
	bool EntityManager::Destroy(const Entity& entity) noexcept
	{
		if (!IsAlive(entity))
		{
			Logger::LogError("[EntityManager] Invalid Entity " + std::to_string(entity.ID) + "!");
			return false;
		}

		m_available.push(entity.ID);
		m_signatures[entity.ID].reset();
		++m_versions[entity.ID];
		m_alive.Remove(entity.ID);
		
		return true;
	}

	void EntityManager::DestroyAll() noexcept
	{
		for (const auto& [id, version] : m_alive)
		{
			m_available.push(id);
			m_signatures[id].reset();
			++m_versions[id];
		}

		m_alive.Clear();
	}

	bool EntityManager::IsValidEntity(const Entity& entity) const noexcept
	{
		return entity.ID < MaxEntities && entity.ID >= 0;
	}

	bool EntityManager::IsAlive(const Entity& entity) const noexcept
	{
		return IsValidEntity(entity) && 
			m_alive.Contains(entity.ID) && 
			m_versions[entity.ID] == entity.Version;
	}

	std::optional<Signature> EntityManager::GetSignature(EntityID id) const noexcept
	{
		return m_signatures[id];
	}

	void EntityManager::SetSignature(const Entity& entity, Signature signature)
	{
		if (!IsValidEntity(entity))
		{
			Logger::LogError("[EntityManager] Invalid Entity " + std::to_string(entity.ID) + "!");
			return;
		}

		if (IsAlive(entity))
		{
			m_signatures[entity.ID] = signature;
		}
		else
		{
			Logger::LogWarning("[EntityManager] - Trying to set signature; entity is not alive!");
		}
	}

	std::vector<EntityID> EntityManager::GetEntityIDs(Signature signature) const
	{
		std::vector<EntityID> matchingIDs;

		for (const auto& entity : m_alive)
		{
			if ((m_signatures[entity.ID] & signature) == signature)
				matchingIDs.emplace_back(entity.ID);
		}

		return matchingIDs;
	}

	std::vector<Entity> EntityManager::GetEntities(Signature signature) const
	{
		std::vector<Entity> matchingEntities;

		for (const auto& entity : m_alive)
		{
			if ((m_signatures[entity.ID] & signature) == signature)
				matchingEntities.emplace_back(entity);
		}

		return matchingEntities;
	}

	void EntityManager::InitializeEntityIDs() noexcept
	{
		for (uint32_t i = 0; i < MaxEntities; ++i)
		{
			m_available.push(i);
		}
	}
}