#pragma once
#include "../Core/Modules/Module.h"
#include "Utility/ECSTypes.h"
#include "Utility/TypeTraits.h"
#include "Core/EntityManager.h"
#include "Core/ComponentManager.h"
#include "Core/ComponentView.h" // req for templated class?
#include "Core/SystemManager.h"
#include "Core/ComponentRegistry.h"

#include "Core/ComponentInitializer.h" // remove?

#include "Utility/DataStructures/SparseSet.h"
#include "../Core/Time/Timer.h"

// #include <functional>

// TODO; create an ECS message system?
// TODO: dont have ECS be a module, rename to World? and store directly in engine?
// maybe store ECS in scene (make part of engine?) or application

// TODO; systems caches signatures?


namespace Hi_Engine::ECS
{
	/*template <ComponentType T>
	SparseSet<T>& GetComponents()
	{
		static SparseSet<T> sparseSet;
		return sparseSet;
	}*/

}

namespace Hi_Engine
{
	class System;
	class Engine;

	class ECSCoordinator : public Module
	{
	public:
		ECSCoordinator(ModuleManager& manager);

		bool Init() override;

		std::optional<Entity> CreateEntity();

		void DestroyAllEntities();

		void DestroyEntity(Entity entity);


		//std::optional<Entity> CreateEntityFromPrefab(const char* type, bool notify = true); // pass string view (by value) instead?
		//std::optional<Entity> CreateEntityFromJson(const rapidjson::Value& jsonEntity);

		// REMOVE?
		//template <ComponentType... Ts, Callable<Entity, Entity> Comparator>
		//ComponentView<Ts...> GetComponentView(Comparator&& comparator); // dont allow sorting here? sort in system?

		template <ComponentType T> //template <ComponentType T, StringConvertible U>
		void RegisterComponent(auto&& name); // TODO; add type safety for auto? static function in registry class instead?

		template <ComponentType... Ts>
		void AddComponents(Entity entity); // take in data instead?

		template <ComponentType T, typename... Args>
		void AddComponent(Entity entity, Args&&... args);

		template <ComponentType T>
		void RemoveComponent(Entity entity);

		template <ComponentType... Ts>
		ComponentView<Ts...> GetComponentView() const;

		template <ComponentType... Ts>
		ComponentView<Ts...> GetComponentView();
	
		template <ComponentType T>
		const T* GetComponent(Entity entity) const;

		template <ComponentType T>
		T* GetComponent(Entity entity);

		template <DerivedFrom<System> T, typename... Args>
		void RegisterSystem(const char* name, Args&&... args); // remove name?

		template <ComponentType... Ts>
		Signature GetSignature() const;

		template <ComponentType... Ts>
		bool HasAllComponents(Entity entity) const;

		// HasAnyComponents

		bool IsAlive(Entity entity) const
		{
			return true;
		}

	private:
		template <ComponentType T>
		ComponentManager<T>& FindOrCreateComponentManager(); // Dont`?
		
		template <ComponentType T>
		const ComponentManager<T>* GetComponentManager() const;

		void Update(float deltaTime); // TEMP

		friend class Engine; // temP?

		EntityManager m_entityManager;

		std::unordered_map<ComponentID, std::unique_ptr<IComponentManager>> m_componentManagers;
		ComponentRegistry m_componentRegistry;

		SystemManager m_systemManager;
	};

#pragma region Templated_Methods

	template <ComponentType T>
	inline void ECSCoordinator::RegisterComponent(auto&& name)
	{
		// TODO; assert that component is trivial?

		m_componentRegistry.RegisterComponent<T>(name); // forward name? 

		//ComponentRegistryEntry entry;
		//entry.AddComponent = [this](Entity entity)
		//{
		//	AddComponents<T>(entity);
		//};
		//entry.InitializeComponent = [this](Entity entity, const ComponentProperties& properties)
		//{
		//	if (auto* component = m_componentManager.GetComponent<T>(entity))
		//		InitializeComponent(component, properties);
		//};

		//m_componentRegistry.insert({ std::forward<decltype(name)>(name), entry });
	}

	template <ComponentType... Ts>
	inline void ECSCoordinator::AddComponents(Entity entity)
	{
		(AddComponent<Ts>(entity), ...);
	}

	template<ComponentType T, typename... Args>
	inline void ECSCoordinator::AddComponent(Entity entity, Args&&... args)
	{
		auto& componentMananger = FindOrCreateComponentManager<T>();

		componentMananger.AddComponent(entity, std::forward<Args>(args)...);
		std::optional<Signature> optionalSignature = m_entityManager.GetSignature(entity);

		if (optionalSignature.has_value())
		{
			Signature signature = optionalSignature.value();
			signature.set(m_componentRegistry.GetComponentID<T>());

			m_entityManager.SetSignature(entity, signature);
		}
		else
		{
			Logger::LogError("[ECSCoordinator::AddComponent] - Failed to fetch correct signature for entity: " + std::to_string(entity));
		}
	}

	template <ComponentType T>
	inline void ECSCoordinator::RemoveComponent(Entity entity)
	{
		if (auto* componentManager = GetComponentManager<T>())
		{
			componentManager->RemoveComponent(entity);
			std::optional<Signature> optionalSignature = m_entityManager.GetSignature(entity);

			if (optionalSignature.has_value())
			{
				auto signature = optionalSignature.value();
				signature.set(m_componentRegistry.GetComponentID<T>(), false);

				m_entityManager.SetSignature(entity, signature);
			}
			else
			{
				Logger::LogWarning("[ECS::RemoveComponent] - Failed to find signature for entity " + std::to_string(entity));
			}
		}
		else
		{
			Logger::LogWarning("[ECS::RemoveComponent] - Failed to find component manager!");
		}
	}

	template<ComponentType ...Ts>
	inline ComponentView<Ts...> ECSCoordinator::GetComponentView() const
	{
		const Signature signature = GetSignature<Ts...>();
		auto entities = m_entityManager.GetEntities(signature);

		const ComponentView<Ts...> componentView{ FindOrCreateComponentManager<Ts>().GetSparseSet()..., std::move(entities) };
		return componentView;
	}

	template <ComponentType... Ts>
	inline ComponentView<Ts...> ECSCoordinator::GetComponentView()
	{
		const Signature signature = GetSignature<Ts...>();
		auto entities = m_entityManager.GetEntities(signature); // instead get sparse sets... get smallest , fetch all entites, compare to other sparse sets??

		ComponentView<Ts...> componentView{ FindOrCreateComponentManager<Ts>().GetSparseSet()..., std::move(entities)};
		return componentView;
	}

	template <ComponentType T>
	inline const T* ECSCoordinator::GetComponent(Entity entity) const
	{
		if (auto* componentManager = GetComponentManager<T>())
		{
			return componentManager->GetComponent(entity);
		}
		
		Logger::LogWarning("[ECS::GetComponent] - ComponentManager for type not found!");
		return nullptr;
	}

	template <ComponentType T>
	inline T* ECSCoordinator::GetComponent(Entity entity)
	{
		auto& componentManager = FindOrCreateComponentManager<T>(); // or always use GetComponentManager?
		return componentManager.GetComponent(entity);
	}

	template <DerivedFrom<System> T, typename... Args>
	inline void ECSCoordinator::RegisterSystem(const char* name, Args&&... args)
	{
		auto system = std::make_shared<T>(*this, std::forward<Args>(args)...);
		m_systemManager.AddSystem(std::move(system));
	}

	template <ComponentType... Ts>
	inline Signature ECSCoordinator::GetSignature() const
	{
		Signature signature;
		(signature.set(m_componentRegistry.GetComponentID<Ts>()), ...);

		return signature;
	}

	template <ComponentType... Ts>
	inline bool ECSCoordinator::HasAllComponents(Entity entity) const
	{
		std::optional<Signature> entitySignature = m_entityManager.GetSignature(entity);

		if (entitySignature.has_value())
		{
			Signature componentSignature;
			(componentSignature.set(m_componentRegistry.GetComponentID<Ts>().value_or(0)), ...);

			return (entitySignature.value() & componentSignature) == componentSignature;
		}

		return false;
	}

	template <ComponentType T>
	ComponentManager<T>& ECSCoordinator::FindOrCreateComponentManager()
	{
		ComponentID id = m_componentRegistry.GetComponentID<T>();

		auto it = m_componentManagers.try_emplace(id, std::make_unique<ComponentManager<T>>());

		if (it.second)
		{
			auto type = std::type_index(typeid(T));
			Logger::LogInfo("ComponentManager created " + std::string(type.name()));
		}

		return *static_cast<ComponentManager<T>*>(it.first->second.get());
	}

	template <ComponentType T>
	const ComponentManager<T>* ECSCoordinator::GetComponentManager() const
	{
		auto id = m_componentRegistry.GetComponentID<T>();
		auto it = m_componentManagers.find(id);

		if (it != m_componentManagers.end())
		{
			return static_cast<ComponentManager<T>*>(it->second.get());
		}

		return nullptr;
	}

#pragma endregion Templated_Methods
}