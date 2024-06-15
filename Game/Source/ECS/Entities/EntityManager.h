#pragma once
#include "Entity.h"
#include "EntityFactory.h"


class EntityManager
{
public:
	EntityManager();
	~EntityManager();

	Entity* Create(const std::string& type);
	Entity* Find(unsigned id);

	template <typename... Components>
	std::vector<Entity*> FindAll();

	template <typename... Components>
	Entity* FindFirst();

	void Destroy(unsigned id);
	void DestroyAll();

	EntityFactory& GetFactory();
	 
private:
	EntityFactory	s_entityFactory;
	std::vector<Entity>		m_entities;			// std::unordered_map<eLayer, std::vector<Entity>> m_layeredEntities;
};

#pragma region Method_Definitions

template <typename... Components>
std::vector<Entity*> EntityManager::FindAll()
{
	std::vector<Entity*> found;

	for (auto& entity : m_entities)
	{
		if (entity.HasComponents<Components...>())
			found.push_back(&entity);
	}
	return found;
}

template <typename... Components>
Entity* EntityManager::FindFirst()
{
	for (auto& entity : m_entities)
	{
		if (entity.HasComponents<Components...>())
			return &entity;
	}

	return nullptr;
}

#pragma endregion Method_Definitions