#pragma once
#include "../Core/Modules/Module.h"
#include "Utility/ECSTypes.h"
#include "Core/EntityManager.h"
#include "Core/EntityFactory.h"
#include "Core/ComponentManager.h"
#include "Core/ComponentView.h" // req for templated class?
#include "Core/SystemManager.h"

#include "Core/ComponentInitializer.h"

// #include <functional>

namespace Hi_Engine
{
	class System;
	class Engine;

	class ECSCoordinator : public Module
	{
	public:
		ECSCoordinator(ModuleManager& manager);
		~ECSCoordinator(); // TEMP

		bool Init() override;

		std::optional<Entity> CreateEntityFromPrefab(const char* type, bool notify = true);

		std::optional<Entity> CreateEntityFromJson(const rapidjson::Value& jsonEntity);

		void DestroyAllEntities();

		void DestroyEntity(Entity entity);

		template <typename Component>
		void RegisterComponent(const char* name);

		template <typename... Components>
		void AddComponents(Entity entity); // take in data instead?

		template <typename Component, typename... Args>
		void AddComponent(Entity entity, Args&&... args);

		template <typename Component>
		void RemoveComponent(Entity entity);

		template <typename... Components>
		ComponentView<Components...> GetComponentView();

		template <typename... Components>
		ComponentView<Components...> GetComponentView(const std::function<bool(Entity e1, Entity e2)>& sort);

		template <typename Component>
		const std::vector<Component>& GetComponents() const;

		template <typename Component>
		std::vector<Component>& GetComponents();

		template <typename Component>
		const Component* GetComponent(Entity entity) const;

		template <typename Component>
		Component* GetComponent(Entity entity);

		template <typename System, typename... Args>
		void RegisterSystem(const char* name, Args&&... args); // remove name?

		template <typename... Components>
		Signature GetSignature();

		template <typename... Components>
		bool HasComponent(Entity entity) const;

	private:
		void Update(float deltaTime); // TEMP

		friend class Engine; // temP?

		EntityManager m_entityManager;
		EntityFactory m_entityFactory;

		ComponentManager m_componentManager;
		ComponentRegistry m_componentRegistry;

		SystemManager m_systemManager;
	};

#pragma region Templated_Methods

	template<typename Component>
	inline void ECSCoordinator::RegisterComponent(const char* name)
	{
		m_componentManager.RegisterComponent<Component>(name);

		ComponentRegistryEntry entry;
		entry.AddComponent = [this](Entity entity)
		{
			AddComponents<Component>(entity);
		};
		entry.InitializeComponent = [this](Entity entity, const ComponentProperties& properties)
		{
			if (auto* component = m_componentManager.GetComponent<Component>(entity))
				InitializeComponent(component, properties);
		};

		m_componentRegistry.insert({ name, entry });
	}

	template<typename ...Components>
	inline void ECSCoordinator::AddComponents(Entity entity)
	{
		(m_componentManager.AddComponent<Components>(entity), ...);

		std::optional<Signature> signature = m_entityManager.GetSignature(entity);
		// TODO; improve!
		if (signature.has_value())
		{
			((signature.value().set(m_componentManager.GetComponentType<Components>())), ...);

			m_entityManager.SetSignature(entity, signature.value());
		}
	}

	template<typename Component, typename ...Args>
	inline void ECSCoordinator::AddComponent(Entity entity, Args && ...args)
	{

	}

	template<typename Component>
	inline void ECSCoordinator::RemoveComponent(Entity entity)
	{
		m_componentManager.RemoveComponent<Component>(entity);

		std::optional<Signature> signature = m_entityManager.GetSignature(entity);

		if (signature.has_value())
		{
			signature.value().set(m_componentManager.GetComponentType<Component>(), false);

			m_entityManager.SetSignature(entity, signature.value());
		}
	}

	template<typename ...Components>
	inline ComponentView<Components...> ECSCoordinator::GetComponentView()
	{
		Signature signature = GetSignature<Components...>();
		auto entities = m_entityManager.GetEntities(signature);

		ComponentView<Components...> componentView{ m_componentManager, std::move(entities) };
		return componentView;
	}

	template<typename ...Components>
	inline ComponentView<Components...> ECSCoordinator::GetComponentView(const std::function<bool(Entity e1, Entity e2)>& sort)
	{
		Signature signature = GetSignature<Components...>();
		auto entities = m_entityManager.GetEntities(signature);

		std::sort(entities.begin(), entities.end(), sort);

		ComponentView<Components...> componentView{ m_componentManager, std::move(entities) };
		return componentView;
	}

	template<typename Component>
	inline const std::vector<Component>& ECSCoordinator::GetComponents() const
	{
		return m_componentManager.GetComponents<Component>();
	}

	template<typename Component>
	inline std::vector<Component>& ECSCoordinator::GetComponents()
	{
		return m_componentManager.GetComponents<Component>();
	}

	template<typename Component>
	inline const Component* ECSCoordinator::GetComponent(Entity entity) const
	{
		return m_componentManager.GetComponent<Component>(entity);
	}

	template<typename Component>
	inline Component* ECSCoordinator::GetComponent(Entity entity)
	{
		return m_componentManager.GetComponent<Component>(entity);
	}

	template <typename System, typename... Args>
	inline void ECSCoordinator::RegisterSystem(const char* name, Args&&... args)
	{
		auto system = std::make_shared<System>(*this, std::forward<Args>(args)...);
		m_systemManager.AddSystem(std::move(system));
	}

	template <typename ...Components>
	inline Signature ECSCoordinator::GetSignature()
	{
		Signature signature;

		((signature.set(m_componentManager.GetComponentType<Components>())), ...);

		return signature;
	}

	template<typename ...Components>
	inline bool ECSCoordinator::HasComponent(Entity entity) const
	{
		std::optional<Signature> entitySignature = m_entityManager.GetSignature(entity);
		if (!entitySignature.has_value())
			return false;

		Signature componentSignature;

		((componentSignature.set(m_componentManager.GetComponentType<Components>())), ...);

		return (entitySignature.value() & componentSignature) == componentSignature;
	}

#pragma endregion Templated_Methods
}