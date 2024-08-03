#pragma once
#include "ECSTypes.h"


class IComponentArray
{
public:
	virtual ~IComponentArray() = default;
	virtual void* RemoveComponent(Entity entity) = 0;	
};

template <typename T>
class ComponentArray : public IComponentArray
{
public:
	void AddComponent(Entity entity, T* component);
	void* RemoveComponent(Entity entity) override;
	
	std::vector<const T*> GetComponents() const;
	std::vector<T*>	GetComponents();

	const T* GetComponent(Entity entity) const;
	T* GetComponent(Entity entity);

	bool HasComponent(Entity entity) const;

private:
	std::unordered_map<Entity, Index> m_entityToIndexMap;
	std::unordered_map<Index, Entity> m_indexToEntityMap;

	// TODO; store "read" and "write" components separately (for multi threading system) 
	std::array<T*, MaxEntities> m_components;
	std::size_t m_currentSize;
};

#pragma region Method_Definitions

template<typename T>
inline void ComponentArray<T>::AddComponent(Entity entity, T* component)
{
	assert(!HasComponent(entity) && "[ERROR - ComponentArray::AddComponent] - Entity already exist!");

	std::size_t index = m_currentSize;

	m_entityToIndexMap.insert_or_assign(entity, index);
	m_indexToEntityMap.insert_or_assign(index, entity);

	m_components[index] = static_cast<T*>(component);
	++m_currentSize;
}

template<typename T>
inline void* ComponentArray<T>::RemoveComponent(Entity entity)
{
	if (!HasComponent(entity))
		return nullptr;

	std::size_t lastIndex = m_currentSize - 1;
	std::size_t indexToRemove = m_entityToIndexMap[entity];

	if (indexToRemove != lastIndex)
	{
		// overwrite entity to remove with the entity that's last
		//m_components[indexToRemove] = m_components[lastIndex];
		std::swap(m_components[indexToRemove], m_components[lastIndex]);
	}

	T* removed = m_components[lastIndex];

	Entity lastEntity = m_indexToEntityMap[lastIndex];

	// update mapping of (previously) last entity
	m_entityToIndexMap[lastEntity] = indexToRemove;
	m_indexToEntityMap[indexToRemove] = lastEntity;

	m_entityToIndexMap.erase(entity);
	m_indexToEntityMap.erase(lastIndex);

	--m_currentSize;

	return removed;
}

template<typename T>
inline std::vector<const T*> ComponentArray<T>::GetComponents() const
{
	std::vector<const void*> components;

	for (int i = 0; i < m_currentSize; ++i)
	{
		components.push_back(m_components[i]);
	}

	return components;
}

template<typename T>
inline std::vector<T*> ComponentArray<T>::GetComponents()
{
	std::vector<T*> components;

	for (int i = 0; i < m_currentSize; ++i)
	{
		components.push_back(m_components[i]);
	}

	return components;
}

template<typename T>
inline const T* ComponentArray<T>::GetComponent(Entity entity) const
{
	const T* component = nullptr;

	if (HasComponent(entity))
	{
		std::size_t index = m_entityToIndexMap.at(entity);
		component = m_components[index];
	}

	return component;
}

template<typename T>
inline T* ComponentArray<T>::GetComponent(Entity entity)
{
	T* component = nullptr;

	if (HasComponent(entity))
	{
		std::size_t index = m_entityToIndexMap.at(entity);
		component = m_components[index];
	}

	return component;
}

template<typename T>
inline bool ComponentArray<T>::HasComponent(Entity entity) const
{
	bool contains = m_entityToIndexMap.contains(entity);
	return contains;
}

#pragma endregion Method_Definitions