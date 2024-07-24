#include "Pch.h"
#include "EntityManager.h"
//#include "EntityFactory.h"
//#include "Entity.h"

//#include "../PostMaster/Message.h"
//#include "../PostMaster/PostMaster.h"


//#include "ECSTypes.h"

EntityManager::EntityManager()
{
	m_active.reserve(MaxEntities);

	for (std::size_t i = 0; i < MaxEntities; ++i)
	{
		m_available.push(i);
	}
}

Entity EntityManager::Create()
{
	assert(m_available.size() > 0 && "[EntityManager - ERROR]: Maximum entity capacity reached!");

	Entity entity = m_available.front();
	m_available.pop();

	m_active.push_back(entity);
	return entity;
}

void EntityManager::Destroy(Entity entity)
{
	assert(entity < MaxEntities && "[EntityManager - ERROR]: Entity out of range.");

	m_available.push(entity);
	m_active.erase(std::remove(m_active.begin(), m_active.end(), entity));
}

std::vector<Entity> EntityManager::GetEntities(const Signature& signature) const
{
	std::vector<Entity> entities;

	std::copy_if(m_active.begin(), m_active.end(), std::back_inserter(entities), [&](Entity entity)
		{ 
			return (m_signatures[entity] & signature) == signature;

			//return m_signatures[entity] == signature;
		});

	return entities;
}

std::optional<Entity> EntityManager::GetEntity(const Signature& signature) const
{
	auto itr = std::find_if(m_active.begin(), m_active.end(), [&](Entity entity) 
		{
			return (m_signatures[entity] & signature) == signature;

		});

	if (itr != m_active.end())
		return *itr;

	return std::nullopt;
}

void EntityManager::SetSignature(Entity entity, const Signature& signature)
{
	assert(entity < MaxEntities && "[EntityManager - ERROR]: Entity out of range.");

	m_signatures[entity] = signature;
}

Signature EntityManager::GetSignature(Entity entity)
{
	assert(entity < MaxEntities && "[EntityManager - ERROR]: Entity out of range.");

	return m_signatures[entity];
}

//void EntityManager::DestroyAll()
//{
//
//}

//EntityManager::EntityManager(EntityFactory& factory)
//	: m_entityFactory{ factory }
//{
//	m_entities.reserve(2500);
//}
//
//EntityManager::~EntityManager()
//{
//}
//
//Entity* EntityManager::Create(const std::string& type)
//{
//	auto entity = m_entityFactory.Create(type);
//
//	m_entities.push_back(std::move(entity));
//
//	auto* created = &m_entities.back();
//	PostMaster::GetInstance().SendMessage(Message{ eMessage::EntityCreated, created });
//
//	return created;
//}
//
//Entity* EntityManager::Find(unsigned id)
//{
//	auto it = std::find_if(m_entities.begin(), m_entities.end(), [=](const Entity& entity) { return entity.GetID() == id; });
//
//	if (it != m_entities.end())
//		return &(*it);
//
//	return nullptr;
//}
//
//void EntityManager::Destroy(unsigned id)
//{
//	auto it = std::find_if(m_entities.begin(), m_entities.end(), [=](const Entity& entity) { return entity.GetID() == id; });
//
//	if (it != m_entities.end())
//	{
//		PostMaster::GetInstance().SendMessage(Message{ eMessage::EntityDestroyed, &(*it) });
//		m_entities.erase(it);
//	}
//}
//
//void EntityManager::DestroyAll()
//{
//	m_entities.clear();
//}
