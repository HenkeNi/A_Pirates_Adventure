#pragma once
#include "ComponentArray.h"
#include "ComponentPool.h"
#include "ECSTypes.h"
#include <assert.h>

class IComponentArray;

class ComponentManager
{
public:
	ComponentManager();

	template <typename T>
	void RegisterComponent(const char* name);

	template <typename T>
	T* AddComponent(Entity entity);

	template <typename T>
	void RemoveComponent(Entity entity);

	void RemoveAllComponents(Entity entity);

	template <typename T>
	std::vector<const T*> GetComponents() const;

	template <typename T>
	std::vector<T*> GetComponents();

	template <typename T>
	const T* GetComponent(Entity entity) const;

	template <typename T>
	T* GetComponent(Entity entity);

	template <typename T>
	ComponentType GetComponentType() const;

	template <typename... T>
	std::vector<ComponentType> GetComponentTypes() const;

private:
	//template <typename T>
	//IComponentArray& GetComponentArray();

	template <typename T>
	const IComponentArray* FindComponentArray() const; // Fix!?

	template <typename T>
	IComponentArray* FindComponentArray();

	template <typename T>
	ComponentPool<T>& GetComponentPool();

	ComponentArrays m_componentArrays;
	ComponentPools  m_componentPools;

	ComponentTypes m_componentTypes;
	ComponentType m_nextComponentType;
};

#pragma region Method_Definitions

template <typename T>
inline void ComponentManager::RegisterComponent(const char* name)
{
	auto type = std::type_index(typeid(T));

	assert(m_componentArrays.find(type) == m_componentArrays.end() && "[ComponentManager - ERROR]: Component type already registered!");

	m_componentArrays.insert({ type, std::make_unique<ComponentArray<T>>() });
	m_componentPools.insert({ type, std::make_unique<ComponentPool<T>>() });
	m_componentTypes.insert({ type, m_nextComponentType });

	++m_nextComponentType;
}

template<typename T>
inline T* ComponentManager::AddComponent(Entity entity)
{
	//T* component = Hi_Engine::MemoryPool<T>::GetInstance().GetResource();
	
	void* component = GetComponentPool<T>().GetResource();
	T* tComponent = static_cast<T*>(component);

	if (auto* componentArray = FindComponentArray<T>())
	{
		componentArray->AddComponent(entity, tComponent);
	}

	return tComponent;
}

template<typename T>
inline void ComponentManager::RemoveComponent(Entity entity)
{
	if (auto* componentArray = FindComponentArray<T>())
	{
		if (void* removed = componentArray->RemoveComponent(entity))
		{
			//T* component = static_cast<T*>(removed);

			GetComponentPool<T>().ReturnResource(removed);
			//Hi_Engine::MemoryPool<T>::GetInstance().ReturnResource(component);
		}
	}
}

template<typename T>
inline std::vector<const T*> ComponentManager::GetComponents() const
{
	std::vector<const T*> components;
	if (auto* componentArray = FindComponentArray<T>())
	{
		return componentArray->GetComponents();
	}

	return components;
}

template<typename T>
inline std::vector<T*> ComponentManager::GetComponents()
{
	std::vector<T*> components;
	if (auto* componentArray = FindComponentArray<T>())
	{
		return componentArray->GetComponents();
	}

	return components;
}

template <typename T>
inline const T* ComponentManager::GetComponent(Entity entity) const
{
	T* component = nullptr;
	if (auto* componentArray = FindComponentArray<T>())
	{
		if (auto* comp = componentArray->GetComponent(entity))
			component = static_cast<T*>(comp);
	}

	return component;
}

template <typename T>
inline T* ComponentManager::GetComponent(Entity entity)
{
	T* component = nullptr;

	if (auto* componentArray = FindComponentArray<T>())
	{
		if (auto* comp = componentArray->GetComponent(entity))
			component = static_cast<T*>(comp);
	}

	return component;
}

template<typename T>
inline ComponentType ComponentManager::GetComponentType() const
{
	auto type = std::type_index(typeid(T));
	auto iterator = m_componentTypes.find(type);

	if (iterator != m_componentTypes.end())
	{
		return iterator->second;
	}

	assert(false && "[ERROR - ComponentManager]: ComponentType not registered!");
	return ComponentType();
}

template<typename ...T>
inline std::vector<ComponentType> ComponentManager::GetComponentTypes() const
{
	std::vector<ComponentType> componentTypes;
	(componentTypes.push_back(GetComponentType<T>()), ...);

	return componentTypes;
}

template<typename T>
inline const IComponentArray* ComponentManager::FindComponentArray() const
{
	auto type = std::type_index(typeid(T));

	auto iterator = m_componentArrays.find(type);
	if (iterator != m_componentArrays.end())
	{
		return iterator->second.get();
	}

	assert(false && "[ERROR - ComponentManager]: Component Array not registered!");

	return nullptr;
}

template <typename T>
IComponentArray* ComponentManager::FindComponentArray()
{
	auto type = std::type_index(typeid(T));

	auto iterator = m_componentArrays.find(type);
	if (iterator != m_componentArrays.end())
	{
		return iterator->second.get();
	}

	assert(false && "[ComponentManager - ERROR]: Component Array not registered!");

	return nullptr;
}

template<typename T>
inline ComponentPool<T>& ComponentManager::GetComponentPool()
{
	auto type = std::type_index(typeid(T));

	auto itr = m_componentPools.find(type);
	if (itr == m_componentPools.end())
	{
		auto componentPool = std::make_unique<ComponentPool<T>>();
		m_componentPools.insert({ type, std::move(componentPool) });

		return static_cast<ComponentPool<T>&>(*m_componentPools[type]);
	}

	return static_cast<ComponentPool<T>&>(*itr->second);
}

#pragma endregion Method_Definitions