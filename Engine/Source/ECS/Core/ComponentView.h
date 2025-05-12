#pragma once
#include "../Utility/ECSTypes.h"
#include "ComponentManager.h"
#include "../../Core/Utility/DataStructures/SparseSet.h"


namespace Hi_Engine
{
	// Consider;
	//  * caching component view (pass in sparse set, but pass in entities each frame?)
	//  * add sorting? and predicate (for ForEach) as optional, or separate function

	template <ComponentType... Ts>
	class ComponentView
	{
	public:
		// ==================== Construction/Destruction ====================
		ComponentView(ComponentContainer<Ts>&... containers, std::vector<EntityID>&& entities);
		~ComponentView() = default;

		ComponentView(const ComponentView&) = default;
		ComponentView(ComponentView&&) noexcept = default;

		ComponentView& operator=(const ComponentView&) = default;
		ComponentView& operator=(ComponentView&&) noexcept = default;

		// ==================== Core API ====================
		// Iteration
		template <typename Callback>  // TODO; replace typename with Callable (<Callable<Ts...>>), assure (force) reference? add predicate (ForEach if...)
		void ForEach(Callback&& callback) const;

		template <typename Callback>
		void ForEach(Callback&& callback);

		// Random Access
		template <ComponentType T>
		const T* GetComponent(EntityID id) const; // OR VALID CHECK ENTITY??!

		template <ComponentType T>
		T* GetComponent(EntityID id);

		// ==================== Queries ====================
		[[nodiscard]] bool Contains(EntityID id) const noexcept;

		[[nodiscard]] bool IsEmpty() const noexcept;

		[[nodiscard]] std::size_t size() const noexcept;

		inline const std::vector<Entity>& GetEntities() const { return m_entities; }

		// ==================== Search ====================
		template <typename Predicate> // template <Callable Func>
		std::optional<Entity> FindIf(Predicate&& predicate) const;

		template <typename Predicate>
		std::vector<Entity> FindAllIf(Predicate&& predicate) const;

		// ==================== Iterators ====================
		class Iterator
		{
		public:
			Iterator(ComponentView* view, std::size_t index = 0);

			Iterator& operator++();
			
			bool operator!=(const Iterator& other) const;

			const std::tuple<Ts*...> operator*() const;

			std::tuple<Ts*...> operator*();

		private:
			ComponentView* m_view;
			std::size_t m_index;
		};

		Iterator begin() { return Iterator(this); }
		Iterator end() { return Iterator(this, m_entities.size()); }

	private:
		// ==================== Helpers ====================
		std::tuple<Ts*...> GetComponents(EntityID id) const;

		// ==================== Data Members ====================
		std::tuple<ComponentContainer<Ts>&...> m_components; // or component managers??	
		const std::vector<EntityID> m_entities;

		// std::vector<std::tuple<Entity, Ts*...>> m_cache;
	};

#pragma region Templated_Methods

	template <ComponentType... Ts>
	ComponentView<Ts...>::ComponentView(ComponentContainer<Ts>&... containers, std::vector<EntityID>&& entities)
		: m_components{ containers... }, m_entities{ std::forward<std::vector<EntityID>>(entities) }
	{
	}

	template <ComponentType ...Ts>
	template <typename Callback>
	void ComponentView<Ts...>::ForEach(Callback&& callback) const
	{
		// try parallell version...
		std::for_each(m_entities.begin(), m_entities.end(), [&](EntityID id)
		{
			if constexpr (requires { { callback(std::get<ComponentContainer<Ts>&>(m_components).At(id)...) } -> std::same_as<bool>; })
			{
				if (!callback(std::get<ComponentContainer<Ts>&>(m_components).At(id)...))
				{
					return;
				}
			}
			else
			{
				callback(std::get<ComponentContainer<Ts>&>(m_components).At(id)...); // pass in entity id? ... func(std::as_const(comps)...);  // const Ts&...
			}
		});
	}

	template <ComponentType ...Ts>
	template <typename Callback>
	void ComponentView<Ts...>::ForEach(Callback&& callback)
	{
		std::for_each(m_entities.begin(), m_entities.end(), [&](EntityID id)
		{
			if constexpr (requires { { callback(std::get<ComponentContainer<Ts>&>(m_components).At(id)...) } -> std::same_as<bool>; })
			{
				if (!callback(std::get<ComponentContainer<Ts>&>(m_components).At(id)...))
				{
					return;
				}
			}
			else
			{
				callback(std::get<ComponentContainer<Ts>&>(m_components).At(id)...); // pass in entity? ... func(std::as_const(comps)...);  // const Ts&...
			}
		});
	}

	template <ComponentType ...Ts>
	template <ComponentType T>
	const T* ComponentView<Ts...>::GetComponent(EntityID id) const
	{
		auto& container = std::get<ComponentContainer<T>&>(m_components); // const cast instead?
		return container.Get(id);
	}

	template <ComponentType ...Ts>
	template <ComponentType T>
	T* ComponentView<Ts...>::GetComponent(EntityID id)
	{
		auto& container = std::get<ComponentContainer<T>&>(m_components);
		return container.Get(id);
	}

	template<ComponentType ...Ts>
	template<typename Predicate>
	std::vector<Entity> ComponentView<Ts...>::FindAllIf(Predicate&& predicate) const
	{
		assert(false && "NOT IMPLEMENTED");

		return std::vector<Entity>{};
	}

	template <ComponentType ...Ts>
	template <typename Predicate>
	std::optional<Entity> ComponentView<Ts...>::FindIf(Predicate&& predicate) const
	{
		assert(false && "NOT IMPLEMENTED");
		// TODO; add iterator?

		// auto sparseSet = std::get<SparseSet<T>&>(m_components); -> dont iterate over sparse set? (req an iterator)

		//return std::find_if
		return nullptr;
	}

	template <ComponentType ...Ts>
	bool ComponentView<Ts...>::Contains(EntityID entity) const noexcept
	{
		return std::find(m_entities.begin(), m_entities.end(), entity) != m_entities.end();
	}

	template <ComponentType ...Ts>
	bool ComponentView<Ts...>::IsEmpty() const noexcept
	{
		return m_entities.empty();
	}

	template <ComponentType... Ts>
	std::size_t ComponentView<Ts...>::size() const noexcept
	{
		return m_entities.size();
	}

	template <ComponentType ...Ts>
	std::tuple<Ts*...> ComponentView<Ts...>::GetComponents(EntityID id) const
	{
		return { std::get<ComponentContainer<Ts>&>(m_components).Get(id)... };
	}

	template <ComponentType ...Ts>
	ComponentView<Ts...>::Iterator::Iterator(ComponentView* view, std::size_t index)
		: m_view{ view }, m_index{ index }
	{
	}

	template <ComponentType ...Ts>
	typename ComponentView<Ts...>::Iterator& ComponentView<Ts...>::Iterator::operator++()
	{
		++m_index;
		return *this;
	}

	template <ComponentType ...Ts>
	bool ComponentView<Ts...>::Iterator::operator!=(const Iterator& other) const
	{
		return m_index != other.m_index;
	}

	template <ComponentType ...Ts>
	const std::tuple<Ts*...> ComponentView<Ts...>::Iterator::operator*() const
	{
		return m_view->GetComponents(m_view->m_entities[m_index]);
	}

	template <ComponentType ...Ts>
	std::tuple<Ts*...> ComponentView<Ts...>::Iterator::operator*()
	{
		return m_view->GetComponents(m_view->m_entities[m_index]);
	}

#pragma endregion
}