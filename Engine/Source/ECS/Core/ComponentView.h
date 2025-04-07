#pragma once
#include "../Utility/ECSTypes.h"
#include "ComponentManager.h"
#include "../../Core/Utility/DataStructures/SparseSet.h"

// TODO; check if const version of get component is ever run (in Component Array)

// allow random access... 
// Add groups that stored indexes to components?
// groups stores entities relevant (and indexes to components?)

namespace Hi_Engine
{
	class Group
	{

	};

	// both single view component and not?  Implement ComponentView<T>


	template <ComponentType... Ts>
	class ComponentView
	{
	public:
		ComponentView(SparseSet<Ts>&... sets, std::vector<Entity>&& entities);
		//ComponentView(ComponentManager<Ts>*... managers, std::vector<Entity>&& entities);

		std::size_t size() const;

		// Use a foreach function instead of providing access to components directly? pass in function?
		template <ComponentType T> //// NEEDED?? maybe onyl allow access through view??
		T* GetComponent(Entity entity) const
		{
			auto& components = std::get<SparseSet<T>&>(m_components);
			return components.Get(entity);

			//if (auto* componentManager = std::get<ComponentManager<T>*>(m_componentManagers))
			//{
			//	return componentManager->GetComponent(entity);
			//}

			//return nullptr;
			// 

			//auto sparseSet = std::get<SparseSet<Component>&>(m_components);
			// return sparseSet->Get(entity);
		}


		// template <Callable<Ts...>> // do this instead?? or to restricting? 

		template <typename Callback>
		void ForEach(Callback&& callback) const
		{
			std::for_each(m_entities.begin(), m_entities.end(), [&](Entity entity)
				{
					//callback(GetComponent<Ts>(entity)...);
					callback(std::get<SparseSet<Ts>&>(m_components).Get(entity)...); // pass in entity? ... func(std::as_const(comps)...);  // const Ts&...
				});
		}

		// TODO; pass in entity as well? will break / return work?
		template <typename Callback> // force reference? or force pointer for components??
		void ForEach(Callback&& callback)
		{			
			// overload parallel version?
			std::for_each(m_entities.begin(), m_entities.end(), [&](Entity entity) 
			{
				//callback(GetComponent<Ts>(entity)...);
				callback(std::get<SparseSet<Ts>&>(m_components).Get(entity)...); // pass in entity? dont "Get" return a pointer? but callback might request a ref?
			});
		}

		// Test... /return component or entity? 
		//template <Callable Func>
		template <typename Func> // TODO; change to Callable concept...
		std::optional<Entity> FindIf(Func&& function) const
		{
			// TODO; add iterator?

			// auto sparseSet = std::get<SparseSet<T>&>(m_components); -> dont iterate over sparse set? (req an iterator)

			//return std::find_if
			return nullptr;
		}
		// return entity or component?


		class Iterator
		{
		public:
			Iterator(std::size_t index, const std::vector<Entity>& entities, std::tuple<SparseSet<Ts>&...>& components)
				: m_index{ index }, m_entities{ entities }, m_components{ components }
			{
			}

			Iterator& operator++()
			{
				++m_index;
				return *this;
			}

			bool operator!=(const Iterator& other) const
			{
				return m_index != other.m_index;
			}

			const std::tuple<Ts*...> operator*() const
			{
				std::tuple<Ts*...> components{ GetComponent<Ts>(m_entities[m_index])... };
				return components;
			}

			std::tuple<Ts*...> operator*()
			{
				// use forward as tuple????
				std::tuple<Ts*...> components{ GetComponent<Ts>(m_entities[m_index])... };
				return components;
			}

		private:
			template <ComponentType T>
			T* GetComponent(Entity entity) const
			{
				auto& sparseSet = std::get<SparseSet<T>&>(m_components);
				return sparseSet.Get(entity);
			}

			std::size_t m_index;
			const std::vector<Entity>& m_entities;
			std::tuple<SparseSet<Ts>&...>& m_components;
		};

		Iterator begin() { return Iterator(0, m_entities, m_components); }
		Iterator end() { return Iterator(m_entities.size(), m_entities, m_components); }


	private:
		std::tuple<SparseSet<Ts>&...> m_components; // alt: use component manager(s)

		//std::tuple<ComponentManager<Ts>*...> m_componentManagers;
		const std::vector<Entity> m_entities;
	};

	template <ComponentType T> // TEST!	
	class ComponentView<T>
	{
	public:
		ComponentView(SparseSet<T>& components, std::vector<Entity>&& entities)
			: m_components{ components }, m_entities{ entities }
		{
		}

		template <typename Callback> // use concept...! 
		void ForEach(Callback&& callback)
		{
			// overload parallel version?
			std::for_each(m_entities.begin(), m_entities.end(), [&](Entity entity)
				{
					//callback(GetComponent<Ts>(entity)...);
					callback(*m_components.Get(entity)); // FIX ref / pointer
				});
		}

	private:
		SparseSet<T>& m_components;
		const std::vector<Entity> m_entities;
	};

	template <ComponentType... Ts>
	ComponentView<Ts...>::ComponentView(SparseSet<Ts>&... sets, std::vector<Entity>&& entities)
		: m_components{ sets... }, m_entities{ std::forward<std::vector<Entity>>(entities) }
	{
	}

	template <ComponentType... Ts>
	inline std::size_t ComponentView<Ts...>::size() const
	{
		return m_entities.size();
	}
}