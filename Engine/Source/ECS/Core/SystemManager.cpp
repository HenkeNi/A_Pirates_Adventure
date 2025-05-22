#include "Pch.h"
#include "SystemManager.h"
#include "../Systems/System.h"

namespace Hi_Engine
{
	void SystemManager::Insert(std::unique_ptr<System>&& system)
	{
		m_systems.push_back(std::move(system));
		m_isSorted = false;
	}

	void SystemManager::Clear()
	{
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
	}
}