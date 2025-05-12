#pragma once
#include "Utility/ECSTypes.h"
#include "Utility/TypeTraits.h"
#include "Core/EntityManager.h"

#include "Core/ComponentManager.h"
#include "Core/ComponentView.h" // req for templated class?
#include "Utility/DataStructures/SparseSet.h" // -> NEEDED?

#include "Registry/ComponentRegistry.h"
#include "ECSRegistry.h"

//#include "Core/ComponentInitializer.h" // remove?
//#include "../Core/Time/Timer.h"

// Consider;
// TODO; create an ECS message system?
// maybe store ECS in scene (make part of engine?) or application

// TODO; systems caches signatures?
// Each scene has a (ECS)world? can transfer entities?

// TODO; cache already created ComponentView's in "Groups"
// TODO; Cache component view (groups)? when created, cache them in a map (key == signature?) -> groups listen to various entity events?

// Maybe world is not part of the ECS???
// contains a Registry class? (register system(s); components, etc)?

// ECS::Core instead?

namespace Hi_Engine
{
	class ECSCore
	{
	public:
		std::optional<Entity> CreateEntity();

		void DestroyAllEntities();

		void DestroyEntity(const Entity& entity);

		template <ComponentType... Ts>
		void AddComponents(const Entity& entity);

		template <ComponentType T, typename... Args>
		void AddComponent(const Entity& entity, Args&&... args);

		template <ComponentType T>
		void RemoveComponent(const Entity& entity);

		template <ComponentType... Ts>
		ComponentView<Ts...> GetComponentView() const;

		template <ComponentType... Ts>
		ComponentView<Ts...> GetComponentView();
	
		template <ComponentType T>
		const T* GetComponent(const Entity& entity) const; // make sure to version check entity!

		template <ComponentType T>
		T* GetComponent(const Entity& entity); // or just iD??

		// more Get component functions (T& etc...)

		template <ComponentType... Ts>
		Signature GetSignature() const;

		template <ComponentType... Ts>
		bool HasAllComponents(EntityID id) const;

		template <ComponentType... Ts>
		bool HasAnyComponent(EntityID id) const; // TODO; TEST!

		bool IsAlive(const Entity& entity) const;

	private:
		template <ComponentType T>
		ComponentManager<T>& FindOrCreateComponentManager(); // Dont`?
		
		template <ComponentType T>
		const ComponentManager<T>* GetComponentManager() const;

		EntityManager m_entityManager;
		ComponentManagerMap m_componentManagers;
	};

#pragma region Templated_Methods

	template <ComponentType... Ts>
	void ECSCore::AddComponents(const Entity& entity)
	{
		(AddComponent<Ts>(entity), ...);
	}

	template<ComponentType T, typename... Args>
	void ECSCore::AddComponent(const Entity& entity, Args&&... args)
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
			signature.set(ECSRegistry::GetComponentRegistry.GetComponentID<T>());

			m_entityManager.SetSignature(entity, signature);
		}
		else
		{
			Logger::LogError("[ECSCoordinator::AddComponent] - Failed to fetch correct signature for entity: " + std::to_string(entity.ID));
		}
	}

	template <ComponentType T>
	void ECSCore::RemoveComponent(const Entity& entity)
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
				signature.set(ECSRegistry::GetComponentRegistry().GetComponentID<T>(), false);

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

	template<ComponentType ...Ts>
	ComponentView<Ts...> ECSCore::GetComponentView() const
	{
		const Signature signature = GetSignature<Ts...>();
		auto entities = m_entityManager.GetEntities(signature);

		const ComponentView<Ts...> componentView{ FindOrCreateComponentManager<Ts>().GetContainer()..., std::move(entities) };
		return componentView;
	}

	template <ComponentType... Ts>
	ComponentView<Ts...> ECSCore::GetComponentView()
	{
		const Signature signature = GetSignature<Ts...>();
		auto entities = m_entityManager.GetEntities(signature); // instead get sparse sets... get smallest , fetch all entites, compare to other sparse sets??

		ComponentView<Ts...> componentView{ FindOrCreateComponentManager<Ts>().GetContainer()..., std::move(entities)};
		return componentView;
	}

	template <ComponentType T>
	const T* ECSCore::GetComponent(const Entity& entity) const
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
	T* ECSCore::GetComponent(const Entity& entity)
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
	Signature ECSCore::GetSignature() const
	{
		Signature signature;
		(signature.set(ECSRegistry::GetComponentRegistry().GetComponentID<Ts>()), ...);

		return signature;
	}

	template <ComponentType... Ts>
	bool ECSCore::HasAllComponents(EntityID id) const
	{
		std::optional<Signature> entitySignature = m_entityManager.GetSignature(id);

		if (entitySignature.has_value())
		{
			Signature componentSignature;
			(componentSignature.set(ECSRegistry::GetComponentRegistry().GetComponentID<Ts>().value_or(0)), ...);

			return (entitySignature.value() & componentSignature) == componentSignature;
		}

		Logger::LogWarning("[ECS::HasAllComponents] - Failed to find entity signature!");
		return false;
	}

	template<ComponentType ...Ts>
	bool ECSCore::HasAnyComponent(EntityID id) const
	{
		std::optional<Signature> optionalSignature = m_entityManager.GetSignature(id);

		if (optionalSignature.has_value())
		{
			Signature componentSignature;
			(componentSignature.set(ECSRegistry::GetComponentRegistry().GetComponentID<Ts>().value_or(0)), ...);

			return (optionalSignature.value() & componentSignature).any();
		}

		Logger::LogWarning("[ECS::HasAnyComponent] - Failed to find entity signature!");
		return false;
	}

	template <ComponentType T>
	ComponentManager<T>& ECSCore::FindOrCreateComponentManager()
	{
		ComponentID id = ECSRegistry::GetComponentRegistry().GetComponentID<T>();

		auto it = m_componentManagers.try_emplace(id, std::make_unique<ComponentManager<T>>());

		if (it.second)
		{
			auto type = std::type_index(typeid(T));
			Logger::LogInfo("ComponentManager created " + std::string(type.name()));
		}

		return *static_cast<ComponentManager<T>*>(it.first->second.get());
	}

	template <ComponentType T>
	const ComponentManager<T>* ECSCore::GetComponentManager() const
	{
		auto id = ECSRegistry::GetComponentRegistry().GetComponentID<T>();
		auto it = m_componentManagers.find(id);

		if (it != m_componentManagers.end())
		{
			return static_cast<ComponentManager<T>*>(it->second.get());
		}

		return nullptr;
	}

#pragma endregion Templated_Methods
}