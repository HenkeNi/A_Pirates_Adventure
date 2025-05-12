#pragma once
#include "../../Core/Utility/DataStructures/SparseSet.h"
#include "../Utility/ECSTypes.h"
#include "../Utility/Entity.h"
#include "Logging/Logger.h"
#include "Utility/TypeTraits.h"



namespace Hi_Engine
{
	class IComponentManager
	{
	public:
		virtual ~IComponentManager() = default;

		// ==================== Component Management ====================
		virtual void RemoveComponent(EntityID id) = 0;
		virtual void RemoveComponents(const std::vector<EntityID>& ids) = 0;
		virtual void RemoveAllComponents() = 0;

		// ==================== Queries ====================
		[[nodiscard]] virtual std::size_t GetComponentCount() const noexcept = 0;
		[[nodiscard]] virtual bool HasComponent(EntityID id) const = 0;
	};

	template <ComponentType T>
	class ComponentManager : public IComponentManager
	{
	public:
		// ==================== Construction/Destruction ====================
		ComponentManager() = default;
		~ComponentManager() override = default;

		ComponentManager(const ComponentManager&) = delete;
		ComponentManager(ComponentManager&&) = default;

		ComponentManager& operator=(const ComponentManager&) = delete;
		ComponentManager& operator=(ComponentManager&&) = default;

		// ==================== Component Operations ====================
		template <typename... Args>
		bool AddComponent(EntityID id, Args&&... args);

		void RemoveComponent(EntityID id) override;
		void RemoveComponents(const std::vector<EntityID>& ids) override;
		void RemoveAllComponents() override;

		// ==================== Component Access ====================
		[[nodiscard]] const T& GetComponent(EntityID id) const;
		[[nodiscard]] T& GetComponent(EntityID id);

		[[nodiscard]] const T* TryGetComponent(EntityID id) const;
		[[nodiscard]] T* TryGetComponent(EntityID id);

		// ==================== Container Access ====================
		[[nodiscard]] const ComponentContainer<T>& GetContainer() const;
		[[nodiscard]] ComponentContainer<T>& GetContainer();

		// ==================== Capacity Management ====================
		void Reserve(std::size_t capacity);

		// ==================== Query Operations ====================
		[[nodiscard]] std::size_t GetComponentCount() override noexcept;
		[[nodiscard]] bool HasComponent(EntityID id) const override;

	private:
		ComponentContainer<T> m_components;
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
	void ComponentManager<T>::RemoveComponents(const std::vector<EntityID>& ids)
	{
		for (const auto& id : ids)
		{
			m_components.Remove(id);
		}
	}

	template <ComponentType T>
	void ComponentManager<T>::RemoveAllComponents()
	{
		m_components.Clear();
	}

	template <ComponentType T>
	const T& ComponentManager<T>::GetComponent(EntityID id) const
	{
		return m_components.At(id);
	}

	template <ComponentType T>
	T& ComponentManager<T>::GetComponent(EntityID id)
	{
		return m_components.At(id);
	}

	template <ComponentType T>
	const T* ComponentManager<T>::TryGetComponent(EntityID id) const
	{
		return m_components.Get(id);
	}

	template <ComponentType T>
	T* ComponentManager<T>::TryGetComponent(EntityID id)
	{
		return m_components.Get(id);
	}

	template <ComponentType T>
	const ComponentContainer<T>& ComponentManager<T>::GetContainer() const
	{
		return m_components;
	}

	template <ComponentType T>
	ComponentContainer<T>& ComponentManager<T>::GetContainer()
	{
		return m_components;
	}

	template <ComponentType T>
	void ComponentManager<T>::Reserve(std::size_t capacity)
	{
		m_components.Reserve(capacity);
	}

	template<ComponentType T>
	inline std::size_t ComponentManager<T>::GetComponentCount() noexcept
	{
		return m_components.Size();
	}

	template <ComponentType T>
	bool ComponentManager<T>::HasComponent(EntityID id) const
	{
		return m_components.Contains(entity);
	}

#pragma endregion
}