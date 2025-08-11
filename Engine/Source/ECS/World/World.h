#pragma once
#include "Utility/TypeTraits.h"
//#include "Utility/DataStructures/SparseSet.h" // -> NEEDED?
#include "../ECS/Core/EntityManager.h"
#include "../ECS/Core/ComponentManager.h"
#include "../ECS/Utility/ComponentView.h"
#include "../ECS/Core/SystemManager.h"
#include "../ECS/Utility/ECSTypes.h"
#include "../../Services/Time/ScopedTimer.h"

// include Logger?

// [TODO] - Send events for entity created / destroyed? (adding/removing components?)
// [TODO] - Add ability to transfer entities (other World)
// [Consider] - cache already created ComponentView's in "Groups" - systems caches signatures?
// [Consider] - Cache component view (groups)? when created, cache them in a map (key == signature?) -> groups listen to various entity events?
// [Consider] - Rename 'Add' To 'Emplace' for components?

// TODO; Add GetEntity(ID) -> returns a handle? SearchForEntity()?
// TODO; Make sure no Component... Ts is called with the same component type more than once!

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

		[[nodiscard]] inline bool IsAlive(const Entity& entity) const { return m_entityManager.IsAlive(entity); }

		std::optional<EntityHandle> FindEntityByName(std::string_view name); 

		std::vector<EntityHandle> FindAllEntitiesWithTag(std::string_view tag);

		// ==================== Component Management ====================

		template <ComponentType T, typename... Args>
		std::pair<T*, bool> AddComponent(const Entity& entity, Args&&... args);

		template <ComponentType T>
		void RemoveComponent(const Entity& entity); // return bool (success)?

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


		// TODO; assert it's not called with same compoennt type more than once!

		template <ComponentType... Ts>
		[[nodiscard]] std::optional<ComponentView<Ts...>> GetComponentView() const; // remove? since requires a const world!

		template <ComponentType... Ts>
		[[nodiscard]] ComponentView<Ts...> GetComponentView();

		template <ComponentType... Ts, CallableReturns<bool, EntityHandle> Func>
		[[nodiscard]] std::optional<ComponentView<Ts...>> GetComponentView(Func&& filtering) const;
		
		template <ComponentType... Ts, CallableReturns<bool, EntityHandle> Func>
		[[nodiscard]] ComponentView<Ts...> GetComponentView(Func&& filtering);

		// ==================== System Management ====================

		template <DerivedFrom<System> T, typename... Args>
		inline void EmplaceSystem(Args&&... args) { m_systemManager.Emplace(std::forward<Args>(args)...); }

		template <DerivedFrom<System> T>
		inline void InsertSystem(std::unique_ptr<T>&& system) { m_systemManager.Insert(std::move(system)); }

		inline void InsertSystem(std::unique_ptr<System>&& system, std::type_index type) { m_systemManager.Insert(std::move(system), type); }

		template <DerivedFrom<System> T>
		inline void RemoveSystem() { m_systemManager.RemoveSystem<T>(); }

		inline void RemoveAllSystems() { m_systemManager.Clear(); }

		template <DerivedFrom<System> T>
		inline void EnableSystem() { m_systemManager.Enable<T>(); }

		template <DerivedFrom<System> T>
		inline void DisableSystem() { m_systemManager.Disable<T>(); }

		// ==================== System Access ====================

		template <DerivedFrom<System> T>
		[[nodiscard]] inline const T& GetSystem() const { return m_systemManager.GetSystem<T>(); }

		template <DerivedFrom<System> T>
		[[nodiscard]] inline T& GetSystem() { return m_systemManager.GetSystem<T>(); }
		
		template <DerivedFrom<System> T>
		[[nodiscard]] inline const T* TryGetSystem() const { return m_systemManager.TryGetSystem<T>(); }

		template <DerivedFrom<System> T>
		[[nodiscard]] inline T* TryGetSystem() { return m_systemManager.TryGetSystem<T>(); }

		// ==================== System Queries ====================
		
		template <DerivedFrom<System> T>
		[[nodiscard]] inline bool HasSystem() const { return m_systemManager.HasSystem<T>(); } // noexcep?

		[[nodiscard]] inline std::size_t GetSystemCount() const noexcept { return m_systemManager.GetSystemCount(); }

		// ==================== Per-Frame Execution ====================

		void Update(float deltaTime);

		// Add ForEachSystem...

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
	std::pair<T*, bool> World::AddComponent(const Entity& entity, Args&&... args)
	{
		const bool isAlive = m_entityManager.IsAlive(entity);

		assert(isAlive && "Entity is no longer valid");

		if (!isAlive)
		{
			Logger::LogWarning("[ECS::AddComponent] - Trying to add component an invalid entity!");
			return { nullptr, false };
		}

		const bool hasComponent = HasAllComponents<T>(entity.ID);

		assert(!hasComponent && "Entity already have component!");

		if (hasComponent)
		{
			Logger::LogError("[ECS::AddComponent] - Entity already have component!");
			return { nullptr, false };
		}

		auto& componentMananger = FindOrCreateComponentManager<T>();
		auto [component, success] = componentMananger.AddComponent(entity.ID, std::forward<Args>(args)...); // or return component directly? since pair?

		// only update signature is success?s

		std::optional<Signature> signatureOpt = m_entityManager.GetSignature(entity.ID);

		if (signatureOpt.has_value())
		{
			Signature& signature = signatureOpt.value(); // or function to "update signature" in entity manager?
			signature.set(GetComponentID<T>());

			m_entityManager.SetSignature(entity, signature);
		}
		else
		{
			Logger::LogError("[ECSCoordinator::AddComponent] - Failed to fetch correct signature for entity: " + std::to_string(entity.ID));
		}

		return { component, true };
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
				auto& signature = optionalSignature.value();
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
		if (!m_entityManager.IsAlive(entity))
		{
			Logger::LogWarning("[ECS::TryGetComponent] - Invalid entity!");
			return nullptr;
		}

		if (auto* componentManager = GetComponentManager<T>()) [[likely]]
		{
			return componentManager->TryGetComponent(entity.ID);
		}
		
		Logger::LogWarning("[ECS::TryGetComponent] - ComponentManager for type not found!");
		return nullptr;
	}

	template <ComponentType T>
	T* World::TryGetComponent(const Entity& entity)
	{
		return const_cast<T*>(std::as_const(*this).TryGetComponent<T>(entity));
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

	template<ComponentType... Ts>
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

	template<ComponentType... Ts>
	std::optional<ComponentView<Ts...>> World::GetComponentView() const // why not called!? -> shoudl use GetComponentManage!
	{
		PROFILE_FUNCTION("[const] World::GetComponentView: ");

		const Signature signature = GetSignature<Ts...>();
		auto entities = m_entityManager.GetEntities(signature);

		// Check if all component managers exist...
		bool hasAllComponentManagers = ((GetComponentManager<Ts>() != nullptr) && ...);

		if (!hasAllComponentManagers)
		{
			Logger::LogError("[World::GetComponentView] - Failed to fetch component manager(s)!");
			return std::nullopt;
		}

		ComponentView<Ts...> componentView{ GetComponentManager<Ts>()->GetContainer()..., std::move(entities) };
		return componentView;
	}

	template <ComponentType... Ts>
	ComponentView<Ts...> World::GetComponentView()
	{
		// use decay type?

		PROFILE_FUNCTION("World::GetComponentView: ");

		const Signature signature = GetSignature<Ts...>();
		auto entities = m_entityManager.GetEntities(signature); // instead get sparse sets... get smallest , fetch all entites, compare to other sparse sets??

		ComponentView<Ts...> componentView{ FindOrCreateComponentManager<Ts>().GetContainer()..., std::move(entities) };
		return componentView;
	}

	template <ComponentType ...Ts, CallableReturns<bool, EntityHandle> Func>
	std::optional<ComponentView<Ts...>> World::GetComponentView(Func&& filtering) const
	{
		const Signature signature = GetSignature<Ts...>();
		const auto entities = m_entityManager.GetEntities(signature);
			
		bool hasAllComponentManagers = ((GetComponentManager<Ts>() != nullptr) && ...);
		if (!hasAllComponentManagers)
		{
			Logger::LogError("[World::GetComponentView(filtering)] - Failed to fetch component manager(s)!");
			return std::nullopt;
		}

		std::vector<Entity> filteredEntities;
		filteredEntities.reserve(entities.size());

		std::copy_if(entities.begin(), entities.end(), std::back_inserter(filteredEntities),
			[&](const Entity& entity)
			{
				return filtering(EntityHandle{ entity, this });
			});

		ComponentView<Ts...> componentView{ GetComponentManager<Ts>()->GetContainer()..., std::move(filteredEntities) };
		return componentView;
	}

	template <ComponentType ...Ts, CallableReturns<bool, EntityHandle> Func>
	ComponentView<Ts...> World::GetComponentView(Func&& filtering)
	{
		const Signature signature = GetSignature<Ts...>();
		const auto entities = m_entityManager.GetEntities(signature);

		std::vector<Entity> filteredEntities;
		filteredEntities.reserve(entities.size());

		std::copy_if(entities.begin(), entities.end(), std::back_inserter(filteredEntities), 
			[&](const Entity& entity) 
			{ 
				return filtering(EntityHandle{ entity, this });
			});

		ComponentView<Ts...> componentView{ FindOrCreateComponentManager<Ts>().GetContainer()..., std::move(filteredEntities) };
		return componentView;
	}

	template <ComponentType T>
	ComponentManager<T>& World::FindOrCreateComponentManager()
	{
		PROFILE_FUNCTION("World::FindOrCreateComponentManager: ");

		// check if null

		auto [it, success] = m_componentManagers.try_emplace(GetComponentID<T>(), nullptr);

		if (success)
		{
			it->second = std::make_unique<ComponentManager<T>>(); // safe to assign to iterator?
			Logger::LogInfo("ComponentManager created " + std::string(std::type_index(typeid(T)).name()));
		}

		//return *static_cast<ComponentManager<T>*>(it.first->second.get());
		return *static_cast<ComponentManager<T>*>(it->second.get()); // safe?
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
		PROFILE_FUNCTION("World::GetSignature: ");

		Signature signature;
		(signature.set(GetComponentID<Ts>()), ...);

		return signature;
	}

#pragma endregion Templated_Methods
}