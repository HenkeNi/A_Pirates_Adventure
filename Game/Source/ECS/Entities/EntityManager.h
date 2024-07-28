#pragma once
#include "ECSTypes.h"


class EntityManager
{
public:
	EntityManager();

	Entity Create();
	void Destroy(Entity entity);
	void DestroyAll();

	inline const std::vector<Entity>& GetActiveEntities() const { return m_active; }

	std::vector<Entity> GetEntities(const Signature& signature) const;
	std::optional<Entity> GetEntity(const Signature& signature) const;

	void SetSignature(Entity entity, const Signature& signature);
	Signature GetSignature(Entity entity);

private:
	std::queue<Entity> m_available;
	std::vector<Entity> m_active;

	std::array<Signature, MaxEntities> m_signatures;
};



// class EntityFactory;

//class EntityManager
//{
//public:
//	EntityManager(EntityFactory& factory);
//	~EntityManager();
//
//	Entity* Create(const std::string& type);
//	Entity* Find(unsigned id);
//
//	template <typename... Components>
//	std::vector<Entity*> FindAll();
//
//	template <typename... Components>
//	Entity* FindFirst();
//
//	void Destroy(unsigned id);
//	void DestroyAll();
//
//	template <typename... Components>
//	void DestroySelected();
//	 
//private:
//	EntityFactory& m_entityFactory; // be able to swap out factories?
//	std::vector<Entity> m_entities;			// std::unordered_map<eLayer, std::vector<Entity>> m_layeredEntities;
//};
//
//#pragma region Method_Definitions
//
//template <typename... Components>
//std::vector<Entity*> EntityManager::FindAll()
//{
//	std::vector<Entity*> found;
//
//	for (auto& entity : m_entities)
//	{
//		if (entity.HasComponents<Components...>())
//			found.push_back(&entity);
//	}
//	return found;
//}
//
//template <typename... Components>
//Entity* EntityManager::FindFirst()
//{
//	for (auto& entity : m_entities)
//	{
//		if (entity.HasComponents<Components...>())
//			return &entity;
//	}
//
//	return nullptr;
//}
//
//template <typename... Components>
//void EntityManager::DestroySelected()
//{
//	auto end = std::remove_if(m_entities.begin(), m_entities.end(),
//		[&](const Entity& entity)
//		{
//			return entity.HasComponents<Components...>();
//		});
//	
//	m_entities.erase(end, m_entities.end());
//}
//
//#pragma endregion Method_Definitions