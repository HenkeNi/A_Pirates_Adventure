#include "Pch.h"
#include "World.h"
#include "ECS/Systems/System.h"
#include "ECS/Utility/EntityHandle.h"


#include <Components/CoreComponents.h>

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

    std::optional<EntityHandle> World::FindEntityByName(std::string_view name)
    {
        auto entities = m_entityManager.GetEntities(GetSignature<NameComponent>());

        auto it = std::find_if(entities.begin(), entities.end(), [&](const Entity& entity)
            {
                if (auto* nameComponent = TryGetComponent<NameComponent>(entity))
                {
                    return nameComponent->Name == name;
                }

                return false;
            });

        return it != entities.end() ? std::optional<EntityHandle>(EntityHandle{ *it, this }) : std::nullopt;
    }

    std::vector<EntityHandle> World::FindAllEntitiesWithTag(std::string_view tag)
    {
        std::vector<EntityHandle> handles;

        auto entities = m_entityManager.GetEntities(GetSignature<TagComponent>());

        for (const auto& entity : entities)
        {
            if (auto* tagComponent = TryGetComponent<TagComponent>(entity))
            {
                if (tagComponent->Tag == tag)
                    handles.emplace_back(entity, this);
            }
        }

        return handles;
    }

    void World::Update(float deltaTime)
    {
        m_systemManager.Update(deltaTime);
    }
}
