#include "Pch.h"
#include "World.h"
#include "ECS/Systems/System.h"
#include "ECS/Utility/EntityHandle.h"

namespace Hi_Engine
{
    std::optional<EntityHandle> World::CreateEntity()
    {
        auto entity = m_entityManager.Create();

        if (entity.has_value())
        {
            return EntityHandle{ entity.value(), this };
        }

        return std::nullopt;
    }

    void World::DestroyEntity(const Entity& entity)
    {
        if (m_entityManager.Destroy(entity))
        {
            for (auto& [componentID, manager] : m_componentManagers)
            {
                manager->RemoveComponent(entity.ID);
            }
        }
    }

    void World::DestroyEntities(const std::vector<Entity>& entities)
    {
        for (const auto& entity : entities)
        {
            if (m_entityManager.Destroy(entity))
            {
                for (auto& [componentID, manager] : m_componentManagers)
                {
                    manager->RemoveComponent(entity.ID);
                }
            }
        }
    }

    void World::DestroyAllEntities()
    {
        m_entityManager.DestroyAll();

        for (auto& manager : m_componentManagers)
        {
            manager.second->RemoveAllComponents();
        }
    }

    bool World::IsAlive(const Entity& entity) const
    {
        return m_entityManager.IsAlive(entity);
    }
  
    void World::RemoveAllSystems()
    {
        m_systemManager.Clear();
    }

    void World::Update(float deltaTime)
    {
        m_systemManager.Update(deltaTime);
    }
}
