#pragma once
#include "Entities/EntityManager.h"
#include "Entities/EntityFactory.h"
#include "Components/ComponentManager.h"
#include "Systems/SystemManager.h"
#include "Systems/SystemFactory.h"
#include "ECSTypes.h"
#include "Components/ComponentInitializer.h"

// Rename: ECS_Engine?
class ECS
{
public:
	ECS();

	void Init();
	void Shutdown();

	void Serialize();
	void Deserialize();

	template <typename T>
	void RegisterSystem(const char* type);

	template <typename T>
	void RegisterComponent(const char* name);

	template <typename... T>
	void AddComponent(Entity entity);

	void AddComponent(Entity entity, const char* component);
	
	template <typename T>
	void RemoveComponent(Entity entity);

	template <typename... T>
	bool HasComponent(Entity entity) const;
	
	//template <typename T>
	//const std::vector<T>& GetComponents() const;

	template <typename T>
	std::vector<T>& GetComponents();

	template <typename T>
	std::vector<T*> GetComponents(const std::vector<Entity>& entities); // used where

	template <typename T>
	T* GetComponent(Entity entity);

	template <typename... Components>
	Signature GetSignature();

	template <typename T>
	std::weak_ptr<System> GetSystem();

	std::weak_ptr<System> GetSystem(const char* system);

	Entity CreateEntity(const char* type, bool notify = true); // bool defered spawn?

	Entity CreateEmptyEntity();

	void DestroyAllEntities();

	void DestroyEntity(Entity entity);

	std::vector<Entity> FindEntities(const Signature& signature);

	std::optional<Entity> FindEntity(const Signature& signature); // return optional?

	//template <typename... T>
	//std::vector<Entity> FindEntities();

	//template <typename Component>
	//Entity FindEntity();

	//void LoadBlueprints();

	// TODO; have function tha tdoes both??
	void InitializeComponent(Entity entity, const char* component, const ComponentProperties& properties);

private:
	EntityManager m_entityManager;
	EntityFactory m_entityFactory;

	ComponentManager m_componentManager;
	ComponentRegistry m_componentRegistry;

	SystemManager m_systemManager;
	SystemFactory m_systemFactory; // Remove? 
};

#pragma region Method_Definitions

template<typename T>
inline void ECS::RegisterSystem(const char* type)
{
	m_systemManager.RegisterSystem<T>(type);
	auto system = m_systemManager.GetSystem<T>().lock();
	system->Init(this);

	//m_systemFactory.Register<T>(type);
}

template<typename T>
inline void ECS::RegisterComponent(const char* name)
{
	m_componentManager.RegisterComponent<T>(name);

	ComponentRegistryEntry entry;
	entry.AddComponent = [this](Entity entity) { AddComponent<T>(entity); };
	entry.InitializeComponent = [this](Entity entity, const ComponentProperties& properties) 
		{
			if (auto* component = m_componentManager.GetComponent<T>(entity))
				ComponentInitializer::InitializeComponent<T>(component, properties); 
		};
	
	m_componentRegistry.insert({ name, entry });
}

template<typename ...T>
inline void ECS::AddComponent(Entity entity)
{
	(m_componentManager.AddComponent<T>(entity), ...);

	Signature signature = m_entityManager.GetSignature(entity); // return reference/const ref instead??

	((signature.set(m_componentManager.GetComponentType<T>())), ...);

	m_entityManager.SetSignature(entity, signature);
}

template<typename T>
inline void ECS::RemoveComponent(Entity entity)
{
	m_componentManager.RemoveComponent<T>(entity);

	Signature signature = m_entityManager.GetSignature(entity);
	signature.set(m_componentManager.GetComponentType<T>(), false);

	m_entityManager.SetSignature(entity, signature);
}

template<typename ...T>
inline bool ECS::HasComponent(Entity entity) const
{
	Signature entitySignature = m_entityManager.GetSignature(entity);

	Signature componentSignature;

	((componentSignature.set(m_componentManager.GetComponentType<T>())), ...);

	return (entitySignature & componentSignature) == componentSignature;
}

//template<typename T>
//inline std::vector<const T*> ECS::GetComponents() const
//{
//	auto components = m_componentManager.GetComponents<T>();
//	return components;
//}

template<typename T>
inline std::vector<T>& ECS::GetComponents()
{
	return m_componentManager.GetComponents<T>();
	//return components;
}

template<typename T>
inline std::vector<T*> ECS::GetComponents(const std::vector<Entity>& entities)
{
	std::vector<T*> components;
	for (const auto& entity : entities)
	{
		if (auto* component = m_componentManager.GetComponent<T>(entity))
		{
			components.push_back(component);
		}
	}

	return components;
}

template <typename T>
inline T* ECS::GetComponent(Entity entity)
{
	T* component = m_componentManager.GetComponent<T>(entity);
	return component;
}

template<typename ...Components>
inline Signature ECS::GetSignature()
{
	Signature signature;

	((signature.set(m_componentManager.GetComponentType<Components>())), ...);

	return signature;
}

template<typename T>
inline std::weak_ptr<System> ECS::GetSystem()
{
	auto system = m_systemManager.GetSystem<T>();
	return system;
}

#pragma endregion Method_Definitions