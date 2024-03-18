#include "Pch.h"
#include "WanderSeekBehavior.h"



WanderSeekBehavior::WanderSeekBehavior()
{
	m_walkDurationRange.Min = 5.f;
	m_walkDurationRange.Max = 25.f;

	//m_timer.m_duration = 10.f;
	//m_timer.m_elapsed = 0.f;
}

void WanderSeekBehavior::Update(float deltaTime)
{
	//m_timer.m_elapsed += aDeltaTime;	// Dont do in behavior???
	if (ShouldChangeDir())
	{
		SetRandomizedTarget();
		//m_timer.m_elapsed = 0.f;
	}
}

const CU::Vector2<float> WanderSeekBehavior::GetSteeringForce(const CU::Vector2<float>& velocity)
{
	assert(false);

	return {};
}

const CU::Vector2<float> WanderSeekBehavior::GetSteeringForce(const CU::Vector2<float>& position, const CU::Vector2<float>& velocity)
{
	static float maxVelocity = 50.f;

	// Seek towards target...
	auto desiredVelocity = m_window - position;

	if (desiredVelocity.Length() == 0)
		desiredVelocity.Normalize();

	desiredVelocity *= maxVelocity;

	auto steeringForce = desiredVelocity - velocity;


	return steeringForce;
}

void WanderSeekBehavior::SetRandomizedTarget()
{
	m_window = { Random::GenerateRandomFloatingPoint<float>(2, 62), Random::GenerateRandomFloatingPoint<float>(2, 62) };
}

bool WanderSeekBehavior::ShouldChangeDir() const
{
	return false; //  m_timer.m_elapsed >= m_timer.m_duration;
}