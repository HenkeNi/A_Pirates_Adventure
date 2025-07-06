#include "Pch.h"
#include "ServiceRegistry.h"


namespace Hi_Engine
{
	void ServiceRegistry::Insert(std::shared_ptr<IService> service, std::type_index type)
	{
		std::lock_guard lock(m_mutex);
		m_services.insert({ type, service });
	}

	void ServiceRegistry::Clear() noexcept
	{
		std::lock_guard lock(m_mutex);
		m_services.clear();
	}

	std::size_t ServiceRegistry::Size() const noexcept
	{
		std::lock_guard lock(m_mutex);
		return m_services.size();
	}

	bool ServiceRegistry::IsEmpty() const noexcept
	{
		std::lock_guard lock(m_mutex);
		return m_services.empty();
	}
}