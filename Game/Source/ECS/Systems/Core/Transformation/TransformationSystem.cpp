#include "Pch.h"
#include "TransformationSystem.h"
#include "ECS.h"
#include "Components/Core/CoreComponents.h"


TransformationSystem::TransformationSystem()
{
}

TransformationSystem::~TransformationSystem()
{
}

void TransformationSystem::Update(float deltaTime)
{
	// update local position of entity: update world position of chhlidren

	//for (const auto&)
	{
		// set local position from world position

		// updat echildren...
	}

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

void TransformationSystem::SetSignature()
{
	m_signatures.insert({ "SubEntities", m_ecs->GetSignature<SubEntitiesComponent>() });
}
