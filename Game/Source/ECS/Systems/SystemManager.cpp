#include "Pch.h"
#include "SystemManager.h"


SystemManager::SystemManager()
{
	m_systems.reserve(64);
}

SystemManager::~SystemManager()
{
}

void SystemManager::Init(class EntityManager* aManager)
{
	for (auto& system : m_systems)
		system->Init(aManager);
}

void SystemManager::Update(float aDeltaTime)
{
	for (auto& system : m_systems)
		system->Update(aDeltaTime);
}

void SystemManager::LateUpdate(float aDeltaTime)
{
	for (auto& system : m_systems)
		system->LateUpdate(aDeltaTime);
}

void SystemManager::Draw() const
{
		for (auto& system : m_systems)
			system->Draw();
}

void SystemManager::Register(std::unique_ptr<System> aSystem)
{
	m_systems.push_back(std::move(aSystem));

	// TODO; sort systems?? or use heap?
}

void SystemManager::Clear()
{
	m_systems.clear();
}