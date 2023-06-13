#include "Pch.h"
#include "EntityManager.h"
#include "../Entity/Entity.h"
#include "../PostMaster/Message.h"
#include "../PostMaster/PostMaster.h"


EntityManager::EntityManager()
{
	m_entities.reserve(200);
}

EntityManager::~EntityManager()
{
}


// TODO; remove later??
void EntityManager::Add(Entity anEntity)
{
	m_entities.push_back(std::move(anEntity));

	PostMaster::GetInstance().SendMessage(Message{ eMessage::EntityCreated, &m_entities.back() }); // REMOVE!!
}


Entity* EntityManager::Create(const std::string& aType)
{
	m_entities.push_back(Entity{});

	auto* entity = &m_entities.back();
	PostMaster::GetInstance().SendMessage(Message{ eMessage::EntityCreated, entity });

	return entity;
}

Entity* EntityManager::Find(unsigned anID)
{
	auto it = std::find_if(m_entities.begin(), m_entities.end(), [=](const Entity& anEntity) { return anEntity.GetID() == anID; });

	if (it != m_entities.end())
		return &(*it);

	return nullptr;
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