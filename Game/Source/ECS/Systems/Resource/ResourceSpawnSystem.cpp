#include "Pch.h"
#include "ResourceSpawnSystem.h"
#include "Entities/Entity.h"
#include "Entities/EntityManager.h"
#include "Components/Core/CoreComponents.h"
#include "Components/Gameplay/GameplayComponents.h"
#include <Core/Resources/ResourceHolder.hpp>


ResourceSpawnSystem::ResourceSpawnSystem()
{
	PostMaster::GetInstance().Subscribe(eMessage::EntityDied, this);
}

ResourceSpawnSystem::~ResourceSpawnSystem()
{
	PostMaster::GetInstance().Unsubscribe(eMessage::EntityDied, this);
}

void ResourceSpawnSystem::Receive(Message& aMsg)
{
	if (!m_entityManager)
		return;

	auto data = std::any_cast<Entity*>(aMsg.GetData());

	//if (data->HasComponents<ResourceComponent>())
	if (data->HasComponents<HarvestableComponent>())
	{
		
		auto* harvestableComponent = data->GetComponent<HarvestableComponent>();

		auto* resource = m_entityManager->Create(harvestableComponent->ResourceType);

		//auto* resourceComponent = data->GetComponent<ResourceComponent>(); // Check if not nullptr ionstead of has component?? -> remove assert in that case 
		//auto droppedResource = m_entityManager->Create(resourceComponent->m_entityToCreate);

		auto transformComponent = resource->GetComponent<TransformComponent>();
		transformComponent->CurrentPos = data->GetComponent<TransformComponent>()->CurrentPos;
		transformComponent->CurrentPos.y = 0.1f;
		transformComponent->Scale = { 0.2f, 0.2f, 0.2f };

		//auto spriteComponent = resource->GetComponent<SpriteComponent>();
		//spriteComponent->m_material = {
		//	&Hi_Engine::ResourceHolder<Hi_Engine::Texture2D>::GetInstance().GetResource("Log"),				// FIX! ResourceType..
		//	&Hi_Engine::ResourceHolder<Hi_Engine::Shader>::GetInstance().GetResource("Billboard") };
		//

		//auto rect = resource->GetComponent<RectComponent>();
		//rect->Shader = &Hi_Engine::ResourceHolder<Hi_Engine::Shader>::GetInstance().GetResource("Primitive");			// TODO; add box collider component => trigger?

		auto pickupCollider = resource->GetComponent<PickupColliderComponent>();
		auto colliderSize = 0.2f;	// take halfsize instead?
		pickupCollider->Collider.Init({ transformComponent->CurrentPos.x - colliderSize, transformComponent->CurrentPos.z - colliderSize }, { transformComponent->CurrentPos.x + colliderSize, transformComponent->CurrentPos.z + colliderSize });
	}
}

void ResourceSpawnSystem::Update(float aDeltaTime)
{
}
