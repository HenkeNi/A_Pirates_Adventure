#pragma once

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

		// ==================== Modifiers ====================
		void Insert(std::unique_ptr<System>&& system);

		template <DerivedFrom<System> T, typename... Args>
		T& Emplace(Args&&... args);

		template <DerivedFrom<System> T>
		void RemoveSystem();

		void Clear();

		// ==================== Access & Queries ====================
		// Nullable access
		template <DerivedFrom<System> T>
		const T* TryGetSystem() const;

		template <DerivedFrom<System> T>
		T* TryGetSystem();

		// Guaranteed access
		template <DerivedFrom<System> T>
		const T& GetSystem() const;

		template <DerivedFrom<System> T>
		T& GetSystem();

		// Existence checks
		template <DerivedFrom<System> T>
		[[nodiscard]] bool HasSystem() const;

		template <DerivedFrom<System>... Ts>
		[[nodiscard]] bool HasSystems() const;

		// Bulk access
		template <typename... Ts>
		std::tuple<Ts*...> GetSystems();

		inline [[nodiscard]] const Systems& GetAllSystems() const noexcept { return m_systems; }

		// ==================== Iteration & Operations ====================
		template <typename Func>
		void ForEach(Func&& callback) const;

		template <typename Func>
		void ForEach(Func&& callback);

		template <DerivedFrom<System> T, typename Func>
		void ForEach(Func&& callback, Func&& predicate);

		// ==================== Sorting ====================
		void SortByPriority();

		template <typename Func>
		void Sort(Func&& sortFnc);

		// ==================== Update ====================
		void Update(float deltaTime);
	
		// ==================== Utility ====================		
		[[nodiscard]] inline std::size_t GetSystemCount() const noexcept { return m_systems.size(); }

		[[nodiscard]] bool IsEmpty() const noexcept;

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
	const T* SystemManager::TryGetSystem() const
	{
		return nullptr;
	}

	template <DerivedFrom<System> T>
	T* SystemManager::TryGetSystem()
	{
		return nullptr;
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
	bool SystemManager::HasSystem() const
	{
		return false;
	}

	template <DerivedFrom<System> ...Ts>
	bool SystemManager::HasSystems() const
	{
		return false;
	}

	template <typename ...Ts>
	std::tuple<Ts*...> SystemManager::GetSystems()
	{
		return std::tuple<Ts*...>();
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