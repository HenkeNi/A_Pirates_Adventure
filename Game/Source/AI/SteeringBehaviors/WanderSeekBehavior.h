#pragma once
#include "SteeringBehavior.h"
#include "../../Data/Structs.h"


class WanderSeekBehavior : public SteeringBehavior
{
public:
	WanderSeekBehavior();

	void Update(float aDeltaTime) override;
	const CU::Vector3<float> GetSteeringForce(const CU::Vector3<float>& aVelocity) override;
	const CU::Vector3<float> GetSteeringForce(const CU::Vector3<float>& aPosition, const CU::Vector3<float>& aVelocity) override;


private:
	void SetRandomizedTarget();
	bool ShouldChangeDir() const;

	Range<float>		m_walkDurationRange;
	Timer				m_timer;
	CU::Vector3<float>	m_target;
};