#include "Pch.h"
#include "EntityManager.h"
#include "EntityFactory.h"
#include "Entity.h"

#include "../PostMaster/Message.h"
#include "../PostMaster/PostMaster.h"


EntityManager::EntityManager(EntityFactory& factory)
	: m_entityFactory{ factory }
{
	m_entities.reserve(2500);
}

EntityManager::~EntityManager()
{
}

Entity* EntityManager::Create(const std::string& type)
{
	auto entity = m_entityFactory.Create(type);

	m_entities.push_back(std::move(entity));

	auto* created = &m_entities.back();
	PostMaster::GetInstance().SendMessage(Message{ eMessage::EntityCreated, created });

	return created;
}

Entity* EntityManager::Find(unsigned id)
{
	auto it = std::find_if(m_entities.begin(), m_entities.end(), [=](const Entity& entity) { return entity.GetID() == id; });

	if (it != m_entities.end())
		return &(*it);

	return nullptr;
}

void EntityManager::Destroy(unsigned id)
{
	auto it = std::find_if(m_entities.begin(), m_entities.end(), [=](const Entity& entity) { return entity.GetID() == id; });

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