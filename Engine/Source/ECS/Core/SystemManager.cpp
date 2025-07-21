#include "Pch.h"
#include "SystemManager.h"
//#include "../Systems/System.h"

namespace Hi_Engine
{
	void SystemManager::Insert(std::unique_ptr<System>&& system, std::type_index type)
	{
		std::cout << "[SystemManager] Inserting: " << type.name() << "\n";

		assert(system && "Invalid System");
		assert(!m_indexToSystem.contains(type) && "System already registered!");

		if (m_systems.size() - 1 == 13)
		{
			int x = 20;
		}

		m_systems.push_back(std::move(system));
		m_indexToSystem.insert({ type, m_systems.size() - 1 });

		auto& inserted = m_systems.back();
		inserted->OnCreated();

		m_isSorted = false;
	}

	void SystemManager::Clear()
	{
		m_indexToSystem.clear();
		m_systems.clear();
	}

	bool SystemManager::IsEmpty() const noexcept
	{
		return m_systems.empty();
	}

	void SystemManager::Update(float deltaTime)
	{
		if (!m_isSorted)
		{
			SortByPriority();
			m_isSorted = true;
		}

		std::for_each(m_systems.begin(), m_systems.end(), [=](auto& system) { system->Update(deltaTime); });
	}

	void SystemManager::SortByPriority()
	{
		std::sort(m_systems.begin(), m_systems.end(), [](const auto& lhs, const auto& rhs)
			{
				return (int)lhs->GetUpdatePhase() < (int)rhs->GetUpdatePhase();
			});

		m_indexToSystem.clear(); // does this work?
		for (std::size_t i = 0; i < m_systems.size(); ++i)
		{
			m_indexToSystem[std::type_index(typeid(*m_systems[i]))] = i;
		}
	}
}