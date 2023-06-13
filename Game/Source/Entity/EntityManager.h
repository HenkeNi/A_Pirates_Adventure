#pragma once
#include "Entity.h"

class EntityManager
{
public:
	EntityManager();
	~EntityManager();

	void	Add(Entity anEntity);	// maybe remove later

	Entity* Create(const std::string& aType);
	Entity* Find(unsigned anID);					// Rename GetEntity?

	template <typename... Components>
	std::vector<Entity*> FindAllWithComponents();



	void Destroy(unsigned anID);
	void DestroyAll();

private:
	// EntityFactory? or ComponentFactory?

	std::vector<Entity> m_entities;
	// std::unordered_map<eLayer, std::vector<Entity>> m_layeredEntities;

};

#pragma region Method_Definitions

template <typename... Components>
std::vector<Entity*> EntityManager::FindAllWithComponents()
{
	std::vector<Entity*> found;

	for (auto& entity : m_entities)
	{
		if (entity.HasComponents<Components...>())
			found.push_back(&entity);
	}
	return found;
}

#pragma endregion Method_Definitions