#include "Pch.h"
#include "SystemManager.h"
#include "Base/System.h"
#include "ECSTypes.h"

SystemManager::SystemManager()
{
	m_systems.reserve(MaxSystems);
}

SystemManager::~SystemManager()
{
}

void SystemManager::AddSystem(System* system)
{
	assert(m_systems.size() < MaxSystems && "[SystemManager - ERROR]: Too many systems!");
	m_systems.push_back(system);
}

void SystemManager::Update(float deltaTime)
{
	for (auto& system : m_systems)
		system->Update(deltaTime); // return false if should break loop?
}

void SystemManager::LateUpdate(float deltaTime)
{
	for (auto& system : m_systems)
		system->LateUpdate(deltaTime);
}

void SystemManager::Draw() const
{
	for (auto& system : m_systems)
		system->Draw();
}

void SystemManager::Clear()
{
	for (auto& system : m_systems)
		delete system;

	m_systems.clear();
}