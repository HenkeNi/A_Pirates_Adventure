#pragma once
#include "../Storage/ComponentArray.h"
#include "../Utility/ECSTypes.h"
#include "Logging/Logger.h"
#include "Utility/TypeTraits.h"

// TODO; add functions for serialize / deserialize all components?
// make component manager templated instead?

namespace Hi_Engine
{
	template <typename... Components>
	class ComponentView;

	class ComponentManager
	{
	public:
		ComponentManager();
		~ComponentManager();

		template <ComponentType T>
		void RegisterComponent();

		template <ComponentType T, typename... Args>
		void AddComponent(Entity entity, Args&&... args);

		template <ComponentType T>
		void RemoveComponent(Entity entity);

		void RemoveAllComponents(Entity entity);
		
		void Clear();

		template <ComponentType T>
		decltype(auto) GetComponents() const;

		template <ComponentType T>
		decltype(auto) GetComponents();

		template <ComponentType T>
		decltype(auto) GetComponent(Entity entity) const;

		template <ComponentType T>
		decltype(auto) GetComponent(Entity entity);

		template <ComponentType... Ts>
		std::vector<ComponentID> GetComponentIDs() const;

		template <ComponentType T>
		std::optional<ComponentID> GetComponentID() const;

	private:
		template <typename... Ts>
		friend class ComponentView;
		
		template <ComponentType T>
		const ComponentArray<T>* FindComponentArray() const;

		template <ComponentType T>
		ComponentArray<T>& GetComponentArray();

		ComponentArrays m_componentArrays;
		ComponentIDs m_componentIDs; // rename ComponentSignature?
		ComponentID m_nextComponentID;
	};

#pragma region Templated_Methods

	template <ComponentType T>
	void ComponentManager::RegisterComponent()
	{
		auto type = std::type_index(typeid(T));

		assert(m_componentArrays.find(type) == m_componentArrays.end() && "[ComponentManager::RegisterComponent] - Error: Component type already registered!");

		m_componentArrays.insert({ type, std::make_unique<ComponentArray<T>>() });
		m_componentIDs.insert({ type, m_nextComponentID });

		++m_nextComponentID;
	}

	template <ComponentType T, typename... Args>
	void ComponentManager::AddComponent(Entity entity, Args&&... args)
	{
		GetComponentArray<T>().AddComponent(entity, std::forward<Args>(args)...);
	}

	template <ComponentType T>
	void ComponentManager::RemoveComponent(Entity entity)
	{
		GetComponentArray<T>().RemoveComponent(entity);	
	}

	template <ComponentType T>
	decltype(auto) ComponentManager::GetComponents() const
	{
		return GetComponentArray<T>().GetComponents();
	}

	template <ComponentType T>
	decltype(auto) ComponentManager::GetComponents()
	{
		return GetComponentArray<T>().GetComponents();
	}

	template <ComponentType T>
	decltype(auto) ComponentManager::GetComponent(Entity entity) const
	{
		if (const auto* componentArray = FindComponentArray<T>())
		{
			return componentArray.GetComponent(entity);
		}

		return decltype(auto){};
	}

	template <ComponentType T>
	decltype(auto) ComponentManager::GetComponent(Entity entity)
	{
		return GetComponentArray<T>().GetComponent(entity); // why not same as above???????
	}

	template<ComponentType ...Ts>
	std::vector<ComponentID> ComponentManager::GetComponentIDs() const
	{
		std::vector<ComponentID> componentIDs;
		(componentIDs.push_back(GetComponentID<Ts>()), ...);

		return componentIDs;
	}

	template<ComponentType T>
	std::optional<ComponentID> ComponentManager::GetComponentID() const
	{
		auto type = std::type_index(typeid(T));
		auto iterator = m_componentIDs.find(type);

		if (iterator != m_componentIDs.end())
		{
			return iterator->second;
		}

		Logger::LogError("ComponentManager::GetComponentID - ComponentID: " + std::string(typeid(T).name()) + " not registered!");
		return std::nullopt;
	}

	template <ComponentType T>
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

	template <ComponentType T>
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

#pragma endregion Templated_Methods
}