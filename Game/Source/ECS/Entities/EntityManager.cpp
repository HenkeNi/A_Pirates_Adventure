#include "Pch.h"
#include "EntityManager.h"
#include "Entity.h"
#include "../PostMaster/Message.h"
#include "../PostMaster/PostMaster.h"

EntityFactory EntityManager::s_entityFactory;

EntityManager::EntityManager()
{
	m_entities.reserve(512);
}

EntityManager::~EntityManager()
{
}

Entity* EntityManager::Create(const std::string& aType)
{
	auto entity = s_entityFactory.Create(aType);

	m_entities.push_back(std::move(entity));

	auto* created = &m_entities.back();
	PostMaster::GetInstance().SendMessage(Message{ eMessage::EntityCreated, created });

	return created;
}

Entity* EntityManager::Find(unsigned anID)
{
	auto it = std::find_if(m_entities.begin(), m_entities.end(), [=](const Entity& anEntity) { return anEntity.GetID() == anID; });

	if (it != m_entities.end())
		return &(*it);

	return nullptr;
}

EntityFactory& EntityManager::GetFactory()
{
	return s_entityFactory;
}

void EntityManager::Destroy(unsigned anID)
{
	auto it = std::find_if(m_entities.begin(), m_entities.end(), [=](const Entity& anEntity) { return anEntity.GetID() == anID; });

	if (it != m_entities.end())
	{
		PostMaster::GetInstance().SendMessage(Message{ eMessage::EntityDestroyed, &(*it) });
		m_entities.erase(it);
	}
}

void EntityManager::DestroyAll()
{
	m_entities.clear();
}