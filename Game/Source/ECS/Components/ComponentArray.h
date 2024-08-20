#pragma once
#include "ECSTypes.h"


class IComponentArray
{
public:
	virtual ~IComponentArray() = default;
	virtual void RemoveComponent(Entity entity) = 0;	
};

template <typename T>
class ComponentArray : public IComponentArray
{
public:
	ComponentArray();

	void AddComponent(Entity entity, T component);
	void RemoveComponent(Entity entity) override;
	
	const std::vector<T>& GetComponents() const;
	std::vector<T>& GetComponents();

	const T* GetComponent(Entity entity) const;
	T*	GetComponent(Entity entity);

	bool HasComponent(Entity entity) const;

private:
	std::unordered_map<Entity, Index> m_entityToIndexMap;
	std::unordered_map<Index, Entity> m_indexToEntityMap;
	
	// TODO; store "read" and "write" components separately (for multi threading system) 
	std::vector<T> m_components;
};

#pragma region Method_Definitions

template<typename T>
ComponentArray<T>::ComponentArray()
{
	m_components.reserve(MaxEntities);
}

template<typename T>
void ComponentArray<T>::AddComponent(Entity entity, T component)
{
	assert(!HasComponent(entity) && "[ComponentArray::AddComponent] - ERROR: Entity already exist!");

	// make sure dont exceed max amount... (return bool?)

	std::size_t index = m_components.size();

	m_entityToIndexMap.insert_or_assign(entity, index);
	m_indexToEntityMap.insert_or_assign(index, entity);

	m_components.push_back(component);
}

template<typename T>
void ComponentArray<T>::RemoveComponent(Entity entity)
{
	if (!HasComponent(entity))
		return;

	std::size_t lastIndex = m_components.size() - 1;
	std::size_t indexToRemove = m_entityToIndexMap[entity];

	if (indexToRemove != lastIndex)
	{
		m_components[indexToRemove] = m_components[lastIndex];
		//std::swap(m_components[indexToRemove], m_components[lastIndex]);
	}

	//T* removed = m_components[lastIndex];
	m_components.pop_back();

	Entity lastEntity = m_indexToEntityMap[lastIndex];

	// update mapping of (previously) last entity
	m_entityToIndexMap[lastEntity] = indexToRemove;
	m_indexToEntityMap[indexToRemove] = lastEntity;

	m_entityToIndexMap.erase(entity);
	m_indexToEntityMap.erase(lastIndex);

	// --m_currentSize;

	//return removed;
}

template<typename T>
const std::vector<T>& ComponentArray<T>::GetComponents() const
{
	return m_components;
}

template<typename T>
std::vector<T>& ComponentArray<T>::GetComponents()
{
	return m_components;
}

template<typename T>
const T* ComponentArray<T>::GetComponent(Entity entity) const
{
	T* component = nullptr;

	if (HasComponent(entity))
	{
		std::size_t index = m_entityToIndexMap.at(entity);
		component = &m_components[index];
	}

	return component;
}

template<typename T>
T* ComponentArray<T>::GetComponent(Entity entity)
{
	T* component = nullptr;

	if (HasComponent(entity))
	{
		std::size_t index = m_entityToIndexMap.at(entity);
		component = &m_components[index];
	}

	return component;
}

template<typename T>
bool ComponentArray<T>::HasComponent(Entity entity) const
{
	bool contains = m_entityToIndexMap.contains(entity);
	return contains;
}

#pragma endregion Method_Definitions