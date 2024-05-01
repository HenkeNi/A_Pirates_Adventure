#include "Pch.h"
#include "ActionNodes.h"
#include "Components/Components.h"
#include "Entities/Entity.h"
#include "Entities/EntityManager.h"


#pragma region IdleNode

eBTNodeStatus IdleNode::Execute(Entity* entity)
{
	if (entity)
	{
		StopMovement(entity);



		auto* blackboardComponent = entity->GetComponent<BlackboardComponent>();

		//if (blackboardComponent->IsMovingToPOI)
		//	return eBTNodeStatus::Failure;

		std::cout << "IDle\n";



		auto* transformComponent = entity->GetComponent<TransformComponent>();
		auto currentPosition = transformComponent->CurrentPos;

		auto* attributesComponent = entity->GetComponent<AttributesComponent>();
		int perception = attributesComponent->Perception;

		auto random = Hi_Engine::GenerateRandomFloatingPointInRadius<float>(currentPosition, perception * Tile::Size);

		blackboardComponent->PointOfInterest = random.GetNormalized() * (perception * Tile::Size);
		blackboardComponent->IsMovingToPOI = true;

		//entity->AddComponent() -> add DestinationComponent instead?

		return eBTNodeStatus::Success;
	}

	return eBTNodeStatus::Invalid;
}

void IdleNode::OnDestroy()
{
}

void IdleNode::StopMovement(Entity* entity)
{
	// Break slowely? (return running if not fully stopped)
	
	if (auto* velocityComponent = entity->GetComponent<VelocityComponent>())
		velocityComponent->Velocity = { 0.f, 0.f }; 
}

#pragma endregion IdleNode


#pragma region AlertNode

eBTNodeStatus AlertNode::Execute(Entity* entity)
{

	return eBTNodeStatus();
}

void AlertNode::OnDestroy()
{
}

#pragma endregion AlertNode


#pragma region MoveToTargetNode

eBTNodeStatus MoveToNode::Execute(Entity* entity)
{
	if (entity)
	{
		std::cout << "move\n";

		auto* blackboardComponent = entity->GetComponent<BlackboardComponent>();
		auto* transformComponent = entity->GetComponent<TransformComponent>();
		
		//if (!blackboardComponent->IsMovingToPOI)
		//	return eBTNodeStatus::Failure;

		if (transformComponent->CurrentPos.DistanceTo(blackboardComponent->PointOfInterest) <= 0.001f)
			return eBTNodeStatus::Success;

		
		//if (transformComponent->CurrentPos == blackboardComponent->PointOfInterest)
		//	return eBTNodeStatus::Success;

		auto* velocityComponent = entity->GetComponent<VelocityComponent>();

		auto direction = transformComponent->CurrentPos.DirectionTo(blackboardComponent->PointOfInterest);
		velocityComponent->Velocity = direction.GetNormalized();

		return eBTNodeStatus::Running;
		// auto direction = en
	}


	// Move to point of intereset?

	// Check for a DestinationComponent?

	// if in range => return success.. else return is running...




	return eBTNodeStatus::Failure;
}

void MoveToNode::OnDestroy()
{
}

#pragma endregion MoveToTargetNode






#pragma region AttackTargetNode
eBTNodeStatus AttackTargetNode::Execute(Entity* entity)
{
	return eBTNodeStatus();
}

void AttackTargetNode::OnDestroy()
{
}
#pragma endregion AttackTargetNode






//
//
//
//eBTNodeStatus IdleNode::Execute(EntityManager* entityManager)
//{
//
//}
//
//
//
//
//
//eBTNodeStatus MoveToNode::Execute(EntityManager* entityManager)
//{
//	if (IsValidTarget() && entityManager)
//	{
//		// use Enemy/NPC controllers instead??
//		auto target = entityManager->Find(m_targetID);
//		auto owner	= entityManager->Find(m_ownerID);
//
//		if (!target || !owner)
//			return eBTNodeStatus::Failure; // Return failure??
//
//		// Get wander behavior... or seek... set target... 
//
//		const auto targetPosition	= target->GetComponent<TransformComponent>()->CurrentPos;
//		const auto ownerPosition	= owner->GetComponent<TransformComponent>()->CurrentPos; 
//
//		auto direction = targetPosition - ownerPosition;
//		direction.y = 0.f;
//
//		// TODO; Check distance to target
//
//		if (direction.Length() != 0.f)
//			direction.Normalize();
//
//		auto* velocityComponent = owner->GetComponent<VelocityComponent>();
//		velocityComponent->Velocity = direction;
//		velocityComponent->Speed = 1.f;
//	}
//
//	return eBTNodeStatus::Running;
//}
//
//void MoveToNode::Clear()
//{
//
//}
//
//void MoveToNode::SetCallback(const std::function<void()>& callback)
//{
//	m_callback = callback;
//}
//
//void MoveToNode::SetTargetID(int targetID)
//{
//	m_targetID = targetID;
//}
//
//bool MoveToNode::IsValidTarget() const
//{
//	return m_targetID != -1;
//}
//
//
//
//
//eBTNodeStatus AttackTargetNode::Execute(EntityManager* entityManager)
//{
//	//std::cout << "Attaclomg..\n";
//
//	if (!entityManager)
//		return eBTNodeStatus::Failure; // CORRECT OT RETURN FAILURE??
//
//	if (auto* owner = entityManager->Find(m_ownerID))
//	{
//		owner->GetComponent<VelocityComponent>()->Velocity = { 0.f, 0.f };
//	}
//
//	// enable attack hitbox 
//
//	return eBTNodeStatus::Running;
//}
//
//void AttackTargetNode::Clear()
//{
//
//}
//
//void AttackTargetNode::SetTargetID(int targetID)
//{
//	m_targetID = targetID;
//}
//
