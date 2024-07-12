#pragma once
#include "Constants.h"

using Entity = int; // Include Entity.h instead?
using Index = std::size_t;

class Component;

class IComponentArray
{
public:
	virtual ~IComponentArray() = default;

	virtual void			 AddComponent(Entity entity, Component* component)	= 0;
	virtual Component*		 RemoveComponent(Entity entity)						= 0;

	virtual const Component* GetComponent(Entity entity)				  const = 0;
	virtual Component*		 GetComponent(Entity entity)						= 0;
};

template <typename T>
class ComponentArray : public IComponentArray
{
public:

	void	 AddComponent(Entity entity, T* component)	override;
	T*		 RemoveComponent(Entity entity)				override;
	
	const T* GetComponent(Entity entity)		  const override;
	T*		 GetComponent(Entity entity)				override;

	bool	 HasComponent(Entity entity)				   const;

private:
	std::unordered_map<Entity, Index> m_entityToIndexMap;
	std::unordered_map<Index, Entity> m_indexToEntityMap;

	std::array<T*, Constants::MaxEntities> m_components;
	std::size_t m_currentSize;
};

#pragma region Method_Definitions

template<typename T>
inline void ComponentArray<T>::AddComponent(Entity entity, T* component)
{
	assert(!HasComponent(entity) && "ERROR: entity already exist");

	std::size_t index = m_currentSize;

	m_entityToIndexMap.insert_or_assign(entity, index);
	m_indexToEntityMap.insert_or_assign(index, entity);

	m_components[index] = component;
	++m_currentSize;
}

template<typename T>
inline T* ComponentArray<T>::RemoveComponent(Entity entity)
{
	assert(HasComponent(entity) && "ERROR: entity doesn't exist");

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
inline const T* ComponentArray<T>::GetComponent(Entity entity) const
{
	assert(HasComponent(entity) && "ERROR: failed to retrieve component for entity");

	std::size_t index = m_entityToIndexMap.at(entity);
	const T* component = m_components[index];

	return component;
}

template<typename T>
inline T* ComponentArray<T>::GetComponent(Entity entity)
{
	assert(HasComponent(entity) && "ERROR: failed to retrieve component for entity");

	std::size_t index = m_entityToIndexMap.at(entity);
	T* component = m_components[index];

	return component;
}

template<typename T>
inline bool ComponentArray<T>::HasComponent(Entity entity) const
{
	bool contains = m_entityToIndexMap.contains(entity);
	return contains;
}

#pragma endregion Method_Definitions