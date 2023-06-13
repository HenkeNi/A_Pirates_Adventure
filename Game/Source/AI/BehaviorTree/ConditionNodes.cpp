#include "Pch.h"
#include "ConditionNodes.h"
#include "../GameObject/GameObject.h"
#include "../GameObject/Components/Core/Transform/C_Transform.h"


TargetInView::TargetInView(const GameObject* aTarget)
	: m_target{ aTarget }, m_radius{ 600.f }
{
}

eBTNodeStatus TargetInView::Execute(GameObject* anOwner)
{
	if (m_target)
	{
		auto currentPosition = anOwner->GetComponent<C_Transform>()->GetPosition();
		auto targetPosition = m_target->GetComponent<C_Transform>()->GetPosition();

		float distance = currentPosition.DistanceTo(targetPosition);

		if (distance <= m_radius)
		{
			return eBTNodeStatus::Success;
		}
	}
	return eBTNodeStatus::Failure;
}

void TargetInView::Clear()
{

}







TargetInRange::TargetInRange(const GameObject* aTarget)
	: m_target{ aTarget }, m_radius{ 0.5f }
{
}

eBTNodeStatus TargetInRange::Execute(GameObject* anOwner)
{
	if (m_target)
	{
		auto currentPosition = anOwner->GetComponent<C_Transform>()->GetPosition();
		auto targetPosition = m_target->GetComponent<C_Transform>()->GetPosition();

		float distance = currentPosition.DistanceTo(targetPosition);

		if (distance <= m_radius)
		{
			// set attacking to true => walking to false?
			return eBTNodeStatus::Success;
		}
	}
	return eBTNodeStatus::Failure;
}

void TargetInRange::Clear()
{

}