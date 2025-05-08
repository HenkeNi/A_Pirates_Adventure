#pragma once

namespace Hi_Engine
{
	class IService;

	class ServiceRegistry
	{
	public:
		// ==================== Insertion / Removal ====================
		template <DerivedFrom<IService> T>
		void Insert(std::shared_ptr<T> service);

		template <DerivedFrom<IService>... Ts>
		void InsertAll(std::shared_ptr<Ts>... services);

		template <DerivedFrom<IService>, typename... Args>
		void Emplace(Args&&... args);

		template <DerivedFrom<IService> T>
		void Remove();

		template <DerivedFrom<IService>... Ts>
		void RemoveAll();

		void Clear() noexcept;

		// ==================== Access Methods ====================
		// Strong guarantee (throws std::out_of_range if service not found)
		template <DerivedFrom<IService> T>
		const T& Get() const;

		template <DerivedFrom<IService> T>
		T& Get();

		// Nullable access (no-throw, returns nullptr if not found)
		template <DerivedFrom<IService> T>
		const T* TryGet() const noexcept;

		template <DerivedFrom<IService> T>
		T* TryGet() noexcept;

		// Shared ownership access (no-throw, returns empty shared_ptr if not found)
		template <DerivedFrom<IService> T>
		const std::shared_ptr<T> TryGetShared() const noexcept;
		
		template <DerivedFrom<IService> T>
		std::shared_ptr<T> TryGetShared() noexcept;

		// ==================== Capacity ====================
		std::size_t Size() const noexcept;

		bool IsEmpty() const noexcept;

		// ==================== Query Methods ====================
		template <DerivedFrom<IService> T> 
		bool Has() const;

		template <DerivedFrom<IService>... Ts>
		bool HasAll() const;

	private:
		// ==================== Interal Helpers ====================
		template <typename T>
		constexpr std::type_index GetTypeIndex() const noexcept;
		
		// ==================== Type Aliases ====================
		using ServicePtr = std::shared_ptr<IService>;
		using ServiceMap = std::unordered_map<std::type_index, ServicePtr>;

		// ==================== Data Members ====================
		ServiceMap m_services;
		mutable std::mutex m_mutex;
	};

#pragma region Templated_Methods

	template <DerivedFrom<IService> T>
	void ServiceRegistry::Insert(std::shared_ptr<T> service)
	{
		std::lock_guard lock(m_mutex);
		m_services.insert_or_assign(GetTypeIndex<T>(), std::move(service));
	}

	template <DerivedFrom<IService> ...Ts>
	void ServiceRegistry::InsertAll(std::shared_ptr<Ts> ...services)
	{
		std::lock_guard lock(m_mutex);
		(m_services.insert_or_assign(GetTypeIndex<Ts>(), std::move(services)), ...);
	}

	template <DerivedFrom<IService> T, typename ...Args>
	void ServiceRegistry::Emplace(Args&&... args)
	{
		std::lock_guard lock(m_mutex);

		m_services.insert_or_assign(
			GetTypeIndex<T>(), 
			std::make_shared<T>(std::forward<Args>(args)...)
		);
	}

	template <DerivedFrom<IService> T>
	void ServiceRegistry::Remove()
	{
		std::lock_guard lock(m_mutex);
		m_services.erase(GetTypeIndex<T>());
	}

	template<DerivedFrom<IService> ...Ts>
	inline void ServiceRegistry::RemoveAll()
	{
		std::lock_guard lock(m_mutex);
		(m_services.erase(GetTypeIndex<Ts>()), ...);
	}

	template <DerivedFrom<IService> T>
	const T& ServiceRegistry::Get() const
	{
		std::lock_guard lock(m_mutex);
		return *m_services.at(GetTypeIndex<T>());
	}

	template <DerivedFrom<IService> T>
	T& ServiceRegistry::Get()
	{
		std::lock_guard lock(m_mutex);
		return *m_services.at(GetTypeIndex<T>());
	}

	template <DerivedFrom<IService> T>
	const T* ServiceRegistry::TryGet() const noexcept
	{
		std::lock_guard lock(m_mutex);

		if (auto it = m_services.find(GetTypeIndex<T>()); it != m_services.end())
		{
			return static_cast<const T*>(it->second.get());
		}

		return nullptr;
	}

	template <DerivedFrom<IService> T>
	T* ServiceRegistry::TryGet() noexcept
	{
		std::lock_guard lock(m_mutex);

		if (auto it = m_services.find(GetTypeIndex<T>()); it != m_services.end())
		{
			return static_cast<T*>(it->second.get());
		}

		return nullptr;
	}

	template <DerivedFrom<IService> T>
	const std::shared_ptr<T> ServiceRegistry::TryGetShared() const noexcept
	{
		std::lock_guard lock(m_mutex);

		if (auto it = m_services.find(GetTypeIndex<T>()); it != m_services.end())
		{
			return std::static_pointer_cast<const T>(it->second);
		}

		return nullptr;
	}

	template <DerivedFrom<IService> T>
	std::shared_ptr<T> ServiceRegistry::TryGetShared() noexcept
	{
		std::lock_guard<std::mutex> lock(m_mutex);

		if (auto it = m_services.find(GetTypeIndex<T>()); it != m_services.end())
		{
			return std::static_pointer_cast<T>(it->second);
		}

		return nullptr;
	}

	template <DerivedFrom<IService> T>
	bool ServiceRegistry::Has() const
	{
		std::lock_guard lock(m_mutex);
		return m_services.contains(GetTypeIndex<T>());
	}

	template <DerivedFrom<IService> ...Ts>
	bool ServiceRegistry::HasAll() const
	{
		static_assert(sizeof...(Ts) > 0, "At least one type must be specified");

		std::lock_guard lock(m_mutex);
		return (m_services.contains(GetTypeIndex<Ts>()) && ...);
	}

	template <typename T>
	constexpr std::type_index ServiceRegistry::GetTypeIndex() const noexcept
	{
		return std::type_index(typeid(T));
	}

#pragma endregion
}
