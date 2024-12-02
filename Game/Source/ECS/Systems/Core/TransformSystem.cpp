#include "Pch.h"
#include "TransformSystem.h"
#include "ECS.h"
#include "Components/Core/CoreComponents.h"


TransformSystem::TransformSystem()
{
}

TransformSystem::~TransformSystem()
{
}

void TransformSystem::Update(float deltaTime)
{
	// update local position of entity: update world position of chhlidren

	//for (const auto&)
	{
		// set local position from world position

		// updat echildren...
	}
	
	UpdateSubEntities();
	UpdateOrientation();
}

void TransformSystem::SetSignature()
{
	m_signatures.insert({ "Transform", m_ecs->GetSignature<TransformComponent, VelocityComponent>() });
	m_signatures.insert({ "SubEntities", m_ecs->GetSignature<SubEntitiesComponent>() });
}

void TransformSystem::UpdateSubEntities()
{

	auto entities = m_ecs->FindEntities(m_signatures["SubEntities"]);

	for (auto entity : entities)
	{
		if (auto* childComponent = m_ecs->GetComponent<SubEntitiesComponent>(entity)) // Change?
		{
			auto* transformComponent = m_ecs->GetComponent<TransformComponent>(entity); // pass in?

			for (unsigned entityID : childComponent->IDs)
			{
				auto* childTransformComponent = m_ecs->GetComponent<TransformComponent>(entityID);

				childTransformComponent->PreviousPos = childTransformComponent->CurrentPos;
				childTransformComponent->CurrentPos = transformComponent->CurrentPos;
			}
		}
	}

}

void TransformSystem::UpdateOrientation()
{
	for (Entity entity : m_ecs->FindEntities(m_signatures["Transform"]))
	{
		auto* transformComponent = m_ecs->GetComponent<TransformComponent>(entity);
		auto* velocityComponent = m_ecs->GetComponent<VelocityComponent>(entity);

		if (!transformComponent || !velocityComponent)
			continue;

		if (velocityComponent->Velocity.x >= 1.f)
		{
			if (transformComponent->Scale.x < 0.f)
				transformComponent->Scale.x *= -1.f;

			//if (aTransformComponent->Scale.x == -1.f)
			//	aTransformComponent->Scale.x = 1.f;
		}
		else if (velocityComponent->Velocity.x <= -1.f)
		{
			if (transformComponent->Scale.x > 0.f)
				transformComponent->Scale.x *= -1.f;
			//if (aTransformComponent->Scale.x == 1.f)
			//	aTransformComponent->Scale.x = -1.f;
		}
	}
}