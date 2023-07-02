#include "Pch.h"
#include "SystemManager.h"


SystemManager::SystemManager()
{
	//PostMaster::GetInstance().Subscribe(eMessage::EntityCreated, this);
	//PostMaster::GetInstance().Subscribe(eMessage::EntityDestroyed, this);
}

SystemManager::~SystemManager()
{
	//PostMaster::GetInstance().Unsubscribe(eMessage::EntityCreated, this);
	//PostMaster::GetInstance().Unsubscribe(eMessage::EntityDestroyed, this);
}

//void SystemManager::Receive(Message& aMsg)
//{
//	if (aMsg.GetMessageType() == eMessage::EntityCreated)
//	{
//		AddEntity(std::any_cast<Entity*>(aMsg.GetData()));
//	}
//	else if (aMsg.GetMessageType() == eMessage::EntityDestroyed)
//	{
//		RemoveEntity(std::any_cast<Entity*>(aMsg.GetData()));
//	}
//}

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

	// TODO; sort systems??
}

void SystemManager::Clear()
{

}

 

//void SystemManager::AddEntity(Entity* anEntity)
//{
//	assert(anEntity && "ERROR: trying to add a nullptr!");
//
//	/* Add entity to relevant systems */
//	for (auto& system : m_systems)
//	{
//		auto it = std::find(system->m_entities.begin(), system->m_entities.end(), anEntity);
//	
//		if (it == system->m_entities.end() && system->HasRequiredComponents(*it))
//		{
//			system->m_entities.push_back(*it);
//		}
//	}
//}

//void SystemManager::RemoveEntity(Entity* anEntity)
//{
//	assert(anEntity && "ERROR: trying to add a nullptr!");
//
//	/* Remove entity from systems */
//	for (auto& system : m_systems)
//	{
//		auto it = std::find(system->m_entities.begin(), system->m_entities.end(), anEntity);
//
//		if (it != system->m_entities.end())
//			system->m_entities.erase(it);
//	}
//}