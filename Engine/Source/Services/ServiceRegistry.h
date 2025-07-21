#pragma once
#include "Utility/TypeTraits.h"
#include <unordered_map>
#include <typeindex>
#include <mutex>

namespace Hi_Engine
{
	class IService;

	// TODO; Send event when register / unregister? observer pattern? (i.e. Subscribe), or use EventDIspatcher?
	// Consider; storing unique_ptr's instead, implement GetSafe (uses dynamic cast rather than static) - or a template bool bUseSafe?
	// [Consider] don't allow overwrite services(?), instead assert if service already exist
	// [Class Name] Is service registry a bad name? SubsystemHolder? ServiceHolder?


	// Consider; marking Insert(s), InsertAll, Remove, RemoveAll, ForEach, Has and HasAll with noexcept?
	class ServiceRegistry
	{
	public:
		// ==================== Constructors ====================
		ServiceRegistry() = default;
		~ServiceRegistry() = default;

		ServiceRegistry(const ServiceRegistry&) = delete;
		ServiceRegistry(ServiceRegistry&&) = delete;

		ServiceRegistry& operator=(const ServiceRegistry&) = delete;
		ServiceRegistry& operator=(ServiceRegistry&&) = delete;

		// ==================== Insertion / Removal ====================
		template <DerivedFrom<IService> T>
		void Insert(std::shared_ptr<T> service);

		void Insert(std::shared_ptr<IService> service);

		template <DerivedFrom<IService>... Ts>
		void InsertAll(std::shared_ptr<Ts>... services);

		template <DerivedFrom<IService> T, typename... Args>
		T& Emplace(Args&&... args);

		template <DerivedFrom<IService> T>
		void Remove();

		template <DerivedFrom<IService>... Ts>
		void RemoveAll();

		void Clear() noexcept;

		// ==================== Iteration ====================
		template <typename Callback>
		void ForEach(Callback&& callback) const;

		template <typename Callback>
		void ForEach(Callback&& callback);

		// ==================== Access Methods ====================
		// Strong guarantee (throws std::out_of_range if service not found)
		template <DerivedFrom<IService> T>
		[[nodiscard]] const T& Get() const;

		template <DerivedFrom<IService> T>
		[[nodiscard]] T& Get();

		// Nullable access (no-throw, returns nullptr if not found)
		template <DerivedFrom<IService> T>
		[[nodiscard]] const T* TryGet() const; // remove?

		template <DerivedFrom<IService> T>
		[[nodiscard]] T* TryGet();

		// Weak ownership access (no-throw, returns empty weak_ptr if not found)
		template <DerivedFrom<IService> T>
		[[nodiscard]] std::weak_ptr<const T> TryGetWeak() const;

		template <DerivedFrom<IService> T>
		[[nodiscard]] std::weak_ptr<T> TryGetWeak();

		// ==================== Capacity ====================
		[[nodiscard]] std::size_t Size() const noexcept;

		[[nodiscard]] bool IsEmpty() const noexcept;

		// ==================== Query Methods ====================
		template <DerivedFrom<IService> T>
		[[nodiscard]] bool Has() const;

		template <DerivedFrom<IService>... Ts>
		[[nodiscard]] bool HasAll() const;

	private:
		// ==================== Interal Helpers ====================
		template <DerivedFrom<IService> T>
		constexpr std::type_index GetTypeIndex() const noexcept;

		// ==================== Type Aliases ====================
		using ServicePtr = std::shared_ptr<IService>;
		using ServiceMap = std::unordered_map<std::type_index, ServicePtr>;

		// ==================== Data Members ====================
		ServiceMap m_services;
		mutable std::mutex m_mutex{};
	};

#pragma region Templated_Methods

	template <DerivedFrom<IService> T>
	void ServiceRegistry::Insert(std::shared_ptr<T> service)
	{
		std::lock_guard lock(m_mutex);

		m_services.insert_or_assign(GetTypeIndex<T>(), service);
	}

	template <DerivedFrom<IService> ...Ts>
	void ServiceRegistry::InsertAll(std::shared_ptr<Ts>... services)
	{
		std::lock_guard lock(m_mutex);
		(m_services.insert_or_assign(GetTypeIndex<Ts>(), std::move(services)), ...);
	}

	template <DerivedFrom<IService> T, typename ...Args>
	T& ServiceRegistry::Emplace(Args&&... args)
	{
		std::lock_guard lock(m_mutex);

		auto service = std::make_shared<T>(std::forward<Args>(args)...);
		m_services.insert_or_assign(GetTypeIndex<T>(), service);

		return *service; // is this safe?
	}

	template <DerivedFrom<IService> T>
	void ServiceRegistry::Remove()
	{
		std::lock_guard lock(m_mutex);
		m_services.erase(GetTypeIndex<T>());
	}

	template <DerivedFrom<IService> ...Ts>
	void ServiceRegistry::RemoveAll()
	{
		std::lock_guard lock(m_mutex);
		(m_services.erase(GetTypeIndex<Ts>()), ...);
	}

	template <typename Callback>
	void ServiceRegistry::ForEach(Callback&& callback) const
	{
		std::lock_guard lock(m_mutex);
		for (const auto& [type, service] : m_services)
		{
			if (service) callback(service);
		}
	}

	template <typename Callback>
	void ServiceRegistry::ForEach(Callback&& callback)
	{
		std::lock_guard lock(m_mutex);
		for (auto& [type, service] : m_services)
		{
			if (service) callback(service);
		}
	}

	template <DerivedFrom<IService> T>
	const T& ServiceRegistry::Get() const
	{
		std::lock_guard lock(m_mutex);

		auto it = m_services.find(GetTypeIndex<T>());

		assert(it != m_services.end() && "Service not found in registry!");
		assert(dynamic_cast<const T*>(it->second.get()) && "Type mismatch detected!");

		return *static_cast<const T*>(it->second.get());
	}

	template <DerivedFrom<IService> T>
	T& ServiceRegistry::Get()
	{
		return const_cast<T&>(std::as_const(*this).Get<T>());
	}

	template <DerivedFrom<IService> T>
	const T* ServiceRegistry::TryGet() const
	{
		std::lock_guard lock(m_mutex);

		if (auto it = m_services.find(GetTypeIndex<T>()); it != m_services.end())
		{
			assert(dynamic_cast<const T*>(it->second.get()) && "Type mismatch detected!");

			return static_cast<const T*>(it->second.get());
		}

		return nullptr;
	}

	template <DerivedFrom<IService> T>
	T* ServiceRegistry::TryGet()
	{
		return const_cast<T*>(std::as_const(*this).TryGet<T>());
	}

	template <DerivedFrom<IService> T>
	std::weak_ptr<const T> ServiceRegistry::TryGetWeak() const
	{
		std::lock_guard lock(m_mutex);

		if (auto it = m_services.find(GetTypeIndex<T>()); it != m_services.end())
		{
			assert(dynamic_cast<const T*>(it->second.get()) && "Type mismatch detected!");

			return std::static_pointer_cast<const T>(it->second);
		}

		return {};
	}

	template <DerivedFrom<IService> T>
	std::weak_ptr<T> ServiceRegistry::TryGetWeak()
	{
		std::lock_guard lock(m_mutex);

		if (auto it = m_services.find(GetTypeIndex<T>()); it != m_services.end())
		{
			assert(dynamic_cast<T*>(it->second.get()) && "Type mismatch detected!");

			return std::static_pointer_cast<T>(it->second);
		}

		return {};
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

	template <DerivedFrom<IService> T>
	constexpr std::type_index ServiceRegistry::GetTypeIndex() const noexcept
	{
		return std::type_index(typeid(T));
	}

#pragma endregion
}
