#include "Pch.h"
#include "ConditionNodes.h"
#include "Entity.h"


TargetInView::TargetInView(const Entity* aTarget)
	: m_target{ aTarget }, m_radius{ 600.f }
{
}

eBTNodeStatus TargetInView::Execute(Entity* anEntity)
{
	if (m_target)
	{
		/*auto currentPosition = anOwner->GetComponent<C_Transform>()->GetPosition();
		auto targetPosition = m_target->GetComponent<C_Transform>()->GetPosition();

		float distance = currentPosition.DistanceTo(targetPosition);

		if (distance <= m_radius)
		{
			return eBTNodeStatus::Success;
		}*/
	}
	return eBTNodeStatus::Failure;
}

void TargetInView::Clear()
{

}







TargetInRange::TargetInRange(const Entity* aTarget)
	: m_target{ aTarget }, m_radius{ 0.5f }
{
}

eBTNodeStatus TargetInRange::Execute(Entity* anEntity)
{
	if (m_target)
	{
		//auto currentPosition = anOwner->GetComponent<C_Transform>()->GetPosition();
		//auto targetPosition = m_target->GetComponent<C_Transform>()->GetPosition();

		//float distance = currentPosition.DistanceTo(targetPosition);

		//if (distance <= m_radius)
		//{
		//	// set attacking to true => walking to false?
		//	return eBTNodeStatus::Success;
		//}
	}
	return eBTNodeStatus::Failure;
}

void TargetInRange::Clear()
{

}