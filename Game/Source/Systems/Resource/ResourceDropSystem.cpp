#include "Pch.h"
#include "ResourceDropSystem.h"
#include "Entity.h"
#include "EntityManager.h"
#include "Core/CoreComponents.h"
#include "Gameplay/GameplayComponents.h"
#include "Rendering/RenderComponents.h"
#include "Combat/CombatComponents.h"
#include <Core/Resources/ResourceHolder.hpp>


ResourceDropSystem::ResourceDropSystem()
{
	PostMaster::GetInstance().Subscribe(eMessage::EntityDied, this);
}

ResourceDropSystem::~ResourceDropSystem()
{
	PostMaster::GetInstance().Unsubscribe(eMessage::EntityDied, this);
}

void ResourceDropSystem::Receive(Message& aMsg)
{
	if (!m_entityManager)
		return;

	auto data = std::any_cast<Entity*>(aMsg.GetData());

	//if (data->HasComponents<ResourceComponent>())
	if (data->HasComponents<HarvestableComponent>())
	{
		
		auto* harvestableComponent = data->GetComponent<HarvestableComponent>();

		auto* resource = m_entityManager->CreateResources(harvestableComponent->m_resourceType);

		//auto* resourceComponent = data->GetComponent<ResourceComponent>(); // Check if not nullptr ionstead of has component?? -> remove assert in that case 
		//auto droppedResource = m_entityManager->Create(resourceComponent->m_entityToCreate);

		auto transformComponent = resource->GetComponent<TransformComponent>();
		transformComponent->m_currentPos = data->GetComponent<TransformComponent>()->m_currentPos;
		transformComponent->m_currentPos.y = 0.1f;
		transformComponent->m_scale = { 0.2f, 0.2f, 0.2f };

		//auto spriteComponent = resource->GetComponent<SpriteComponent>();
		//spriteComponent->m_material = {
		//	&Hi_Engine::ResourceHolder<Hi_Engine::Texture2D>::GetInstance().GetResource("Log"),				// FIX! ResourceType..
		//	&Hi_Engine::ResourceHolder<Hi_Engine::Shader>::GetInstance().GetResource("Billboard") };
		//

		auto rect = resource->GetComponent<RectComponent>();
		rect->m_shader = &Hi_Engine::ResourceHolder<Hi_Engine::Shader>::GetInstance().GetResource("Primitive");			// TODO; add box collider component => trigger?

		auto pickupCollider = resource->GetComponent<PickupColliderComponent>();
		auto colliderSize = 0.2f;	// take halfsize instead?
		pickupCollider->m_collider.Init({ transformComponent->m_currentPos.x - colliderSize, transformComponent->m_currentPos.z - colliderSize }, { transformComponent->m_currentPos.x + colliderSize, transformComponent->m_currentPos.z + colliderSize });
	}
}

void ResourceDropSystem::Update(float aDeltaTime)
{
}
