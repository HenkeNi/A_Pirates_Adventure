#include "Pch.h"
#include "ECSCore.h"
#include "Systems/System.h"

namespace Hi_Engine /// ::ECS
{
    //void World::Init()
    //{
    //  //  m_entityFactory.LoadPrefabs();
    //    m_entityManager.Initialize();
    //}

    std::optional<Entity> ECSCore::CreateEntity()
    {
        return m_entityManager.Create();
    }

    //std::optional<Entity> World::CreateEntityFromPrefab(const char* type, bool notify)
    //{
    //    std::optional<Entity> entity = m_entityFactory.Create(type);

    //    if (!entity.has_value())
    //        return std::nullopt;

    //    //if (notify)
    //    //    PostMaster::GetInstance().SendMessage({ eMessage::EntityCreated, entity.value()});

    //    return entity.value();
    //}

    //std::optional<Entity> World::CreateEntityFromJson(const rapidjson::Value& jsonEntity)
    //{
    //    std::optional<Entity> entity = m_entityFactory.CreateFromJson(jsonEntity);

    //    if (!entity.has_value())
    //    {
    //        //std::cerr << "[World::CreateEntityFromJson] - Failed to create entity!\n";
    //        return std::nullopt;
    //    }

    //    // PostMaster::GetInstance().SendMessage({ eMessage::EntityCreated, entity });

    //    return entity;
    //}

    void ECSCore::DestroyAllEntities()
    {
        m_entityManager.DestroyAll();

        for (auto& manager : m_componentManagers)
        {
            manager.second->RemoveAllComponents();
        }
    }

    void ECSCore::DestroyEntity(const Entity& entity)
    {
        if (m_entityManager.Destroy(entity))
        {
            for (auto& manager : m_componentManagers)
            {
                manager.second->RemoveComponent(entity.ID); 
            }
        }
    }

    bool ECSCore::IsAlive(const Entity& entity) const
    {
        return m_entityManager.IsAlive(entity);
    }
}
