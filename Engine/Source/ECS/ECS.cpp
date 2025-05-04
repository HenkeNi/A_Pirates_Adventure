#include "Pch.h"
#include "ECS.h"
#include "Systems/System.h"

namespace Hi_Engine
{
    ECSCoordinator::ECSCoordinator(ModuleManager& manager)
        : Module{ manager } // , m_entityFactory{ m_entityManager, m_componentRegistry }
    {
    }


    bool ECSCoordinator::Init()
    {
      //  m_entityFactory.LoadPrefabs();
        m_entityManager.Initialize();

        return true;
    }

    std::optional<Entity> ECSCoordinator::CreateEntity()
    {
        return m_entityManager.Create();
    }

    //std::optional<Entity> ECSCoordinator::CreateEntityFromPrefab(const char* type, bool notify)
    //{
    //    std::optional<Entity> entity = m_entityFactory.Create(type);

    //    if (!entity.has_value())
    //        return std::nullopt;

    //    //if (notify)
    //    //    PostMaster::GetInstance().SendMessage({ eMessage::EntityCreated, entity.value()});

    //    return entity.value();
    //}

    //std::optional<Entity> ECSCoordinator::CreateEntityFromJson(const rapidjson::Value& jsonEntity)
    //{
    //    std::optional<Entity> entity = m_entityFactory.CreateFromJson(jsonEntity);

    //    if (!entity.has_value())
    //    {
    //        //std::cerr << "[ECSCoordinator::CreateEntityFromJson] - Failed to create entity!\n";
    //        return std::nullopt;
    //    }

    //    // PostMaster::GetInstance().SendMessage({ eMessage::EntityCreated, entity });

    //    return entity;
    //}

    void ECSCoordinator::DestroyAllEntities()
    {
        m_entityManager.DestroyAll();

        for (auto& manager : m_componentManagers)
        {
            manager.second->RemoveAllComponents();
        }
    }

    void ECSCoordinator::DestroyEntity(const Entity& entity)
    {
        if (m_entityManager.Destroy(entity))
        {
            for (auto& manager : m_componentManagers)
            {
                manager.second->RemoveComponent(entity.ID); 
            }
        }
    }

    bool ECSCoordinator::IsAlive(const Entity& entity) const
    {
        return m_entityManager.IsAlive(entity);
    }

    void ECSCoordinator::Update(float deltaTime)
    {
        m_systemManager.ForEachSystem([&](System& system) { system.Update(deltaTime); }); // measure execution here?? or in systme manager? i.e how long each system takes..
    }
}
