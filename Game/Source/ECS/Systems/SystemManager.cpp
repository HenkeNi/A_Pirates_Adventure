#include "Pch.h"
#include "SystemManager.h"
#include "Base/System.h"
#include "ECSTypes.h"


SystemManager::SystemManager()
{
	//m_systems.reserve(MaxSystems);
}

SystemManager::~SystemManager()
{
}

std::weak_ptr<System> SystemManager::GetSystem(const char* system)
{
	auto typeItr = m_systemTypes.find(system);
	if (typeItr != m_systemTypes.end())
	{
		auto itr = m_systems.find(typeItr->second);
		if (itr != m_systems.end())
		{
			return itr->second;
		}
	}

	return std::weak_ptr<System>();
}

void SystemManager::RemoveAllSystem()
{
	m_systems.clear();
}

//void SystemManager::AddSystem(System* system)
//{
//	//assert(m_systems.size() < MaxSystems && "[SystemManager - ERROR]: Too many systems!");
//	//m_systems.push_back(system);
//}

//void SystemManager::Update(float deltaTime)
//{
//	for (auto& system : m_systems)
//		system->Update(deltaTime); // return false if should break loop?
//}
//
//void SystemManager::LateUpdate(float deltaTime)
//{
//	for (auto& system : m_systems)
//		system->LateUpdate(deltaTime);
//}
//
//void SystemManager::Draw() const
//{
//	for (auto& system : m_systems)
//		system->Draw();
//}

//void SystemManager::Clear()
//{
//	for (auto& system : m_systems)
//		delete system;
//
//	m_systems.clear();
//}