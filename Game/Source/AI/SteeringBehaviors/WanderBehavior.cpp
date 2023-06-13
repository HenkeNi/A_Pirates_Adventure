#include "Pch.h"
#include "WanderBehavior.h"


WanderBehavior::WanderBehavior()
	: m_wanderAngle{ (float)Random::InRange(0, 1) }, m_distanceToSteeringCircle{ 100.f } /* 10 ? ?*/, m_steeringCircleRadius{ 125.f }, m_angleChange{ 100.f }
{
}



const CU::Vector3<float> WanderBehavior::GetSteeringForce(const CU::Vector3<float>& aVelocity)
{
	/* Calculate the circle's center */
	auto circleCenter = aVelocity.Length() == 0 ? aVelocity : aVelocity.GetNormalized();					// TODO: Add a NormalizeSafe()??
	circleCenter *= m_distanceToSteeringCircle;																// TODO: add ScaleBy Function to Vector??

	/* Calculate the displacement force */
	CU::Vector3<float> displacement{ 0.f, 0.f, -1.f };														// set to random???
	displacement *= m_steeringCircleRadius;

	SetAngle(displacement, m_wanderAngle);	// What is wander angle??

	m_wanderAngle += (Random::InRange(0, 1) * m_angleChange) - (m_angleChange * 0.5f);

	auto wanderForce = circleCenter + displacement;

	return wanderForce;
}


void WanderBehavior::Update(float aDeltaTime)
{
	//std::cout << "Wander: " << aPosition.x << ", " << aPosition.y << ", " << aPosition.z << "\n";

	m_timer.m_elapsed += aDeltaTime;
	if (ShouldChangeDir())
	{
		m_target = { (float)Random::InRange(2, 62), 0.f, (float)Random::InRange(2, 62) };
	}

	
		
	
		
}

void WanderBehavior::Wander()
{
	return Seek();
}

void WanderBehavior::Seek()
{

}

void WanderBehavior::SetNewTarget()
{

}

bool WanderBehavior::ShouldChangeDir() const
{
	return m_timer.m_elapsed >= m_timer.m_duration;
}

void WanderBehavior::SetAngle(CU::Vector3<float>& aVelocity, float aValue)
{
	float length = aVelocity.Length();
	aVelocity.x = std::cos(aValue) * length;
	aVelocity.z = std::sin(aValue) * length;
}