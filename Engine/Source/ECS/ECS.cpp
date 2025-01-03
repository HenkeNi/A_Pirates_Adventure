#include "Pch.h"
#include "ECS.h"
#include "Systems/System.h"

namespace Hi_Engine
{
    ECSCoordinator::ECSCoordinator(ModuleManager& manager)
        : Module{ manager }, m_entityFactory{ m_entityManager, m_componentRegistry }
    {
    }

    ECSCoordinator::~ECSCoordinator()
    {
    }

    bool ECSCoordinator::Init()
    {
        m_entityFactory.LoadPrefabs();
        m_entityManager.Initialize();

        return true;
    }

    std::optional<Entity> ECSCoordinator::CreateEntityFromPrefab(const char* type, bool notify)
    {
        std::optional<Entity> entity = m_entityFactory.Create(type);

        if (!entity.has_value())
            return std::nullopt;

        //if (notify)
        //    PostMaster::GetInstance().SendMessage({ eMessage::EntityCreated, entity.value()});

        return entity.value();
    }

    std::optional<Entity> ECSCoordinator::CreateEntityFromJson(const rapidjson::Value& jsonEntity)
    {
        std::optional<Entity> entity = m_entityFactory.CreateFromJson(jsonEntity);

        if (!entity.has_value())
        {
            //std::cerr << "[ECSCoordinator::CreateEntityFromJson] - Failed to create entity!\n";
            return std::nullopt;
        }

        // PostMaster::GetInstance().SendMessage({ eMessage::EntityCreated, entity });

        return entity;
    }

    void ECSCoordinator::DestroyAllEntities()
    {
    }

    void ECSCoordinator::DestroyEntity(Entity entity)
    {
    }

    void ECSCoordinator::Update(float deltaTime)
    {
        m_systemManager.ForEachSystem([&](System& system) { system.Update(deltaTime); });
    }
}
