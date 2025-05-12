#include "Pch.h"
#include "ECSCore.h"
#include "Systems/System.h"

namespace Hi_Engine /// ::ECS
{
    std::optional<Entity> ECSCore::CreateEntity()
    {
        return m_entityManager.Create();
    }

    void ECSCore::DestroyEntity(const Entity& entity)
    {
        if (m_entityManager.Destroy(entity))
        {
            for (auto& [componentID, manager] : m_componentManagers)
            {
                manager->RemoveComponent(entity.ID);
            }
        }
    }

    void ECSCore::DestroyEntities(const std::vector<Entity>& entities)
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

    void ECSCore::DestroyAllEntities()
    {
        m_entityManager.DestroyAll();

        for (auto& manager : m_componentManagers)
        {
            manager.second->RemoveAllComponents();
        }
    }

    bool ECSCore::IsAlive(const Entity& entity) const
    {
        return m_entityManager.IsAlive(entity);
    }
}
