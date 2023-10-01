#pragma once
#include "Entity.h"
#include "EntityFactory.h"

namespace Registration
{
	void RegisterComponents();
}

class EntityManager
{
public:
	EntityManager();
	~EntityManager();

	// static void LoadBlueprints(const std::string& aFilePath);

	Entity* CreateResources(const std::string& aType);
	Entity* Find(unsigned anID);					// Rename GetEntity?

	template <typename... Components>
	std::vector<Entity*> FindAllWithComponents();

	void Destroy(unsigned anID);
	void DestroyAll();

	static EntityFactory& GetFactory();		// replace with freiend function?

private:
	friend void Registration::RegisterComponents();

	static EntityFactory	s_entityFactory;

	std::vector<Entity>		m_entities;
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