#pragma once
//#include "Entities/EntityManager.h"
// #include "Systems/SystemManager.h"

class EntityManager;
class EntityFactory;
class SystemManager;

class ECS
{
public:
	void Init();
	void Shutdown();
	
	void AddSystems(const std::vector<std::string>& systems);
	//void AddEntities()

	inline const EntityManager& GetEntityMananger() const { return *m_entityManager; }

	inline const EntityFactory& GetEntityFactory() const { return *m_entityFactory; }

	inline const SystemManager& GetSystemManager() const { return *m_systemManager; }

	inline EntityManager& GetEntityManager() { return *m_entityManager; }

	inline EntityFactory& GetEntityFactory() { return *m_entityFactory; }

	inline SystemManager& GetSystemManager() { return *m_systemManager; }
	
private:
	EntityManager* m_entityManager; // FIX!!!
	EntityFactory* m_entityFactory;

	SystemManager* m_systemManager;
};

