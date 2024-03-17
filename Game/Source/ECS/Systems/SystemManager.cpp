#include "Pch.h"
#include "SystemManager.h"


SystemManager::SystemManager()
{
	m_systems.reserve(64);
}

SystemManager::~SystemManager()
{
}

void SystemManager::Init(class EntityManager* entityManager)
{
	for (auto& system : m_systems)
		system->Init(entityManager);
}

void SystemManager::Update(float deltaTime)
{
	for (auto& system : m_systems)
		system->Update(deltaTime);
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

void SystemManager::Register(std::unique_ptr<System> system)
{
	m_systems.push_back(std::move(system));

	// TODO; sort systems?? or use heap?
}

void SystemManager::Clear()
{
	m_systems.clear();
}