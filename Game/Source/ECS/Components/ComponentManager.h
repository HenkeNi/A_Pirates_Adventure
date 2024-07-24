#pragma once
#include "ComponentArray.h"
//#include "Entities/Entity.h"
#include "ECSTypes.h"
#include <assert.h>

#include "ComponentInitializer.h"


class IComponentArray;

class ComponentManager
{
public:
	ComponentManager();

	template <typename T>
	void RegisterComponent(const char* name);

	//template <typename T>
	//void RegisterComponentInitializer(const char* name, const ComponentInitializer& initializer);

	template <typename T>
	void AddComponent(Entity entity);

	template <typename T>
	void RemoveComponent(Entity entity);

	template <typename T>
	void Destroy(Entity entity);

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

	//template <typename... Components>
	template <typename... T>
	std::vector<ComponentType> GetComponentTypes() const;

	//std::type_index GetComponentIdentifier(const char* name) const;

	// void InitializeComponent(std::string type, void* component, const ComponentProperties& properties);

private:
	template <typename T>
	const IComponentArray* FindComponentArray() const; // Fix!?

	template <typename T>
	IComponentArray* FindComponentArray();

	ComponentArrays m_componentArrays;
	
	ComponentTypes m_componentTypes;

	// std::unordered_map<std::string, ComponentInitializerFunc> m_componentInitializers;

	ComponentType m_nextComponentType;

	// Hi_Engine::MemoryPool<Component>
	//Hi_Engine::MemoryPool<std::type_index>
};

#pragma region Method_Definitions

template <typename T>
inline void ComponentManager::RegisterComponent(const char* name)
{
	auto type = std::type_index(typeid(T));

	assert(m_componentArrays.find(type) == m_componentArrays.end() && "[ComponentManager - ERROR]: Component type already registered!");

	m_componentArrays.insert({ type, std::make_unique<ComponentArray<T>>() });
	m_componentTypes.insert({ type, m_nextComponentType });
	

	/*auto initializeFunction = [](void* component, const ComponentProperties& properties)
		{
			T* castedComponent = static_cast<T*>(component);
			ComponentInitializer::InitializeComponent<T>(castedComponent, properties);
		};

	m_componentInitializers.insert({ name, initializeFunction });*/

	++m_nextComponentType;
}

//template<typename T>
//inline void ComponentManager::RegisterComponentInitializer(const ComponentInitializer& initializer)
//{
//	m_componentInitializers.insert()
//}

template<typename T>
inline void ComponentManager::AddComponent(Entity entity)
{
	T* component = Hi_Engine::MemoryPool<T>::GetInstance().GetResource(); // TODO; store in ComponentManager!
	
	if (auto* componentArray = FindComponentArray<T>())
	{
		componentArray->AddComponent(entity, component);
	}

	// return component!??
}

template<typename T>
inline void ComponentManager::RemoveComponent(Entity entity)
{
	if (auto* componentArray = FindComponentArray())
	{
		void* removed = componentArray->RemoveComponent(entity);
		T* component = static_cast<T*>(removed);

		Hi_Engine::MemoryPool<T>::GetInstance().ReturnResource(component);
	}
}

template <typename T>
inline void ComponentManager::Destroy(Entity entity)
{
	for (auto& [key, componentArray] : m_componentArrays)
	{
		componentArray->RemoveComponent(entity);
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
		component = static_cast<T*>(componentArray->GetComponent(entity));
	}

	return component;
}

template <typename T>
inline T* ComponentManager::GetComponent(Entity entity)
{
	T* component = nullptr;

	if (auto* componentArray = FindComponentArray<T>())
	{
		auto* comp = componentArray->GetComponent(entity);
		if (comp)
			component = static_cast<T*>(comp);
			//component = static_cast<T*>(componentArray->GetComponent(entity));
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

	assert(false && "[ComponentManager - ERROR]: ComponentType not registered!");
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

	assert(false && "[ComponentManager - ERROR]: Component Array not registered!");

	return nullptr;
}

template <typename T>
IComponentArray* ComponentManager::FindComponentArray()
{
	//IComponentArray* componentArray;

	auto type = std::type_index(typeid(T));

	auto iterator = m_componentArrays.find(type);
	if (iterator != m_componentArrays.end())
	{
		return iterator->second.get();
	}

	assert(false && "[ComponentManager - ERROR]: Component Array not registered!");

	return nullptr;
}

#pragma endregion Method_Definitions