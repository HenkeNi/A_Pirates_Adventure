#pragma once
#include "../Utility/ECSTypes.h"
#include "ComponentManager.h"

// TODO; check if const version of get component is ever run (in Component Array)

namespace Hi_Engine
{
	template <typename... Components>
	class ComponentView
	{
	public:
		ComponentView(ComponentManager& componentManager, std::vector<Entity>&& entities);

		std::size_t size() const;

		// Use a foreach function instead of providing access to components directly? pass in function?
		template <typename Component>
		Component* GetComponent(Entity entity) const
		{
			auto componentArray = std::get<ComponentArray<Component>*>(m_componentArrays);
			return componentArray->GetComponent(entity);
		}

		// TODO; provide const version?
		template <typename Callback>
		void ForEach(Callback&& callback)
		{			
			// overload parallel version?
			std::for_each(m_entities.begin(), m_entities.end(), [&](Entity entity) 
			{
				callback(GetComponent<Components>(entity)...);
			});
		}

		class Iterator
		{
		public:
			Iterator(std::size_t index, const std::vector<Entity>& entities, std::tuple<ComponentArray<Components>*...>& componentArrays);

			Iterator& operator++();

			bool operator!=(const Iterator& other) const;

			const std::tuple<Components*...> operator*() const;

			std::tuple<Components*...> operator*();

		private:
			template <typename Component>
			Component* GetComponent(Entity entity) const;

			std::size_t m_index;
			const std::vector<Entity>& m_entities;
			std::tuple<ComponentArray<Components>*...>& m_componentArrays;

		};

		Iterator begin() { return Iterator(0, m_entities, m_componentArrays); }
		Iterator end() { return Iterator(m_entities.size(), m_entities, m_componentArrays); }

	private:
		std::tuple<ComponentArray<Components>*...> m_componentArrays;
		const std::vector<Entity> m_entities;
	};

	template <typename... Components>
	ComponentView<Components...>::ComponentView(ComponentManager& componentManager, std::vector<Entity>&& entities)
		: m_componentArrays{ std::make_tuple(&componentManager.GetComponentArray<Components>()...) }, m_entities{ std::move(entities) }
	{
	}

	template<typename ...Components>
	inline std::size_t ComponentView<Components...>::size() const
	{
		return m_entities.size();
	}

	template <typename... Components>
	ComponentView<Components...>::Iterator::Iterator(std::size_t index, const std::vector<Entity>& entities, std::tuple<ComponentArray<Components>*...>& componentArrays)
		: m_index{ index }, m_entities{ entities }, m_componentArrays{ componentArrays }
	{
	}

	template <typename... Components>
	typename ComponentView<Components...>::Iterator& ComponentView<Components...>::Iterator::operator++()
	{
		++m_index;
		return *this;
	}

	template <typename... Components>
	bool ComponentView<Components...>::Iterator::operator!=(const Iterator& other) const
	{
		return m_index != other.m_index;
	}

	template <typename... Components>
	const std::tuple<Components*...> ComponentView<Components...>::Iterator::operator*() const
	{
		std::tuple<Components*...> components{ GetComponent<Components>(m_entities[m_index])... };
		return components;
	}

	template <typename... Components>
	std::tuple<Components*...> ComponentView<Components...>::Iterator::operator*()
	{
		std::tuple<Components*...> components{ GetComponent<Components>(m_entities[m_index])... };
		return components;
	}

	template <typename... Components>
	template <typename Component>
	inline Component* ComponentView<Components...>::Iterator::GetComponent(Entity entity) const
	{
		auto componentArray = std::get<ComponentArray<Component>*>(m_componentArrays);
		return componentArray->GetComponent(entity);
	}
}