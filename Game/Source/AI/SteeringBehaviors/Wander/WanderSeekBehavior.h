#pragma once
#include "../Base/SteeringBehavior.h"

class WanderSeekBehavior : public SteeringBehavior
{
public:
	WanderSeekBehavior();

	void Update(float deltaTime) override;
	const FVector2 GetSteeringForce(const FVector2& velocity) override;
	const FVector2 GetSteeringForce(const FVector2& position, const FVector2& velocity) override;


private:
	void SetRandomizedTarget();
	bool ShouldChangeDir() const;

	Hi_Engine::Range<float>	m_walkDurationRange;
	FVector2				m_window;
};