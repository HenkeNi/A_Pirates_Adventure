#include "Pch.h"
#include "EntityManager.h"

namespace Hi_Engine
{
	EntityManager::EntityManager()
		: m_signatures{}, m_versions{}
	{
	}

	void EntityManager::Initialize()
	{
		//m_active.reserve(MaxEntities);

		for (uint32_t i = 0; i < MaxEntities; ++i)
		{
			m_available.push(i);
		}
	}

	std::optional<Entity> EntityManager::Create()
	{
		if (!m_available.empty())
		{
			EntityID id = m_available.front();
			m_available.pop();

			//m_alive[entity] = true;
			
			m_alive.Emplace(id, id, m_versions[id]);
			return Entity{ id, m_versions[id] };
		}

		Logger::LogWarning("[EntityManager::Create] - Maximum entity capacity reached!");
		return std::nullopt;
	}
	
	bool EntityManager::Destroy(const Entity& entity)
	{
		if (IsAlive(entity)) // valid check entiy as well?
		{
			m_available.push(entity.ID);
			
			m_signatures[entity.ID].reset();
			++m_versions[entity.ID];

			//m_alive[false];

			m_alive.Remove(entity.ID);
			return true;

			//auto it = std::find(m_active.begin(), m_active.end(), entity);
			//if (it != m_active.end())
			//{
			//	std::iter_swap(it, m_active.end() - 1);
			//}

			// m_active.erase(std::remove(m_active.begin(), m_active.end(), entity), m_active.end()); // circular delete..
		}
		else
		{
			Logger::LogError("[EntityManager::Destroy] - Invalid Entity " + std::to_string(entity.ID) + " !");
			return false;
		}
	}

	void EntityManager::DestroyAll()
	{
		for (auto& [id, version] : m_alive) // call destroy function instead? or not?
		{
			//m_alive[entity] = false;

			m_available.push(id);
			m_signatures[id].reset();
			++m_versions[id];
		}

		m_alive.Clear();
	}

	std::vector<EntityID> EntityManager::GetEntities(Signature signature) const // Return id or entities?
	{
		std::vector<EntityID> matchingIDs;

		for (const auto& entity : m_alive)
		{
			if ((m_signatures[entity.ID] & signature) == signature)
				matchingIDs.emplace_back(entity.ID);
		}

		return matchingIDs;

		//std::vector<EntityID> matchingIDs(m_alive.Size()); // TODO; store id insteadD!
		//auto it = std::copy_if(std::execution::seq, m_alive.begin(), m_alive.end(), matchingIDs.begin(), [&](const Entity& entity) // TODO: make sure works with sparse set..
		//	{
		//		return (m_signatures[entity.ID] & signature) == signature;
		//	});

		//matchingIDs.resize(std::distance(matchingIDs.begin(), it));
		//return matchingIDs;
	}
	
	std::optional<Signature> EntityManager::GetSignature(EntityID id) const
	{
		return m_signatures[id];
	}

	void EntityManager::SetSignature(const Entity& entity, Signature signature)
	{
		assert(IsValidEntity(entity) && "[EntityManager - ERROR]: Entity out of range.");

		if (IsAlive(entity))
		{
			m_signatures[entity.ID] = signature;
		}
		else
		{
			Logger::LogWarning("[EntityManager::SetSignature] - Invalid Entity");
		}
	}

	bool EntityManager::IsValidEntity(const Entity& entity) const
	{
		return entity.ID < MaxEntities && entity.ID >= 0;
	}

	bool EntityManager::IsAlive(const Entity& entity) const
	{
		return m_versions[entity.ID] == entity.Version; // get from sparse set as well???
	}
}