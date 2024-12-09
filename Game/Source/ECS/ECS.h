#pragma once
#include "Entities/EntityManager.h"
#include "Entities/EntityFactory.h"
#include "Components/ComponentManager.h"
#include "Components/ComponentInitializer.h"
#include "Components/ComponentIO.h"
#include "Systems/SystemManager.h"
#include "ECSTypes.h"

#include "Components/ComponentView.h"

class ECS
{
public:
	ECS();

	void Init();
	void Shutdown();

	void Serialize(const char* file);
	void Deserialize(const char* file);

	Entity CreateEntityFromBlueprint(const char* type, bool notify = true);

	Entity CreateEntityFromJson(const rapidjson::Value& jsonEntity);

	std::vector<Entity> FindEntities(const Signature& signature);

	std::optional<Entity> FindEntity(const Signature& signature);

	void DestroyAllEntities();

	void DestroyEntity(Entity entity);

	template <typename T>
	void RegisterComponent(const char* name);

	template <typename... T>
	void AddComponent(Entity entity);

	template <typename T>
	void RemoveComponent(Entity entity);

	template <typename... T>
	bool HasComponent(Entity entity) const;
	
	template <typename T>
	const T* GetComponent(Entity entity) const;

	template <typename T>
	T* GetComponent(Entity entity);

	template <typename T>
	const std::vector<T>& GetComponents() const;

	template <typename T>
	std::vector<T>& GetComponents();

	template <typename... T>
	ComponentView<T...> GetComponentView();

	template <typename T>
	void RegisterSystem(const char* type);

	template <typename T>
	std::weak_ptr<System> GetSystem();

	std::weak_ptr<System> GetSystem(const char* system);

	template <typename... Components>
	Signature GetSignature();

	//template <typename T>
	//std::vector<std::reference_wrapper<T>> GetComponents(const std::vector<Entity>& entities); //since cant guarnatee that entity has component?!
	//std::vector<T*> GetComponents(const std::vector<Entity>& entities); // used where? reference wrapper?

	//template <typename... T>
	//std::vector<Entity> FindEntities();

	//template <typename... Components>
	//Entity FindEntity();

private:
	EntityManager m_entityManager;
	EntityFactory m_entityFactory;

	ComponentManager m_componentManager;
	ComponentRegistry m_componentRegistry;

	SystemManager m_systemManager;
	// SystemFactory m_systemFactory; // Remove? replace with system registry? or something?
};

#pragma region Method_Definitions

template<typename T>
inline void ECS::RegisterComponent(const char* name)
{
	m_componentManager.RegisterComponent<T>(name);

	ComponentRegistryEntry entry;
	entry.AddComponent = [this](Entity entity) 
	{ 
		AddComponent<T>(entity); 
	};
	entry.InitializeComponent = [this](Entity entity, const ComponentProperties& properties) 
	{
		if (auto* component = m_componentManager.GetComponent<T>(entity))
			ComponentInitializer::InitializeComponent<T>(component, properties); 
	};

	// entry.SerializeComponent = [this](Entity entity)
	// {
	//		if (auto* component = m_componentManager.GetComponent<T>(entity))
	//			ComponentIO::Serialize(component); // Pass in entity and document?
	// };

	entry.SerializeComponent = [](const void* component, const SerializationData& data)
	{
		// if (auto* component = m_componentManager.GetComponent<T>(entity))
			ComponentIO::Serialize(static_cast<const T*>(component), data); // Pass in entity and document?
	};

	entry.Type = std::type_index(typeid(T));
	//entry.TypeIndexToType.insert_or_assign(std::type_index(typeid(T)), name);

	m_componentRegistry.insert({ name, entry });
}

template<typename ...T>
inline void ECS::AddComponent(Entity entity)
{
	(m_componentManager.AddComponent<T>(entity), ...);

	Signature signature = m_entityManager.GetSignature(entity);

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

template<typename T>
inline const T* ECS::GetComponent(Entity entity) const
{
	return m_componentManager.GetComponent<T>(entity);;
}

template <typename T>
inline T* ECS::GetComponent(Entity entity)
{
	return m_componentManager.GetComponent<T>(entity);
}

template<typename T>
inline const std::vector<T>& ECS::GetComponents() const
{
	return m_componentManager.GetComponents<T>();
}

template<typename T>
inline std::vector<T>& ECS::GetComponents()
{
	return m_componentManager.GetComponents<T>();
}

template <typename... T>
inline ComponentView<T...> ECS::GetComponentView()
{
	Signature signature = GetSignature<T...>();
	auto entities = m_entityManager.GetEntities(signature);

	ComponentView<T...> componentView{ m_componentManager, std::move(entities) };
	return componentView;
}


template<typename T>
inline void ECS::RegisterSystem(const char* type)
{
	m_systemManager.RegisterSystem<T>(type);
	auto system = m_systemManager.GetSystem<T>().lock();
	system->Init(this);

	//m_systemFactory.Register<T>(type);
}

template<typename T>
inline std::weak_ptr<System> ECS::GetSystem()
{
	auto system = m_systemManager.GetSystem<T>();
	return system;
}

template<typename ...Components>
inline Signature ECS::GetSignature()
{
	Signature signature;

	((signature.set(m_componentManager.GetComponentType<Components>())), ...);

	return signature;
}

//template<typename T>
//inline std::vector<T*> ECS::GetComponents(const std::vector<Entity>& entities)
//{
//	std::vector<T*> components;
//	for (const auto& entity : entities)
//	{
//		if (auto* component = m_componentManager.GetComponent<T>(entity))
//		{
//			components.push_back(component);
//		}
//	}
//
//	return components;
//}

//template<typename T>
//inline std::vector<std::reference_wrapper<T>> ECS::GetComponents(const std::vector<Entity>& entities)
//{
//	std::vector<std::reference_wrapper<T>> components;
//	for (const auto& entity : entities)
//	{
//		if (auto* component = m_componentManager.GetComponent<T>(entity))
//		{
//			components.push_back(std::ref(*component));
//		}
//	}
//
//	return components;
//}

#pragma endregion Method_Definitions