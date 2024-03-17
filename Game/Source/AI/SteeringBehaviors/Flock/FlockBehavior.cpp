#include "Pch.h"
#include "FlockBehavior.h"
#include "Entities/Entity.h"
#include "Components/Core/CoreComponents.h"


FlockBehavior::FlockBehavior()
	: m_minSeparationDistance{ 1.f }, m_radius{ 0.1f }, m_maxForce{ 1.f }, m_maxCohesion{ 3.f }
{
}

void FlockBehavior::Update(float deltaTime)
{
	// auto separation = GetSeparationForce();
}

const CU::Vector2<float> FlockBehavior::GetSteeringForce(const CU::Vector2<float>& velocity)
{
	float cohesionWeight = 5.f;
	float alignmentWeight = 3.f;
	float separationWeight = 1.f;

	auto cohesion = CalculateCohesionForce() * cohesionWeight;
	auto alginment = CalculateAlignmentForce() * alignmentWeight;
	auto separation = CalculateSeparationForce() * separationWeight;

	auto combined = cohesion + alginment + separation;
	return combined.GetNormalized();
	//return {};
}

const CU::Vector2<float> FlockBehavior::GetSteeringForce(const CU::Vector2<float>& position, const CU::Vector2<float>& velocity)
{
	return {};
}

void FlockBehavior::SetFlockMembers(const std::vector<Entity*>& entities)
{	
	// TODO; avoid setting self...

	m_flockMembers = entities;
}

void FlockBehavior::SetOwner(Entity* entity)
{
	m_owner = entity;
}

CU::Vector2<float> FlockBehavior::CalculateSeparationForce() const
{
	CU::Vector2<float> separationForce;
	float separationDistance = 2.f;
	int neighbours = 0;

	for (auto* member : m_flockMembers)
	{
		if (!member || member->GetID() == m_owner->GetID())
			continue;

		auto ownerTransformComponent = m_owner->GetComponent<TransformComponent>();
		auto otherTransformComponent = member->GetComponent<TransformComponent>();

		auto ownPosition = ownerTransformComponent->CurrentPos;
		auto otherPosition = otherTransformComponent->CurrentPos;


		auto distance = ownPosition.DistanceTo(otherPosition);
		if (distance < separationDistance && distance > 0)
		{
			auto pushForce = ownPosition - otherPosition;
			separationForce += pushForce / m_radius;

			++neighbours;
		}
	}

	if (neighbours == 0)
		return { 0.f, 0.f };

	separationForce = separationForce / (float)neighbours;
	separationForce *= m_maxForce;

	return separationForce.GetNormalized();
	// CU::Vector3<float> separationForce = { 0.f, 0.f, 0.f };


	// return {};
}

CU::Vector2<float> FlockBehavior::CalculateCohesionForce() const
{
	auto centerOfMass = m_owner->GetComponent<TransformComponent>()->CurrentPos;
	int neighbours = 0;

	for (auto* member : m_flockMembers)
	{
		if (!member || member->GetID() == m_owner->GetID())
			continue;

		auto otherTransformComponent = member->GetComponent<TransformComponent>();
		auto otherVelocityComponent = member->GetComponent<VelocityComponent>();

		auto otherPosition = otherTransformComponent->CurrentPos;
		auto otherVelocity = otherVelocityComponent->Velocity;
		//auto ownPosition = m_owner->GetComponent<TransformComponent>()->m_currentPos;
		// auto distance = ownPosition.DistanceTo(otherPosition);

		centerOfMass += otherPosition + otherVelocity;
		++neighbours;
	}


	if (neighbours == 0)
		return { 0.f, 0.f };

	centerOfMass = { centerOfMass.x / neighbours, centerOfMass.y / neighbours };
	return centerOfMass.GetNormalized();
}

CU::Vector2<float> FlockBehavior::CalculateAlignmentForce() const
{
	CU::Vector2<float> alignmentForce;
	int neighbours = 0;

	for (auto* member : m_flockMembers)
	{
		if (!member || member->GetID() == m_owner->GetID())
			continue;

		auto ownerTransformComponent = m_owner->GetComponent<TransformComponent>();
		auto otherTransformComponent = member->GetComponent<TransformComponent>();

		auto ownPosition = ownerTransformComponent->CurrentPos;
		auto otherPosition = otherTransformComponent->CurrentPos;

		if (ownPosition.DistanceTo(otherPosition) < 4.f)
		{
			auto otherVelocity = member->GetComponent<VelocityComponent>()->Velocity;
			alignmentForce += otherVelocity;

			++neighbours;
		}
	}
		
	if (neighbours == 0)
		return { 0.f, 0.f };

	
	alignmentForce = { alignmentForce.x / neighbours, alignmentForce.y / neighbours };
	return alignmentForce.Length() == 0.f ? CU::Vector2<float>{ 0.f, 0.f } : alignmentForce.GetNormalized();
}