#include "Pch.h"
#include "WanderBehavior.h"


WanderBehavior::WanderBehavior()
	: m_wanderAngle{ Random::GenerateRandomFloatingPoint<float>(0.f, 1.f) }, m_distanceToSteeringCircle{ 100.f } /* 10 ? ?*/, m_steeringCircleRadius{ 125.f }, m_angleChange{ 100.f }, m_walkDuration{ 0.f }, m_shouldSeek{ false }
{
}



const CU::Vector2<float> WanderBehavior::GetSteeringForce(const CU::Vector2<float>& velocity)
{
	/* Calculate the circle's center */
	auto circleCenter = velocity.Length() == 0 ? velocity : velocity.GetNormalized();					// TODO: Add a NormalizeSafe()??
	circleCenter *= m_distanceToSteeringCircle;																// TODO: add ScaleBy Function to Vector??

	/* Calculate the displacement force */
	CU::Vector2<float> displacement{ 0.f, -1.f };														// set to random???
	displacement *= m_steeringCircleRadius;

	SetAngle(displacement, m_wanderAngle);	// What is wander angle??

	m_wanderAngle += (Random::GenerateRandomFloatingPoint<float>(0.f, 1.f) * m_angleChange) - (m_angleChange * 0.5f);

	auto wanderForce = circleCenter + displacement;

	return wanderForce;
}


void WanderBehavior::Update(float deltaTime)
{
	//m_timer.m_elapsed += aDeltaTime;
	if (ShouldChangeDir())
	{
		m_window = { Random::GenerateRandomFloatingPoint<float>(2.f, 62.f), Random::GenerateRandomFloatingPoint<float>(2.f, 62.f) };
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
	return false; //m_timer.m_elapsed >= m_timer.m_duration;
}

void WanderBehavior::SetAngle(CU::Vector2<float>& velocity, float value)
{
	float length = velocity.Length();
	velocity.x = std::cos(value) * length;
	velocity.y = std::sin(value) * length;
}