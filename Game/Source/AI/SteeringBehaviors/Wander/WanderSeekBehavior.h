#pragma once
#include "../Base/SteeringBehavior.h"

class WanderSeekBehavior : public SteeringBehavior
{
public:
	WanderSeekBehavior();

	void Update(float deltaTime) override;
	const CU::Vector2<float> GetSteeringForce(const CU::Vector2<float>& velocity) override;
	const CU::Vector2<float> GetSteeringForce(const CU::Vector2<float>& position, const CU::Vector2<float>& velocity) override;


private:
	void SetRandomizedTarget();
	bool ShouldChangeDir() const;

	Range<float>		m_walkDurationRange;
	CU::Vector2<float>	m_window;
};