#pragma once
#include <span> // temp

namespace Hi_Engine
{
	// Figure out system dependencies
	// Separate between update and render systems
	// SparseSet?
	// return optional? instead of T&

	class System;

	class SystemManager
	{
	public:
		// ==================== Type Aliases ====================
		using Systems = std::vector<std::unique_ptr<System>>; 
		using SystemView = std::span<const std::unique_ptr<System>>;

		// ==================== System Management ====================
		// Methods that handles the lifecycle of systems (addition, removal, clearing)

		void Insert(std::unique_ptr<System>&& system);

		template <DerivedFrom<System> T, typename... Args>
		T& Emplace(Args&&... args);

		template <DerivedFrom<System> T>
		void RemoveSystem();

		void Clear();

		// ==================== System Access ====================
		// Methods for accessing systems with different safety guarantees

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

		inline [[nodiscard]] const Systems& GetAllSystems() const noexcept { return m_systems; }

		// ==================== System Queries ====================
		// Methods for querying system state and existence

		template <DerivedFrom<System> T>
		[[nodiscard]] bool HasSystem() const; // Noexcept?

		template <DerivedFrom<System>... Ts>
		[[nodiscard]] bool HasSystems() const; // Noexcept?

		template <DerivedFrom<System>... Ts>
		[[nodiscard]] bool IsEnabled() const noexcept; // Noexcept?

		[[nodiscard]] bool IsEmpty() const noexcept;

		[[nodiscard]] inline std::size_t GetSystemCount() const noexcept { return m_systems.size(); }

		// ==================== System Control ====================
		// Methods for enabling/disabling systems and controlling execution

		template <DerivedFrom<System> T>
		void Enable();

		template <DerivedFrom<System> T>
		void Disable();

		void Update(float deltaTime);

		// ==================== System Iteration ====================
		// Methods for iterating over systems with various predicates

		template <typename Func>
		void ForEach(Func&& callback) const;

		template <typename Func>
		void ForEach(Func&& callback);

		template <DerivedFrom<System> T, typename Func>
		void ForEach(Func&& callback, Func&& predicate);

		// ==================== System Ordering ====================
		// Methods for controlling system execution order

		void SortByPriority();

		template <typename Func>
		void Sort(Func&& sortFnc);
	
	private:
		std::unordered_map<std::type_index, std::size_t> m_indexToSystem;
		Systems m_systems;
		bool m_isSorted = false;
	};

#pragma region Templated_Methods
	
	template <DerivedFrom<System> T, typename... Args>
	T& SystemManager::Emplace(Args&&... args)
	{
		m_systems.push_back(std::make_unique<T>(std::forward<Args>(args)...));
		m_isSorted = false;

		return m_systems.back();
	}

	template <DerivedFrom<System> T>
	void SystemManager::RemoveSystem()
	{
		m_systems.erase(std::remove_if(m_systems.begin(), m_systems.end(), [](const auto& system) { return std::type_index(typeid(system)) == std::type_index(typeid(T)); }));
	}

	template <DerivedFrom<System> T>
	const T& SystemManager::GetSystem() const
	{
		// TODO: insert return statement here
	}

	template <DerivedFrom<System> T>
	T& SystemManager::GetSystem()
	{
		// TODO: insert return statement here
	}

	template <DerivedFrom<System> T>
	const T* SystemManager::TryGetSystem() const
	{
		return nullptr;
	}

	template <DerivedFrom<System> T>
	T* SystemManager::TryGetSystem()
	{
		return nullptr;
	}

	template <typename ...Ts>
	std::tuple<Ts*...> SystemManager::GetSystems()
	{
		return std::tuple<Ts*...>();
	}

	template <DerivedFrom<System> T>
	bool SystemManager::HasSystem() const
	{
		return false;
	}

	template <DerivedFrom<System> ...Ts>
	bool SystemManager::HasSystems() const
	{
		return false;
	}

	template <DerivedFrom<System> ...Ts>
	bool SystemManager::IsEnabled() const noexcept
	{
		return false;
	}

	template <DerivedFrom<System> T>
	void SystemManager::Enable()
	{
		if (auto* system = TryGetSystem<T>())
		{
			system->SetEnabled(true);
		}
	}

	template <DerivedFrom<System> T>
	void SystemManager::Disable()
	{
		if (auto* system = TryGetSystem<T>())
		{
			system->SetEnabled(false);
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
	}

	template <typename Func>
	void SystemManager::Sort(Func&& sortFnc)
	{
	}

#pragma endregion
}