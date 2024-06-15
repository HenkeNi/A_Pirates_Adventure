#pragma once
//#include "Entities/EntityManager.h"
#include "Systems/SystemManager.h"

class EntityManager;

class ECS
{
public:
	void Init();
	void Shutdown();
	void RegisterSystems(const std::vector<std::string>& systems);

	inline EntityManager& GetEntityManager()
	{
		return *m_entityManager;
	}

	inline const EntityManager& GetEntityMananger() const
	{
		return *m_entityManager;
	}

	inline SystemManager& GetSystemManager() 
	{ 
		return m_systemManager; 
	}

	inline const SystemManager& GetSystemManager() const 
	{ 
		return m_systemManager; 
	}

private:
	EntityManager* m_entityManager; // FIX!!!
	SystemManager m_systemManager;
};

