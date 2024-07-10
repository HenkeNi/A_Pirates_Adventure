#include "Pch.h"
#include "SystemManager.h"
#include "Base/System.h"


SystemManager::SystemManager()
{
	m_systems.reserve(64);
}

SystemManager::~SystemManager()
{
}

void SystemManager::Create(const std::string& identifier)
{
 	if (auto* system = m_factory.Build(identifier))
		m_systems.push_back(system);
}

void SystemManager::Init(class EntityManager* entityManager)
{
	for (auto& system : m_systems)
		system->Init(entityManager);
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

//void SystemManager::Register(std::unique_ptr<System> system)
//{
//	m_systems.push_back(std::move(system));
//
//	// TODO; sort systems?? or use heap?
//}

void SystemManager::Clear()
{
	for (auto& system : m_systems)
	{
		delete system;
	}

	m_systems.clear();
}