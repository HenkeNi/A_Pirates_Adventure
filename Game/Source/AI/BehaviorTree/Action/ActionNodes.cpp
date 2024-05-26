#include "Pch.h"
#include "ActionNodes.h"
#include "Entities/Entity.h"
#include "Components/Components.h"


#pragma region IdleNode

eBTNodeStatus IdleNode::Execute(Entity* entity)
{
	if (entity)
	{
		StopMovement(entity);

		return eBTNodeStatus::Success;
	}

	return eBTNodeStatus::Invalid;
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

eBTNodeStatus MoveToDestinationNode::Execute(Entity* entity)
{
	static float wanderSpeed = 0.5f;

	if (entity)
	{
		auto* destinationComponent = entity->GetComponent<DestinationComponent>();
		const auto& destination = destinationComponent->Destination;

		auto* transformComponent = entity->GetComponent<TransformComponent>();
		const auto& currentPosition = transformComponent->CurrentPos;

		auto direction = currentPosition.DirectionTo(destination);
		
		auto* velocityComponent = entity->GetComponent<VelocityComponent>();
		velocityComponent->Velocity = direction.GetNormalized();
		velocityComponent->Speed = wanderSpeed;

	}

	// Remove destination component if in range??

	// check if destination is reached...?? return succedded then?
	return eBTNodeStatus::Running;
}

eBTNodeStatus ChaseTargetNode::Execute(Entity* entity)
{
	static float chaseSpeed = 1.f;

	if (entity)
	{
		auto* targetComponent = entity->GetComponent<TargetComponent>();
		auto* transformComponent = entity->GetComponent<TransformComponent>();

		const auto& currentPosition = transformComponent->CurrentPos;


		auto* targetTransformComponent = targetComponent->Target->GetComponent<TransformComponent>();
		const auto& targetCurrentPosition = targetTransformComponent->CurrentPos;

		auto direction = currentPosition.DirectionTo(targetCurrentPosition);

		auto* velocityComponent = entity->GetComponent<VelocityComponent>();
		velocityComponent->Velocity = direction.GetNormalized();
		velocityComponent->Speed = chaseSpeed;

	}

	return eBTNodeStatus::Running;
}

#pragma region MoveToTargetNode

eBTNodeStatus MoveToNode::Execute(Entity* entity)
{
	if (entity)
	{
		//std::cout << "move\n";

		auto* blackboardComponent = entity->GetComponent<BlackboardComponent>();
		auto* transformComponent = entity->GetComponent<TransformComponent>();
		
		//if (!blackboardComponent->IsMovingToPOI)
		//	return eBTNodeStatus::Failure;

		//if (transformComponent->CurrentPos.DistanceTo(blackboardComponent->PointOfInterest) <= 0.001f)
		//	return eBTNodeStatus::Success;

		
		//if (transformComponent->CurrentPos == blackboardComponent->PointOfInterest)
		//	return eBTNodeStatus::Success;

		auto* velocityComponent = entity->GetComponent<VelocityComponent>();

	//	auto direction = transformComponent->CurrentPos.DirectionTo(blackboardComponent->PointOfInterest);
	//	velocityComponent->Velocity = direction.GetNormalized();

		return eBTNodeStatus::Running;
		// auto direction = en
	}


	// Move to point of intereset?

	// Check for a DestinationComponent?

	// if in range => return success.. else return is running...




	return eBTNodeStatus::Failure;
}

#pragma endregion MoveToTargetNode






#pragma region AttackTargetNode
eBTNodeStatus AttackTargetNode::Execute(Entity* entity)
{
	return eBTNodeStatus();
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


