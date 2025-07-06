#pragma once
#include "Utility/TypeTraits.h"
//#include "Utility/DataStructures/SparseSet.h" // -> NEEDED?
#include "../ECS/Core/EntityManager.h"
#include "../ECS/Core/ComponentManager.h"
#include "../ECS/Utility/ComponentView.h"
#include "../ECS/Core/SystemManager.h"
#include "../ECS/Utility/ECSTypes.h"

// include Logger?

// TODO; - Send events for entity added / removed? - can transfer entities (between scenes / World)?
// Consider; cache already created ComponentView's in "Groups" - systems caches signatures?
// Consider; Cache component view (groups)? when created, cache them in a map (key == signature?) -> groups listen to various entity events?

// Consider; 1. Rename 'Add' To 'Emplace' for components? 2. Put world in ECS folder? 3. Return Component in AddComponent function?

namespace Hi_Engine
{
	class EntityHandle;

	class World : public NonCopyable
	{
	public:
		// ==================== Construction/Destruction ====================

		World() = default;
		~World() = default;

		World(World&&) = delete;
		World& operator=(World&&) = delete;
		
		// ==================== Entity Management ====================

		[[nodiscard]] std::optional<EntityHandle> CreateEntity();

		void DestroyEntity(const Entity& entity);

		void DestroyEntities(const std::vector<Entity>& entities);

		void DestroyAllEntities();

		// ==================== Entity Queries ====================

		[[nodiscard]] bool IsAlive(const Entity& entity) const;

		// ==================== Component Management ====================

		template <ComponentType T, typename... Args>
		void AddComponent(const Entity& entity, Args&&... args);

		template <ComponentType... Ts>
		void AddComponents(const Entity& entity);

		template <ComponentType T>
		void RemoveComponent(const Entity& entity);

		// ==================== Component Access ====================

		template <ComponentType T>
		[[nodiscard]] const T& GetComponent(const Entity& entity) const;

		template <ComponentType T>
		[[nodiscard]] T& GetComponent(const Entity& entity);

		template <ComponentType T>
		[[nodiscard]] const T* TryGetComponent(const Entity& entity) const;

		template <ComponentType T>
		[[nodiscard]] T* TryGetComponent(const Entity& entity);

		// ==================== Component Queries ====================

		template <ComponentType... Ts>
		[[nodiscard]] bool HasAllComponents(EntityID id) const;

		template <ComponentType... Ts>
		[[nodiscard]] bool HasAnyComponent(EntityID id) const;

		template <ComponentType... Ts>
		[[nodiscard]] ComponentView<Ts...> GetComponentView() const;

		template <ComponentType... Ts>
		[[nodiscard]] ComponentView<Ts...> GetComponentView();

		template <ComponentType... Ts, CallableReturns<bool, EntityHandle> Func>
		[[nodiscard]] ComponentView<Ts...> GetComponentView(Func&& filtering) const;
		
		template <ComponentType... Ts, CallableReturns<bool, EntityHandle> Func>
		[[nodiscard]] ComponentView<Ts...> GetComponentView(Func&& filtering);

		// ==================== System Management ====================

		template <DerivedFrom<System> T, typename... Args>
		void EmplaceSystem(Args&&... args);

		void InsertSystem(std::unique_ptr<System> system);

		template <DerivedFrom<System> T>
		void RemoveSystem();

		void RemoveAllSystems();

		template <DerivedFrom<System> T>
		void EnableSystem();

		template <DerivedFrom<System> T>
		void DisableSystem();

		// ==================== System Queries ====================
		
		template <DerivedFrom<System> T>
		[[nodiscard]] bool HasSystem() const; // noexcep?

		// ==================== Per-Frame Execution ====================

		void Update(float deltaTime);

	private:
		// ==================== Internal Helpers ====================

		template <ComponentType T>
		[[nodiscard]] ComponentManager<T>& FindOrCreateComponentManager();
		
		template <ComponentType T>
		[[nodiscard]] const ComponentManager<T>* GetComponentManager() const;

		template <ComponentType... Ts>
		[[nodiscard]] Signature GetSignature() const;

		EntityManager m_entityManager;
		ComponentManagerMap m_componentManagers; // Use a sparse set instead? (component ID as key)
		SystemManager m_systemManager;
	};

#pragma region Templated_Methods

	template<ComponentType T, typename... Args>
	void World::AddComponent(const Entity& entity, Args&&... args)
	{
		if (!m_entityManager.IsAlive(entity))
		{
			Logger::LogWarning("[ECS::AddComponents] - Trying to add component an invalid entity!");
			return;
		}

		auto& componentMananger = FindOrCreateComponentManager<T>();

		componentMananger.AddComponent(entity.ID, std::forward<Args>(args)...);
		std::optional<Signature> optionalSignature = m_entityManager.GetSignature(entity.ID);

		if (optionalSignature.has_value())
		{
			Signature signature = optionalSignature.value();
			signature.set(GetComponentID<T>());

			m_entityManager.SetSignature(entity, signature);
		}
		else
		{
			Logger::LogError("[ECSCoordinator::AddComponent] - Failed to fetch correct signature for entity: " + std::to_string(entity.ID));
		}
	}
	
	template <ComponentType... Ts>
	void World::AddComponents(const Entity& entity)
	{
		(AddComponent<Ts>(entity), ...);
	}

	template <ComponentType T>
	void World::RemoveComponent(const Entity& entity)
	{
		if (!m_entityManager.IsAlive(entity))
		{
			Logger::LogWarning("[ECS::RemoveComponent] - Invalid Entity: " + std::to_string(entity.ID));
			return;
		}

		if (auto* componentManager = GetComponentManager<T>())
		{
			componentManager->RemoveComponent(entity.ID);
			std::optional<Signature> optionalSignature = m_entityManager.GetSignature(entity.ID);

			if (optionalSignature.has_value())
			{
				auto signature = optionalSignature.value();
				signature.set(GetComponentID<T>(), false);

				m_entityManager.SetSignature(entity, signature);
			}
			else
			{
				Logger::LogWarning("[ECS::RemoveComponent] - Failed to find signature for entity " + std::to_string(entity.ID));
			}
		}
		else
		{
			Logger::LogWarning("[ECS::RemoveComponent] - Failed to find component manager!");
		}
	}

	template <ComponentType T>
	const T& World::GetComponent(const Entity& entity) const
	{
		assert(m_entityManager.IsAlive(entity) && HasAllComponents<T>(entity.ID));

		return GetComponentManager<T>()->GetComponent(entity.ID);
	}

	template <ComponentType T>
	T& World::GetComponent(const Entity& entity)
	{
		return const_cast<T&>(std::as_const(*this).GetComponent<T>(entity));
	}

	template <ComponentType T>
	const T* World::TryGetComponent(const Entity& entity) const
	{
		T* component = nullptr;

		if (!m_entityManager.IsAlive(entity))
		{
			Logger::LogWarning("[ECS::GetComponent] - Invalid entity!");
		}
		else if (auto* componentManager = GetComponentManager<T>())
		{
			component = componentManager->GetComponent(entity.ID);
		}
		else
		{
			Logger::LogWarning("[ECS::GetComponent] - ComponentManager for type not found!");
		}

		return component;
	}

	template <ComponentType T>
	T* World::TryGetComponent(const Entity& entity)
	{
		if (!m_entityManager.IsAlive(entity))
		{
			Logger::LogWarning("[ECS::GetComponent] - Invalid entity!");
			return nullptr;
		}

		auto& componentManager = FindOrCreateComponentManager<T>(); // or always use GetComponentManager?
		return componentManager.GetComponent(entity.ID); // Check if alive before calling component manager?
	}

	template <ComponentType... Ts>
	bool World::HasAllComponents(EntityID id) const
	{
		std::optional<Signature> entitySignature = m_entityManager.GetSignature(id);

		if (entitySignature.has_value())
		{
			Signature componentSignature;
			(componentSignature.set(GetComponentID<Ts>()), ...);

			return (entitySignature.value() & componentSignature) == componentSignature;
		}

		Logger::LogWarning("[ECS::HasAllComponents] - Failed to find entity signature!");
		return false;
	}

	template<ComponentType ...Ts>
	bool World::HasAnyComponent(EntityID id) const
	{
		std::optional<Signature> optionalSignature = m_entityManager.GetSignature(id);

		if (optionalSignature.has_value())
		{
			Signature componentSignature;
			(componentSignature.set(GetComponentID<Ts>()), ...);

			return (optionalSignature.value() & componentSignature).any();
		}

		Logger::LogWarning("[ECS::HasAnyComponent] - Failed to find entity signature!");
		return false;
	}

	template<ComponentType ...Ts>
	ComponentView<Ts...> World::GetComponentView() const
	{
		const Signature signature = GetSignature<Ts...>();
		auto entities = m_entityManager.GetEntities(signature);

		const ComponentView<Ts...> componentView{ FindOrCreateComponentManager<Ts>().GetContainer()..., std::move(entities) };
		return componentView;
	}

	template <ComponentType... Ts>
	ComponentView<Ts...> World::GetComponentView()
	{
		const Signature signature = GetSignature<Ts...>();
		auto entities = m_entityManager.GetEntities(signature); // instead get sparse sets... get smallest , fetch all entites, compare to other sparse sets??

		ComponentView<Ts...> componentView{ FindOrCreateComponentManager<Ts>().GetContainer()..., std::move(entities) };
		return componentView;
	}

	template <ComponentType ...Ts, CallableReturns<bool, EntityHandle> Func>
	ComponentView<Ts...> World::GetComponentView(Func&& filtering) const
	{
		const Signature signature = GetSignature<Ts...>();
		auto entities = m_entityManager.GetEntities(signature); // return entity handles instead..

		std::vector<Entity> matchingEntities;
		for (const auto& entity : entities)
		{
			if (filtering(EntityHandle{ entity, this }))
			{
				matchingEntities.emplace_back(entity);
			}
		}

		ComponentView<Ts...> componentView{ FindOrCreateComponentManager<Ts>().GetContainer()..., std::move(matchingEntities) };
		return componentView;
	}

	template <ComponentType ...Ts, CallableReturns<bool, EntityHandle> Func>
	ComponentView<Ts...> World::GetComponentView(Func&& filtering)
	{
		const Signature signature = GetSignature<Ts...>();
		auto entities = m_entityManager.GetEntities(signature);

		std::vector<Entity> matchingEntities;
		for (const auto& entity : entities)
		{
			if (filtering(EntityHandle{ entity, this }))
			{
				matchingEntities.emplace_back(entity);
			}
		}

		ComponentView<Ts...> componentView{ FindOrCreateComponentManager<Ts>().GetContainer()..., std::move(matchingEntities) };
		return componentView;
	}

	template <DerivedFrom<System> T, typename... Args>
	void World::EmplaceSystem(Args&&... args)
	{
		m_systemManager.Emplace(std::forward<Args>(args)...);
	}

	template <DerivedFrom<System> T>
	void World::RemoveSystem()
	{
		m_systemManager.RemoveSystem<T>();
	}

	template <DerivedFrom<System> T>
	void World::EnableSystem()
	{
		m_systemManager.Enable<T>();
	}

	template <DerivedFrom<System> T>
	void World::DisableSystem()
	{
		m_systemManager.Disable<T>();
	}

	template <DerivedFrom<System> T>
	bool World::HasSystem() const
	{
		return m_systemManager.HasSystem<T>();
	}

	template <ComponentType T>
	ComponentManager<T>& World::FindOrCreateComponentManager()
	{
		auto it = m_componentManagers.try_emplace(GetComponentID<T>(), std::make_unique<ComponentManager<T>>());

		if (it.second)
		{
			auto type = std::type_index(typeid(T));
			Logger::LogInfo("ComponentManager created " + std::string(type.name()));
		}

		return *static_cast<ComponentManager<T>*>(it.first->second.get());
	}

	template <ComponentType T>
	const ComponentManager<T>* World::GetComponentManager() const
	{
		auto id = GetComponentID<T>();
		auto it = m_componentManagers.find(id);

		if (it != m_componentManagers.end())
		{
			return static_cast<ComponentManager<T>*>(it->second.get());
		}

		return nullptr;
	}

	template <ComponentType... Ts>
	Signature World::GetSignature() const
	{
		Signature signature;
		(signature.set(GetComponentID<Ts>()), ...);

		return signature;
	}

#pragma endregion Templated_Methods
}