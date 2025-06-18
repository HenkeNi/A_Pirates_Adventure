#pragma once
#include "../../World/World.h"
// #include "Logging/Logger.h"
#include "Entity.h"
#include <memory>

namespace Hi_Engine
{
	class EntityHandle
	{
	public:
		EntityHandle(Entity entity, World* world = nullptr);
		~EntityHandle();

		EntityHandle(const EntityHandle&) = default;
		EntityHandle(EntityHandle&&) = default;

		EntityHandle& operator=(const EntityHandle&) = default;
		EntityHandle& operator=(EntityHandle&&) = default;

		template <ComponentType T, typename... Args>
		void AddComponent(Args&&... args);

		template <ComponentType T>
		void RemoveComponent();

		template <ComponentType T>
		[[nodiscard]] const T& GetComponent() const;

		template <ComponentType T>
		[[nodiscard]] T& GetComponent();

		template <ComponentType T>
		[[nodiscard]] const T* TryGetComponent() const;
		
		template <ComponentType T>
		[[nodiscard]] T* TryGetComponent();

		void SetWorld(World* world);

		void Destroy();

		template <ComponentType... Ts>
		[[nodiscard]] bool HasAllComponents() const;

		template <ComponentType... Ts>
		[[nodiscard]] bool HasAnyComponents() const;

		[[nodiscard]] bool IsAlive() const noexcept;

		[[nodiscard]] inline const Entity& GetEntity() const noexcept { return m_entity; }

	private:
		Entity m_entity;
		World* m_world;
	};

	template <ComponentType T, typename... Args>
	void EntityHandle::AddComponent(Args&&... args)
	{
		if (m_world)
		{
			m_world->AddComponent<T>(m_entity, std::forward<Args>(args)...);
		}
		else
		{
			Logger::LogWarning("EntityHandle - invalid World!");
		}
	}

	template <ComponentType T>
	void EntityHandle::RemoveComponent()
	{
		if (m_world)
		{
			m_world->RemoveComponent<T>(m_entity);
		}
		else
		{
			Logger::LogWarning("EntityHandle - invalid World!");
		}
	}

	template <ComponentType T>
	const T& EntityHandle::GetComponent() const
	{
		// TODO; any valid checking??

		return m_world->GetComponent<T>(m_entity);
	}

	template <ComponentType T>
	T& EntityHandle::GetComponent()
	{
		return const_cast<T&>(std::as_const(*this).GetComponent<T>());
	}

	template <ComponentType T>
	const T* EntityHandle::TryGetComponent() const
	{
		return m_world->TryGetComponent(m_entity);
	}

	template <ComponentType T>
	T* EntityHandle::TryGetComponent()
	{
		return const_cast<T*>(std::as_const(*this).TryGetComponent<T>()); // safe?
	}

	template <ComponentType... Ts>
	bool EntityHandle::HasAllComponents() const
	{
		return m_world->HasAllComponents<Ts...>(m_entity.ID);
	}

	template <ComponentType ...Ts>
	bool EntityHandle::HasAnyComponents() const
	{
		return m_world->HasAnyComponent<Ts...>(m_entity.ID);
	}
}