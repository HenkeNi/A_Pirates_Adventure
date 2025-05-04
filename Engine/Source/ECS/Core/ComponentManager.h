#pragma once
#include "../../Core/Utility/DataStructures/SparseSet.h"
#include "../Utility/ECSTypes.h"
#include "../Utility/Entity.h"
#include "Logging/Logger.h"
#include "Utility/TypeTraits.h"

// TODO; add functions for serialize / deserialize all components? NOT HERE!

namespace Hi_Engine
{
	class IComponentManager
	{
	public:
		virtual ~IComponentManager() = default;

		virtual void RemoveComponent(EntityID id) = 0;
		virtual void RemoveAllComponents() = 0;
	};

	template <ComponentType T>
	class ComponentManager : public IComponentManager
	{
	public:
		// pass in component registry class? (ref)

		template <typename... Args>
		bool AddComponent(EntityID id, Args&&... args);

		void RemoveComponent(EntityID id) override;

		void RemoveAllComponents() override;

		decltype(auto) GetComponent(EntityID id) const;

		decltype(auto) GetComponent(EntityID id);

		decltype(auto) GetComponents() const; // remvoe? or return the sparse set instead?

		decltype(auto) GetComponents();

		const ComponentContainer<T>& GetSparseSet() const { return m_components; }

		ComponentContainer<T>& GetSparseSet() { return m_components; }

	private:
		ComponentContainer<T> m_components;
		//SparseSet<std::decay_t<T>, EntityID> m_components;
	};

#pragma region Templated_Methods

	template <ComponentType T>
	template <typename... Args>
	bool ComponentManager<T>::AddComponent(EntityID id, Args&&... args)
	{
		return m_components.Emplace(id, std::forward<Args>(args)...);
	}

	template <ComponentType T>
	void ComponentManager<T>::RemoveComponent(EntityID id)
	{
		m_components.Remove(id);
	}

	template <ComponentType T>
	void ComponentManager<T>::RemoveAllComponents()
	{
		m_components.Clear();
	}

	template <ComponentType T>
	decltype(auto) ComponentManager<T>::GetComponent(EntityID id) const
	{
		return m_components.Get(id);
	}

	template <ComponentType T>
	decltype(auto) ComponentManager<T>::GetComponent(EntityID id)
	{
		return m_components.Get(id);
	}

	template <ComponentType T>
	decltype(auto) ComponentManager<T>::GetComponents() const
	{
		return m_components.Data(); // return sparse set?
	}

	template <ComponentType T>
	decltype(auto) ComponentManager<T>::GetComponents()
	{
		return m_components.Data();
	}

#pragma endregion
}