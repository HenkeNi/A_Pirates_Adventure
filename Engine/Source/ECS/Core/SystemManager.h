#pragma once
#include "../Systems/System.h"
#include <span> // temp
#include <ranges>

namespace Hi_Engine
{
	// Consider replacing map and vector with a SparseSet; - might be worse for sorting though!
	// Figure out system dependencies
	// Separate between update and render systems
	// SparseSet?
	// return optional? instead of T&

	//class System;

	class SystemManager
	{
	public:
		// ==================== Type Aliases ====================
		using Systems = std::vector<std::unique_ptr<System>>; 
		using SystemView = std::span<const std::unique_ptr<System>>;

		// ==================== System Management ====================
		template <DerivedFrom<System> T, typename... Args>
		T& Emplace(Args&&... args);

		template <DerivedFrom<System> T>
		void Insert(std::unique_ptr<T>&& system);

		void Insert(std::unique_ptr<System>&& system, std::type_index type); // dont pass in typeindex?

		template <DerivedFrom<System> T>
		void RemoveSystem();

		void Clear();

		// ==================== System Access ====================
		template <DerivedFrom<System> T>
		[[nodiscard]] const T& GetSystem() const;

		template <DerivedFrom<System> T>
		[[nodiscard]] T& GetSystem();

		template <DerivedFrom<System> T>
		[[nodiscard]] const T* TryGetSystem() const;

		template <DerivedFrom<System> T>
		[[nodiscard]] T* TryGetSystem();

		template <typename... Ts>
		std::tuple<Ts*...> GetSystems(); // no discard?

		// ==================== System Queries ====================
		template <DerivedFrom<System> T>
		[[nodiscard]] bool HasSystem() const; // Noexcept?

		template <DerivedFrom<System>... Ts>
		[[nodiscard]] bool HasSystems() const; // Noexcept?

		template <DerivedFrom<System> T>
		[[nodiscard]] bool IsEnabled() const; // Noexcept?

		[[nodiscard]] bool IsEmpty() const noexcept;

		[[nodiscard]] inline std::size_t GetSystemCount() const noexcept { return m_systems.size(); }

		// ==================== System Control ====================
		template <DerivedFrom<System> T>
		void Enable();

		template <DerivedFrom<System> T>
		void Disable();

		void Update(float deltaTime);

		// ==================== System Iteration ====================
		template <typename Func>
		void ForEach(Func&& callback) const;

		template <typename Func>
		void ForEach(Func&& callback);

		// remove?
		template <DerivedFrom<System> T, typename Func> // Func needs to accept a unqie-ptr&? and return a bool
		void ForEach(Func&& callback, Func&& predicate);

		// ==================== System Ordering ====================
		void SortByPriority();

		template <typename Func>
		void Sort(Func&& sortFnc);
	
	private:
		template <DerivedFrom<System> T>
		[[nodiscard]] std::type_index GetTypeIndex() const; // make global function?

		template <DerivedFrom<System> T>
		[[nodiscard]] std::size_t GetVectorIndex() const;

		// use sparse set? 
		std::unordered_map<std::type_index, std::size_t> m_indexToSystem;
		Systems m_systems;
		bool m_isSorted = false;
	};

#pragma region Templated_Methods
	
	template <DerivedFrom<System> T, typename... Args>
	T& SystemManager::Emplace(Args&&... args)
	{
		assert(!HasSystem<T>() && "System already registered!");

		m_systems.push_back(std::make_unique<T>(std::forward<Args>(args)...));
		m_indexToSystem.insert({ std::type_index(typeid(T)), m_systems.size() - 1 });

		m_isSorted = false;
		
		auto& system = m_systems.back();
		system->OnCreated();

		return *system;
		//return m_systems.back();
	}

	template <DerivedFrom<System> T>
	void SystemManager::Insert(std::unique_ptr<T>&& system)
	{
		assert(!HasSystem<T>() && "System already registered!");

		auto [it, success] = Insert(std::move(system), std::type_index(typeid(T)));
		m_indexToSystem.insert({ std::type_index(typeid(T)), m_systems.size() - 1 });

		if (success)
		{
			it->OnCreated();
		}
	}

	template <DerivedFrom<System> T>
	void SystemManager::RemoveSystem()
	{
		auto type = std::type_index(typeid(T));

		m_indexToSystem.erase(type);

		m_systems.erase(std::remove_if(m_systems.begin(), m_systems.end(), 
			[](const auto& system) 
			{ 
				return std::type_index(typeid(*system)) == type; 
			}), m_systems.end());
	}

	template <DerivedFrom<System> T>
	const T& SystemManager::GetSystem() const
	{
		const auto& system = m_systems.at(GetVectorIndex<T>());
		return static_cast<T&>(*system.get());
	}

	template <DerivedFrom<System> T>
	T& SystemManager::GetSystem()
	{
		return const_cast<T&>(std::as_const(*this).GetSystem<T>());
	}

	template <DerivedFrom<System> T>
	const T* SystemManager::TryGetSystem() const
	{
		auto index = GetVectorIndex<T>();

		if (index != std::numeric_limits<std::size_t>::max())
		{
			const auto& system = m_systems.at(index);
			return static_cast<T*>(system.get());
		}
		
		return nullptr;
	}

	template <DerivedFrom<System> T>
	T* SystemManager::TryGetSystem()
	{
		return const_cast<T*>(std::as_const(*this).TryGetSystem<T>());
	}

	template <typename... Ts>
	std::tuple<Ts*...> SystemManager::GetSystems()
	{
		return std::make_tuple<Ts*...>(TryGetSystem<Ts>()...);
	}

	template <DerivedFrom<System> T>
	bool SystemManager::HasSystem() const
	{
		return m_indexToSystem.contains(GetTypeIndex<T>());
	}

	template <DerivedFrom<System>... Ts>
	bool SystemManager::HasSystems() const
	{
		return (... && m_indexToSystem.contains(GetTypeIndex<Ts>()));
	}

	template <DerivedFrom<System> T>
	bool SystemManager::IsEnabled() const
	{
		if (auto* system = TryGetSystem<T>())
		{
			return system->IsEnabled();
		}

		return false;
	}

	template <DerivedFrom<System> T>
	void SystemManager::Enable()
	{
		if (auto* system = TryGetSystem<T>())
		{
			if (!system->IsEnabled())
			{
				system->Enable;
				system->OnEnabled();
			}
		}
	}

	template <DerivedFrom<System> T>
	void SystemManager::Disable()
	{
		if (auto* system = TryGetSystem<T>())
		{
			if (system->IsEnabled())
			{
				system->Disable();
				system->OnDisabled();
			}
		}
	}

	template <typename Func>
	void SystemManager::ForEach(Func&& callback) const
	{
	}

	template <typename Func>
	void SystemManager::ForEach(Func&& callback)
	{
	}

	template <DerivedFrom<System> T, typename Func>
	void SystemManager::ForEach(Func&& callback, Func&& predicate)
	{
		auto filtered = m_systems | std::views::filter([](auto& system) { return predicate(system); });
		std::for_each(filtered.begin(), filtered.end(), [](auto& system) { callback(system); });
	}

	template <typename Func>
	void SystemManager::Sort(Func&& sortFnc)
	{
		std::sort(m_systems.begin(), m_systems.end(), sortFnc);
	}
	
	template <DerivedFrom<System> T>
	std::type_index SystemManager::GetTypeIndex() const
	{

	}

	template <DerivedFrom<System> T>
	std::size_t SystemManager::GetVectorIndex() const
	{
		auto type = std::type_index(typeid(T));

		if (auto it = m_indexToSystem.find(type); it != m_indexToSystem.end())
		{
			return it->second;
		}

		return std::numeric_limits<std::size_t>::max();
	}

#pragma endregion
}