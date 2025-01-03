#include "Pch.h"
#include "SystemManager.h"
#include "../Systems/System.h"

namespace Hi_Engine
{
	struct SystemDependency
	{

	};


	void SystemManager::AddSystem(std::shared_ptr<System>&& system)
	{
		m_systems.push_back(std::move(system));
		SortSystems();
	}

	void SystemManager::ForEachSystem(const std::function<void(System&)>& callback)
	{
		for (auto& system : m_systems)
		{
			if (system)
			{
				callback(*system);
			}
		}
	}

	void SystemManager::SortSystems()
	{
		std::sort(m_systems.begin(), m_systems.end(), [](const std::shared_ptr<System>& lhs, const std::shared_ptr<System>& rhs) 
			{
				return (int)lhs->GetUpdatePhase() < (int)rhs->GetUpdatePhase();
			});
	}
}