#pragma once
#include "ComponentArray.h"
#include "ComponentPool.h"
#include "ECSTypes.h"
#include <assert.h>


class ComponentManager
{
public:
	ComponentManager();

	template <typename T>
	void RegisterComponent(const char* name);

	void RemoveAllComponents(Entity entity);

	template <typename T>
	void RemoveComponent(Entity entity);

	void SerializeComponents(ComponentRegistry& registry);

	void DeserializeComponents();

	template <typename T>
	void AddComponent(Entity entity);
	//T* AddComponent(Entity entity);

	//template <typename T>
	//std::optional<const std::vector<const T>&> GetComponents() const;
	//std::vector<const T*> GetComponents() const;

	template <typename T>
	const std::vector<T>& GetComponents() const;

	template <typename T>
	std::vector<T>& GetComponents(); // return component array instead?
	//std::vector<T*> GetComponents();

	template <typename T>
	const T* GetComponent(Entity entity) const;

	template <typename T>
	T* GetComponent(Entity entity);

	template <typename... T>
	std::vector<ComponentType> GetComponentTypes() const;

	template <typename T>
	ComponentType GetComponentType() const;

private:
	template <typename T>
	const ComponentArray<T>* FindComponentArray() const;

	template <typename T>
	ComponentArray<T>& GetComponentArray();

	template <typename T>
	ComponentPool<T>& GetComponentPool();

	ComponentArrays m_componentArrays;
	ComponentPools  m_componentPools; // remove?

	ComponentTypes m_componentTypes;
	ComponentType m_nextComponentType;
};

#pragma region Method_Definitions

template <typename T>
void ComponentManager::RegisterComponent(const char* name)
{
	auto type = std::type_index(typeid(T));

	assert(m_componentArrays.find(type) == m_componentArrays.end() && "[ERROR - ComponentManager::RegisterComponent] - Component type already registered!");

	m_componentArrays.insert({ type, std::make_unique<ComponentArray<T>>() });
	m_componentPools.insert({ type, std::make_unique<ComponentPool<T>>() });
	m_componentTypes.insert({ type, m_nextComponentType });

	++m_nextComponentType;
}

template<typename T>
void ComponentManager::RemoveComponent(Entity entity)
{
	GetComponentArray<T>().RemoveComponent(entity);
	//auto& componentArray = GetComponentArray<T>();
	//auto* component = componentArray.RemoveComponent(entity);

	//auto& componentPool = GetComponentPool<T>();
	//componentPool.ReturnResource(component);
}

template<typename T>
void ComponentManager::AddComponent(Entity entity)
{
	GetComponentArray<T>().AddComponent(entity, T{}); // pass in just T??

	//auto& componentPool = GetComponentPool<T>();
	//T* component = componentPool.GetResource();

	//auto& componentArray = GetComponentArray<T>();
	//componentArray.AddComponent(entity, component);

	//return component;
}

//template<typename T>
//inline std::optional<const std::vector<const T>&> ComponentManager::GetComponents() const
//{
//	if (auto* componentArray = FindComponentArray<T>())
//	{
//		return std::optional(componentArray.GetComponents());
//	}
//
//	return std::nullopt;
//}

template <typename T>
const std::vector<T>& ComponentManager::GetComponents() const
{
	return GetComponentArray<T>().GetComponents();
}

template<typename T>
std::vector<T>& ComponentManager::GetComponents()
{
	return GetComponentArray<T>().GetComponents();

	//auto& componentArray = GetComponentArray<T>();
	//std::vector<T*> components = componentArray.GetComponents();
	
	//return components;
}

template <typename T>
const T* ComponentManager::GetComponent(Entity entity) const
{
	const T* component = nullptr;

	if (const auto* componentArray = FindComponentArray<T>())
	{
		component = componentArray.GetComponent(entity);
	}

	return component;
}

template <typename T>
T* ComponentManager::GetComponent(Entity entity)
{
	return GetComponentArray<T>().GetComponent(entity);

	//auto& componentArray = GetComponentArray<T>();
	//T* component = componentArray.GetComponent(entity);

	//return component;
}

template<typename T>
ComponentType ComponentManager::GetComponentType() const
{
	auto type = std::type_index(typeid(T));
	auto iterator = m_componentTypes.find(type);

	if (iterator != m_componentTypes.end())
	{
		return iterator->second;
	}

	assert(false && "[ERROR - ComponentManager::GetComponentType] - ComponentType not registered!");
	return ComponentType();
}

template<typename ...T>
std::vector<ComponentType> ComponentManager::GetComponentTypes() const
{
	std::vector<ComponentType> componentTypes;
	(componentTypes.push_back(GetComponentType<T>()), ...);

	return componentTypes;
}

template<typename T>
const ComponentArray<T>* ComponentManager::FindComponentArray() const
{
	auto type = std::type_index(typeid(T));

	auto iterator = m_componentArrays.find(type);
	if (iterator != m_componentArrays.end())
	{
		return static_cast<ComponentArray<T>*>(iterator->second.get());
	}

	return nullptr;
}

template <typename T>
ComponentArray<T>& ComponentManager::GetComponentArray()
{
	auto type = std::type_index(typeid(T));

	auto iterator = m_componentArrays.find(type);
	if (iterator == m_componentArrays.end())
	{
		auto componentArray = std::make_unique<ComponentArray<T>>();
		m_componentArrays.insert({ type, std::move(componentArray) });

		return static_cast<ComponentArray<T>&>(*m_componentArrays[type]);
	}

	return static_cast<ComponentArray<T>&>(*iterator->second);
}

template<typename T>
ComponentPool<T>& ComponentManager::GetComponentPool()
{
	auto type = std::type_index(typeid(T));

	auto iterator = m_componentPools.find(type);
	if (iterator == m_componentPools.end())
	{
		auto componentPool = std::make_unique<ComponentPool<T>>();
		m_componentPools.insert({ type, std::move(componentPool) });

		return static_cast<ComponentPool<T>&>(*m_componentPools[type]);
	}

	return static_cast<ComponentPool<T>&>(*iterator->second);
}

#pragma endregion Method_Definitions