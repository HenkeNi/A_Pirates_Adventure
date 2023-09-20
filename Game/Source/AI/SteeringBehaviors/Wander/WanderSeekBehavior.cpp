#include "Pch.h"
#include "WanderSeekBehavior.h"



WanderSeekBehavior::WanderSeekBehavior()
{
	m_walkDurationRange.m_min = 5.f;
	m_walkDurationRange.m_max = 25.f;

	//m_timer.m_duration = 10.f;
	//m_timer.m_elapsed = 0.f;
}

void WanderSeekBehavior::Update(float aDeltaTime)
{
	//m_timer.m_elapsed += aDeltaTime;	// Dont do in behavior???
	if (ShouldChangeDir())
	{
		SetRandomizedTarget();
		//m_timer.m_elapsed = 0.f;
	}
}

const CU::Vector3<float> WanderSeekBehavior::GetSteeringForce(const CU::Vector3<float>& aVelocity)
{
	assert(false);

	return {};
}

const CU::Vector3<float> WanderSeekBehavior::GetSteeringForce(const CU::Vector3<float>& aPosition, const CU::Vector3<float>& aVelocity)
{
	static float maxVelocity = 50.f;

	// Seek towards target...
	auto desiredVelocity = m_target - aPosition;

	if (desiredVelocity.Length() == 0)
		desiredVelocity.Normalize();

	desiredVelocity *= maxVelocity;

	auto steeringForce = desiredVelocity - aVelocity;


	return steeringForce;
}

void WanderSeekBehavior::SetRandomizedTarget()
{
	m_target = { (float)Random::InRange(2, 62), 0.f, (float)Random::InRange(2, 62) };
}

bool WanderSeekBehavior::ShouldChangeDir() const
{
	return false; //  m_timer.m_elapsed >= m_timer.m_duration;
}