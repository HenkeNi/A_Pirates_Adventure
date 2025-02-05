#pragma once
#include "../Core/Modules/Module.h"
#include "Utility/ECSTypes.h"
#include "Utility/TypeTraits.h"
#include "Core/EntityManager.h"
#include "Core/EntityFactory.h"
#include "Core/ComponentManager.h"
#include "Core/ComponentView.h" // req for templated class?
#include "Core/SystemManager.h"

#include "Core/ComponentInitializer.h"

// #include <functional>

// TODO; create an ECS message system?
// TODO: dont have ECS be a module, rename to World? and store directly in engine?
// maybe store ECS in scene (make part of engine?) or application

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

		std::optional<Entity> CreateEntityFromPrefab(const char* type, bool notify = true); // pass string view (by value) instead?

		std::optional<Entity> CreateEntityFromJson(const rapidjson::Value& jsonEntity);

		void DestroyAllEntities();

		void DestroyEntity(Entity entity);

		//template <ComponentType T, StringConvertible U>
		template <ComponentType T>
		void RegisterComponent(auto&& name); // TODO; add type safety for auto?

		template <ComponentType... Ts>
		void AddComponents(Entity entity); // take in data instead?

		template <ComponentType T, typename... Args>
		void AddComponent(Entity entity, Args&&... args);

		template <ComponentType T>
		void RemoveComponent(Entity entity);

		template <ComponentType... Ts>
		ComponentView<Ts...> GetComponentView();

		template <ComponentType... Ts, Callable<Entity, Entity> Comparator>
		ComponentView<Ts...> GetComponentView(Comparator&& comparator);

		template <ComponentType T>
		const std::vector<T>& GetComponents() const;

		template <ComponentType T>
		std::vector<T>& GetComponents();

		template <ComponentType T>
		const T* GetComponent(Entity entity) const;

		template <ComponentType T>
		T* GetComponent(Entity entity);

		template <DerivedFrom<System> T, typename... Args>
		void RegisterSystem(const char* name, Args&&... args); // remove name?

		template <ComponentType... Ts>
		Signature GetSignature();

		template <ComponentType... Ts>
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

	template <ComponentType T>
	inline void ECSCoordinator::RegisterComponent(auto&& name)
	{
		// TODO; assert that component is trivial?

		m_componentManager.RegisterComponent<T>();

		ComponentRegistryEntry entry;
		entry.AddComponent = [this](Entity entity)
		{
			AddComponents<T>(entity);
		};
		entry.InitializeComponent = [this](Entity entity, const ComponentProperties& properties)
		{
			if (auto* component = m_componentManager.GetComponent<T>(entity))
				InitializeComponent(component, properties);
		};

		m_componentRegistry.insert({ std::forward<decltype(name)>(name), entry });
	}

	template <ComponentType... Ts>
	inline void ECSCoordinator::AddComponents(Entity entity)
	{
		(m_componentManager.AddComponent<Ts>(entity), ...);

		std::optional<Signature> signature = m_entityManager.GetSignature(entity);
		// TODO; improve!
		if (signature.has_value())
		{
			((signature.value().set(m_componentManager.GetComponentID<Ts>().value_or(0))), ...);

			m_entityManager.SetSignature(entity, signature.value());
		}
	}

	template<ComponentType T, typename ...Args>
	inline void ECSCoordinator::AddComponent(Entity entity, Args&& ...args)
	{
		m_componentManager.AddComponent<T>(entity, std::forward<Args>(args));

		std::optional<Signature> signature = m_entityManager.GetSignature(entity);
		if (signature.has_value())
		{
			signature.value().set(m_componentManager.GetComponentID<T>().value_or(0));
		}
		else
		{
			Logger::LogError("[ECSCoordinator::AddComponent] - Failed to fetch correct signature for entity: " + std::to_string(entity));
		}
	}

	template <ComponentType T>
	inline void ECSCoordinator::RemoveComponent(Entity entity)
	{
		m_componentManager.RemoveComponent<T>(entity);

		std::optional<Signature> signature = m_entityManager.GetSignature(entity);

		if (signature.has_value())
		{
			signature.value().set(m_componentManager.GetComponentID<T>(), false);

			m_entityManager.SetSignature(entity, signature.value());
		}
	}

	template <ComponentType... Ts>
	inline ComponentView<Ts...> ECSCoordinator::GetComponentView()
	{
		Signature signature = GetSignature<Ts...>();
		auto entities = m_entityManager.GetEntities(signature);

		ComponentView<Ts...> componentView{ m_componentManager, std::move(entities) };
		return componentView;
	}

	template <ComponentType... Ts, Callable<Entity, Entity> Comparator>
	inline ComponentView<Ts...> ECSCoordinator::GetComponentView(Comparator&& comparator)
	{
		Signature signature = GetSignature<Ts...>();
		auto entities = m_entityManager.GetEntities(signature);

		std::sort(entities.begin(), entities.end(), comparator);

		ComponentView<Ts...> componentView{ m_componentManager, std::move(entities) };
		return componentView;
	}

	template <ComponentType T>
	inline const std::vector<T>& ECSCoordinator::GetComponents() const
	{
		return m_componentManager.GetComponents<T>();
	}

	template <ComponentType T>
	inline std::vector<T>& ECSCoordinator::GetComponents()
	{
		return m_componentManager.GetComponents<T>();
	}

	template <ComponentType T>
	inline const T* ECSCoordinator::GetComponent(Entity entity) const
	{
		return m_componentManager.GetComponent<T>(entity);
	}

	template <ComponentType T>
	inline T* ECSCoordinator::GetComponent(Entity entity)
	{
		return m_componentManager.GetComponent<T>(entity);
	}

	template <DerivedFrom<System> T, typename... Args>
	inline void ECSCoordinator::RegisterSystem(const char* name, Args&&... args)
	{
		auto system = std::make_shared<T>(*this, std::forward<Args>(args)...);
		m_systemManager.AddSystem(std::move(system));
	}

	template <ComponentType... Ts>
	inline Signature ECSCoordinator::GetSignature()
	{
		Signature signature;

		//((signature.set(m_componentManager.GetComponentID<Components>())), ...);
		((signature.set(m_componentManager.GetComponentID<Ts>().value_or(0))), ...);

		return signature;
	}

	template <ComponentType... Ts>
	inline bool ECSCoordinator::HasComponent(Entity entity) const
	{
		std::optional<Signature> entitySignature = m_entityManager.GetSignature(entity);
		if (!entitySignature.has_value())
			return false;

		Signature componentSignature;

		//((componentSignature.set(m_componentManager.GetComponentID<Components>())), ...);
		
		((componentSignature.set(m_componentManager.GetComponentID<Ts>().value_or(0))), ...);

		return (entitySignature.value() & componentSignature) == componentSignature;
	}

#pragma endregion Templated_Methods
}