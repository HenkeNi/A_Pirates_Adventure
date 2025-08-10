#pragma once
#include "../Utility/ECSTypes.h"
#include "../Utility/Entity.h"
#include "../../Core/Utility/DataStructures/SparseSet.h"
#include <execution>

namespace Hi_Engine
{
	// [Consider] - replacing SparseSet with ComponentMananger (hide impl)
	//  * caching component view (pass in sparse set, but pass in entities each frame?)
	//  * add sorting? and predicate (for ForEach) as optional, or separate function

	template <ComponentType... Ts>
	class ComponentView
	{
	public:
		// ==================== Construction/Destruction ====================
		ComponentView(ComponentContainer<Ts>&... containers, std::vector<Entity>&& entities);
		~ComponentView() = default;

		ComponentView(const ComponentView&) = default;
		ComponentView(ComponentView&&) noexcept = default;

		ComponentView& operator=(const ComponentView&) = default;
		ComponentView& operator=(ComponentView&&) noexcept = default;

		// ==================== Core API ====================
		template <typename Callback>  // TODO; replace typename with Callable (<Callable<Ts...>>), assure (force) reference? add predicate (ForEach if...)
		void ForEach(Callback&& callback) const;

		template <typename Callback>
		void ForEach(Callback&& callback);

		template <ComponentType T>
		[[nodiscard]] const T* GetComponent(EntityID id) const;

		template <ComponentType T>
		[[nodiscard]] T* GetComponent(EntityID id);

		// ==================== Queries ====================
		[[nodiscard]] bool Contains(EntityID id) const noexcept;

		[[nodiscard]] bool IsEmpty() const noexcept;

		[[nodiscard]] std::size_t Size() const noexcept;

		[[nodiscard]] inline const std::vector<Entity>& GetEntities() const { return m_entities; }

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
		std::tuple<const Ts&...> GetComponents(EntityID id) const;
		
		std::tuple<Ts&...> GetComponents(EntityID id);

		// ==================== Data Members ====================
		std::tuple<ComponentContainer<Ts>&...> m_components; // store manager instad? (hide implementation)
		const std::vector<Entity> m_entities; // store entity handles instead?

		// std::vector<std::tuple<Entity, Ts*...>> m_cache;
	};

#pragma region Templated_Methods

	template <ComponentType... Ts>
	ComponentView<Ts...>::ComponentView(ComponentContainer<Ts>&... containers, std::vector<Entity>&& entities)
		: m_components{ containers... }, m_entities{ std::move(entities) }
	{
	}

	template <ComponentType... Ts>
	template <typename Callback>
	void ComponentView<Ts...>::ForEach(Callback&& callback) const 
	{
		// For now, don't allow entity to be last argument...
		static_assert(!std::invocable<Callback, Ts&..., Entity> && "Entity can't be last argument in callback!");

		constexpr bool hasEntityParam = std::invocable<Callback, Entity, Ts&...>;

		for (const auto& entity : m_entities)
		{
			auto components = GetComponents(entity.ID);

			if constexpr (hasEntityParam)
			{
				// Check if Callback returns bool (breakable)
				if constexpr (std::is_invocable_r_v<bool, Callback, Entity, Ts&...>)
				{
					if (!std::apply([&](auto&&... components) { return std::invoke(callback, entity, components...); }, components))
					{
						break;
					}

				}
				else
				{
					std::apply([&](auto&&... components) { return std::invoke(callback, entity, components...); }, components);
				}
			}
			else
			{
				// Check if Callback returns bool (breakable)
				if constexpr (std::is_invocable_r_v<bool, Callback, Ts&...>)
				{
					if (!std::apply(callback, components))
					{
						break;
					}
				}
				else
				{
					std::apply(callback, components);
				}
			}
		}
	}

	template <ComponentType... Ts>
	template <typename Callback>
	void ComponentView<Ts...>::ForEach(Callback&& callback) 
	{
		static_assert(!std::invocable<Callback, Ts&..., Entity> && "Entity can't be last argument in callback!");

		constexpr bool hasEntityParam = std::invocable<Callback, Entity, Ts&...>;
		
		// TODO; make functions safe for parallization... (Seq) seems to be fastest approach

		std::for_each(std::execution::seq, m_entities.begin(), m_entities.end(),
			[&](const Entity& entity) {
				auto components = GetComponents(entity.ID);

				if constexpr (hasEntityParam)
				{
					// Check if Callback returns bool (breakable)
					if constexpr (std::is_invocable_r_v<bool, Callback, Entity, Ts&...>)
					{
						if (!std::apply([&](auto&&... components) { return std::invoke(callback, entity, components...); }, components))
						{
							break;
						}
					}
					else
					{
						std::apply([&](auto&&... components) { return std::invoke(callback, entity, components...); }, components);
					}
				}
				else
				{
					// Check if Callback returns bool (breakable)
					if constexpr (std::is_invocable_r_v<bool, Callback, Ts&...>)
					{
						if (!std::apply(callback, components))
						{
							break;
						}
					}
					else
					{
						std::apply(callback, components);
					}
				}
			});
	}

	template <ComponentType... Ts>
	template <ComponentType T>
	const T* ComponentView<Ts...>::GetComponent(EntityID id) const
	{
		return std::get<ComponentContainer<T>&>(m_components).Get(id);
	}

	template <ComponentType... Ts>
	template <ComponentType T>
	T* ComponentView<Ts...>::GetComponent(EntityID id)
	{
		return const_cast<T*>(std::as_const(*this).template GetComponent<T>(id));
	}

	template<ComponentType... Ts>
	template<typename Predicate>
	std::vector<Entity> ComponentView<Ts...>::FindAllIf(Predicate&& predicate) const
	{
		assert(false && "NOT IMPLEMENTED");

		return std::vector<Entity>{};
	}

	template <ComponentType... Ts>
	template <typename Predicate>
	std::optional<Entity> ComponentView<Ts...>::FindIf(Predicate&& predicate) const // return pair?
	{
		//assert(false && "NOT IMPLEMENTED");

		for (const auto& entity : m_entities)
		{
			if (predicate(std::get<ComponentContainer<Ts>&>(m_components).At(entity.ID)...))
				return entity;
		}

		// TODO; return EntityHandle...?

		// TODO; add iterator?

		// auto sparseSet = std::get<SparseSet<T>&>(m_components); -> dont iterate over sparse set? (req an iterator)

		//return std::find_if
		return std::nullopt;
	}

	template <ComponentType... Ts>
	bool ComponentView<Ts...>::Contains(EntityID id) const noexcept
	{
		return std::find(m_entities.begin(), m_entities.end(), id) != m_entities.end();
	}

	template <ComponentType... Ts>
	bool ComponentView<Ts...>::IsEmpty() const noexcept
	{
		return m_entities.empty();
	}

	template <ComponentType... Ts>
	std::size_t ComponentView<Ts...>::Size() const noexcept
	{
		return m_entities.size();
	}

	template <ComponentType... Ts>
	std::tuple<const Ts&...> ComponentView<Ts...>::GetComponents(EntityID id) const
	{
		return std::tie(std::get<ComponentContainer<Ts>&>(m_components).At(id)...);
	}

	template <ComponentType ...Ts>
	std::tuple<Ts&...> ComponentView<Ts...>::GetComponents(EntityID id)
	{
		return std::tie(std::get<ComponentContainer<Ts>&>(m_components).At(id)...);
	}

	template <ComponentType... Ts>
	ComponentView<Ts...>::Iterator::Iterator(ComponentView* view, std::size_t index)
		: m_view{ view }, m_index{ index }
	{
	}

	template <ComponentType... Ts>
	typename ComponentView<Ts...>::Iterator& ComponentView<Ts...>::Iterator::operator++()
	{
		++m_index;
		return *this;
	}

	template <ComponentType... Ts>
	bool ComponentView<Ts...>::Iterator::operator!=(const Iterator& other) const
	{
		return m_index != other.m_index;
	}

	template <ComponentType... Ts>
	const std::tuple<Ts*...> ComponentView<Ts...>::Iterator::operator*() const
	{
		return m_view->GetComponents(m_view->m_entities[m_index]);
	}

	template <ComponentType... Ts>
	std::tuple<Ts*...> ComponentView<Ts...>::Iterator::operator*()
	{
		return m_view->GetComponents(m_view->m_entities[m_index]);
	}

#pragma endregion
}